#undef NDEBUF
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lcthw/dbg.h>
#include <lcthw/ringbufferposix.h>

RingBufferPOSIX * RingBufferPOSIX_create(unsigned int length)
{
	RingBufferPOSIX *buffer = calloc(1, sizeof(RingBufferPOSIX));
	if(!buffer) return NULL;

	buffer->length = length + 1; // when stat is full, there's one location unavailable. 
	/*
	 * read == write  ----> empty 
	 * write+1 == full ----> full
	 */ 
	buffer->read = 0;
	buffer->write = 0;

	buffer->buffer = calloc(buffer->length, sizeof(char));
	if(!buffer->buffer)
	{
	  free(buffer);
	  return NULL;
	}
	return buffer;
}

void RingBufferPOSIX_destroy(RingBufferPOSIX *buffer)
{
  if(buffer)
  {
	free(buffer->buffer);
	free(buffer);
  }
}

int RingBufferPOSIX_write(RingBufferPOSIX *buffer, char *data, unsigned int size)
{
	unsigned int available = RingBufferPOSIX_available_space(buffer);
	check(available, "Not enough space: %u request, %u available", size, available);
	/* Only when write > read, there are rmost space for writing */
	unsigned int rmost_space = (buffer->write >= buffer->read) ? buffer->length - buffer->write : 0;
	
	if(rmost_space >= size)
	{
		/* Right most space can contain all given data */
		memcpy(buffer->buffer + buffer->write, data, size);
	}
	else
	{
	  /* We need seperate data to two parts to write */
		memcpy(buffer->buffer+buffer->write, data, rmost_space);	  
		memcpy(buffer->buffer, data+rmost_space, size-rmost_space);
	}

	/* Update write */
	buffer->write = (buffer->write + size) % buffer->length;
	return size;
error:
	return -1;
}

int RingBufferPOSIX_read(RingBufferPOSIX *buffer, char *target, unsigned int amount)
{
	unsigned int available = RingBufferPOSIX_available_data(buffer);
	check(amount <= available, "Not enough in buffer: has%u, needs %u", available, amount); // When conditon is not met, print the given message and go to error tag. 	

	unsigned int rmost_data_len = (buffer->read >= buffer->write) ? buffer->length-buffer->read : 0;
	if(rmost_data_len != 0)
	{
	  /* Now read > write,  we should read two parts */
	  memcpy(target, buffer->buffer+buffer->read, rmost_data_len);
	  memcpy(target+rmost_data_len, buffer, amount-rmost_data_len); 
	}
	else
	{
	  memcpy(target, buffer->buffer+buffer->read, amount);
	}
  
    /* Update read */
	buffer->read =(buffer->read + amount) % buffer->length;

	return amount;
error:
	return -1;
}	
	
