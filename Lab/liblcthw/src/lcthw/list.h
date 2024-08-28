#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode
{
	struct ListNode *next;
	struct ListNode *prev;
	void *value;
}ListNode;

typedef struct List
{
	int count;
	ListNode *first;
	ListNode *last;
}List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);
void List_check_invariants(List *list);
#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);

/*
 * LIST_FOREACH中V和_node都不可或缺，因为ListNode对应的value也是一个链表
 * 此时，V可以用来遍历整个子链表，而_node持有父链表的正确节点进行下一个
 * 遍历。
 *
 */
 
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
	ListNode *V = NULL;\
	for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif



