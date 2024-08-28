#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include "lcthw/list.h"

typedef int (*List_compare)(const void *a, const void*b); // cmp函数

int List_bubble_sort(List *list, List_compare cmp);

ListNode *List_split(ListNode *Node);
ListNode *List_merge(ListNode *left, ListNode *right, List_compare cmp);
ListNode *merge_sort(ListNode *Node, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

#endif


