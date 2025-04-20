#ifndef lcthw_Queue_h
#define lcthw_Queue_h

#include <lcthw/list.h>
#include <assert.h>

struct Queue;

typedef struct Queue
{
  List *list;
}Queue;


Queue *Queue_create()
{
  Queue *queue = calloc(1, sizeof(Queue));
  assert(queue != NULL);

   queue->list = List_create();
   return queue;
}

void Queue_destroy(Queue *queue)
{
  List_clear_destroy(queue->list);
  free(queue);
}


int Queue_count(Queue *queue)
{
	return queue->list->count;
}

void *Queue_peek(Queue *queue)
{
	return List_first(queue->list);
}

void *Queue_recv(Queue *queue)
{
  void *result = List_first(queue->list);
  List_shift(queue->list); // remove head list node
  return result;
}

void Queue_send(Queue *queue, void *value)
{
  List_push(queue->list, value);
}


#define QUEUE_FOREACH(L, V) ListNode *_node = NULL;\
	ListNode *V = NULL;\
   for(V = _node = L->list->first; _node != NULL; V = _node = _node-> next)

#endif



