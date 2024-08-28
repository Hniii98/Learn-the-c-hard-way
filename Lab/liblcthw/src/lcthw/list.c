#include "lcthw/list.h"
#include "lcthw/dbg.h"
#include  <assert.h>


List *List_create()
{
	return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
  	assert(list != NULL);

	LIST_FOREACH(list, first, next, cur)
	{
		free(cur->prev);
		cur->prev = NULL;
	}
	
	if(list->last) 
	{
		free(list->last);
		list->last = NULL;
	}
	free(list);
	list = NULL;
}

void List_clear(List *list)
{
	assert(list != NULL);

	LIST_FOREACH(list, first, next, cur)
	{
		free(cur->value); // 释放每个节点的值，而不是节点本身
		cur->value = NULL;
	}
}

void List_clear_destroy(List *list)
{
	//List_clear(list);  // 释放节点和对应的值
	//List_destroy(list);
	assert(list != NULL);

	LIST_FOREACH(list, first, next, cur)
	{
		if(cur->prev)
		{
			free(cur->prev->value);
			free(cur->prev);
			cur->prev->value = NULL;
			cur->prev = NULL;
		}
	}

	if(list->last)
	{
		free(list->last->value); // 必须保证list->last为NULL，不然list->last->value为对NULL解引用
		free(list->last); 
		list->last->value = NULL;
		list->last = NULL;
	}

	free(list);
	list = NULL;
	//assert(list != NULL);
}

void List_push(List *list, void *value)
{
	assert(list != NULL);

	ListNode *node = calloc(1, sizeof(ListNode));  // void *calloc(size_t num, size_t size) 
												   // calloc会把分配的内存初始化为0,malloc为随机值
												   // 纯C中，void *可以自动转换为任何其他类型指针
												   // 不需要强制转换 
	check_mem(node);

	node->value = value;

	if(list->last == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}

	list->count++;

error:
	return;
}

/*
 *  头插法
 */
void List_unshift(List *list, void *value)
{
	assert(list != NULL);

	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if(list->first == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
   	{ 
		node->next = list->first; 
		list->first->prev = node; 
		list->first = node;
   	}
	
	list->count++;

error:
	return;
}

void *List_shift(List *list) // 删除头结点
{
	assert(list != NULL);

	ListNode *node = list->first;
	return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
	assert(list != NULL);

	void *result = NULL;

	check(list->first && list->last, "List is empty. ");
	check(node, " node can't be NULL");

	if(node == list->first && node == list->last) //  只有一个节点
	{
		list->first = NULL;
		list->last = NULL;
	}
	else if(node == list->first) // 多节点删除头结点
	{
list->first = node->next;
		check(list->first != NULL, " Invalid list, somehow got a first that is NULL. ");
		list->first->prev = NULL;
	}
	else if(node == list->last) // 多节点删除尾节点
{
		list->last = node->prev;
		check(list->last != NULL, " Invalid list, somehow got a next that is NULL .");
		list->last->next = NULL;
	}
	else // 多节点删除中间节点
	{
			ListNode *after = node->next;
			ListNode *before = node->prev;
			after->prev = before;
			before->next = after;
	}

	list->count--;
	result = node->value;
	free(node);
	node = NULL;

error:
	return result;
}

void *List_pop(List *list)
{
	assert(list != NULL);
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_check_invariants(List *list)
{
	assert(list != NULL);
	
	assert(list->count >= 0);

	if(list->count > 0)
	{
		assert(list->first != NULL);
		assert(list->last != NULL);
	}
	else
	{
		assert(list->first == NULL);
		assert(list->last == NULL);
	}
}
/*
 *  
 *  采用题目中所给的Makefile进行构建一直出错，暂时还找不到原因，采用如下命令手动构建：
 *  gcc -c -Isrc -o build/list.o src/lcthw/list.c
 *	ar rcs build/liblcthw.a build/list.o
 *  gcc -g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG tests/list_tests.c build/liblcthw.a -o tests/
 *  list_tests -ldl
 *
 *  运行正常，./list_tests也都pass，后续学完Makefile再来Debug
 *  又经过了1一个小时的排查，最终发现，是链接顺序的问题。链接静态库必须在源文件之后。
 *  于是在Makefile文件中添加如下代码：
 *  tests/%: tests/%.c $(TARGET)
 *	$(CC) $(CFLAGS) $(LIBS) -o $@ $< $(TARGET)、
 *	最终make顺利执行。终于解决了。
 */

   

