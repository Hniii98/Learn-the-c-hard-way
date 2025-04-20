#ifndef lcthw_Stack_h
#define lcthw_Stack_h

#include <lcthw/list.h>
#include <assert.h>

struct Stack;

typedef struct Stack
{
	List *list;
}Stack;


Stack *Stack_create()
{
  Stack *stack = calloc(1, sizeof(Stack));
  assert(stack != NULL);
  stack->list = List_create();
  return stack;
}


void Stack_destroy(Stack *stack)
{
  if(!stack) return; 
  
  List_clear_destroy(stack->list);
  free(stack);

}

int Stack_count(Stack *stack)
{
  return stack->list->count;
}

void *Stack_peek(Stack *stack)
{
  return List_last(stack->list);
}

void Stack_push(Stack *stack, void *value)
{
	assert(stack != NULL);
	List_push(stack->list, value);
}

void *Stack_pop(Stack *stack)
{
	assert(stack != NULL);
	void *result = List_last(stack->list);
	List_remove(stack->list, stack->list->last); // remove last node of list
	return result;
}

#define STACK_FOREACH(L, V) ListNode *_node = NULL;\
	ListNode *V = NULL;\
	for(V = _node = L->list->last; _node != NULL; V = _node = _node->prev)

#endif

