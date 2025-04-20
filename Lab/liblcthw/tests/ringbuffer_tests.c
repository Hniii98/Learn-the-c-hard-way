#include "minunit.h"
#include <lcthw/ringbuffer.h>
#include <assert.h>

static RingBuffer *buffer = NULL;
char *test_data = "testdata";
#define TEST_DATA_LEN 9  // strlen("test data") + null terminator

char *test_create()
{
    debug("----- test_create");
    buffer = RingBuffer_create(15);
    mu_assert(buffer != NULL, "Failed to create ring buffer.");
    mu_assert(RingBuffer_empty(buffer), "Buffer should start empty.");
    
    return NULL;
}

char *test_read_write()
{
    debug("----- test_read_write");
    
    // Test writing
    int rc = RingBuffer_write(buffer, test_data, TEST_DATA_LEN);
    mu_assert(rc == TEST_DATA_LEN, "Failed to write full data.");
    mu_assert(!RingBuffer_empty(buffer), "Buffer should not be empty after write.");
    mu_assert(RingBuffer_available_data(buffer) == TEST_DATA_LEN, 
             "Available data should match written length.");
    
    // Test reading
    char target[TEST_DATA_LEN];
    rc = RingBuffer_read(buffer, target, TEST_DATA_LEN);
    mu_assert(rc == TEST_DATA_LEN, "Failed to read full data.");
    mu_assert(memcmp(target, test_data, TEST_DATA_LEN) == 0, 
             "Read data doesn't match written data.");
    mu_assert(RingBuffer_empty(buffer), "Buffer should be empty after read.");
    
    
    return NULL;
}

char *test_destroy()
{
    debug("----- test_destroy");
    mu_assert(buffer != NULL, "Failed to make buffer #2");
    RingBuffer_destroy(buffer);
    
    return NULL;
}

char *all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_destroy);
    
    return NULL;
}

RUN_TESTS(all_tests);
