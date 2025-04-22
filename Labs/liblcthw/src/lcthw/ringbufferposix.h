#ifndef _lcthw_RingBufferPOSIX_h
#define _lcthw_RingBufferPOSIX_h

#include <lcthw/bstrlib.h>

typedef struct {
    char *buffer;
    unsigned  int length;
    unsigned  int read;
    unsigned  int write;
} RingBufferPOSIX;

RingBufferPOSIX *RingBufferPOSIX_create(unsigned int length);

void RingBufferPOSIX_destroy(RingBufferPOSIX *buffer);

int RingBufferPOSIX_read(RingBufferPOSIX *buffer, char *target, unsigned int amount);

int RingBufferPOSIX_write(RingBufferPOSIX *buffer, char *data, unsigned int length);

#define RingBufferPOSIX_available_data(B) \
	((B)->write >= (B)->read ? (B)->write - (B)->read : (B)->length - (B)->read + (B)->write)

#define RingBufferPOSIX_available_space(B) \
    ((B)->write >= (B)->read ? \
        (B)->length - (B)->write - 1 + (B)->read : \
        (B)->read - (B)->write -1)

#endif
