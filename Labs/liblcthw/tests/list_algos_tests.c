#include "minunit.h"
#include "lcthw/list_algos.h"
#include <assert.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS", "aacc", "scg12"};
#define NUM_VALUES 7

List *create_words()
{
    int i = 0;
    List *words = List_create();

    for(i = 0; i < NUM_VALUES; i++) {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List *words)
{
    LIST_FOREACH(words, first, next, cur) {
        if(cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort()
{
    List *words = create_words();

    // should work on a list that needs sorting
    int rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // should work on an already sorted list
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // should work on an empty list
    words = List_create(words);
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort()
{
    List *words = create_words();

    // should work on a list that needs sorting
    List *res = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List *res2 = List_merge_sort(res, (List_compare)strcmp);
    mu_assert(is_sorted(res2), "Should still be sorted after merge sort.");
   	//List_destroy(res2);
   	//List_destroy(res);  更改后的写法返回的都是同一个list,所以不需要多次List_destory
	//  否则会double free							
    List_destroy(words);
    return NULL;
}

char *merge_sort_loop()
{
	int loops = 10000000;
	time_t start_time, end_time;
	time(&start_time);
	while(loops--) test_merge_sort();
	time(&end_time);
	double seconds = difftime(end_time, start_time);

	printf("Loop merge sort: 1kw times spend %.2f seconds\n", seconds);

	return NULL;
}

char *bubble_sort_loop()
{
	int loops = 10000000;
	time_t start_time, end_time;
	time(&start_time);
	while(loops--) test_bubble_sort();
	time(&end_time);
	double seconds = difftime(end_time, start_time);

	printf("Loop bubble sort: 1kw times spend %.2f seconds\n", seconds);
	
	return NULL;
}


char *all_tests()
{
    mu_suite_start();

	mu_run_test(bubble_sort_loop);
	mu_run_test(merge_sort_loop);
    //mu_run_test(test_bubble_sort);
   //	mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);
