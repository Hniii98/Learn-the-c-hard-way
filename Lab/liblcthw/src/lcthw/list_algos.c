#include "lcthw/list_algos.h"
#include "lcthw/dbg.h"

void ListNode_swap(ListNode *a, ListNode *b)
{
	void *tmp = a->value;
	a->value = b->value; // value对应的是指针,所以交换的是值的地址
	b->value = tmp;
}

int List_bubble_sort(List *list, List_compare cmp)
{
	int swapped = 0;
	if(!list) return 0;
	if(List_count(list) <= 1) return 0;	

	do
	{
		ListNode *cur = list->first;
		swapped = 0;

		while(cur->next)
		{
			if(cmp(cur->value, cur->next->value) > 0)
			{
				ListNode_swap(cur, cur->next); // 参数应该传入节点而不是对应value，否则段错误
				swapped = 1;
			}
			cur = cur->next;
		}
	}while(swapped);
	/*
	do
	{
		sorted = 0;
		LIST_FOREACH(list, first, next, cur)
		{
			if(cur->next)
			{
				if(cmp(cur->value, cur->next->value) > 0)
				{
					ListNode_swap(cur, cur->next);
					sorted = 0;
				}
			}
		}
	}while(!sorted);
	*/

	return 0;
}

/*
List *List_merge(List *left, List *right, List_compare cmp)
{	
    List *result = List_create();
    void *val = NULL;

    while(List_count(left) > 0 || List_count(right) > 0) {
        if(List_count(left) > 0 && List_count(right) > 0) {
            if(cmp(List_first(left), List_first(right)) <= 0) {
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            List_push(result, val);
        } else if(List_count(left) > 0) {
            val = List_shift(left);
            List_push(result, val);
        } else if(List_count(right) > 0) {
            val = List_shift(right);
            List_push(result, val);
        }
    }
    return result;
}
*/

/* 给定两个链表的首节点，合并成一个链表并返回首节点*/
ListNode *List_merge(ListNode *left, ListNode *right, List_compare cmp)
{
	ListNode *dummy = calloc(1, sizeof(ListNode));
	//check_mem(dummy);
	if(dummy == NULL) printf("1111111111111111"); 

	ListNode *cur = dummy; // 循环变量
	
	while(left && right)
	{
		if(cmp(left->value, right->value) <= 0)
		{
			cur->next = left;
			left->prev = cur;
			cur = cur->next;
			left = left->next;
		}
		else
		{
			cur->next = right;
			right->prev = cur;
			cur = cur->next;
			right = right->next;
		}

	}

	if(left) // left还有节点剩下
	{
		cur->next = left;
		left->prev = cur;
	}
	else if(right)
	{
		cur->next = right;
		right->prev = cur;
	}
	
	if(dummy->next)dummy->next->prev = NULL; // 将真正的头结点的prev设置为NULL
	
	cur = dummy->next; //  方便删除dummy
	free(dummy);
	
	return cur; // 此时cur指向合并后链表的第一个节点
}

/*给定一个链表的首节点，返回指向中间节点的指针*/
ListNode *List_split(ListNode *Node)
{
	if(!Node) return NULL;

	ListNode *fast = Node->next;
	ListNode *slow = Node;

	while(fast && fast->next)
	{	
		fast = fast->next->next;
		slow = slow->next;
	}
	
	ListNode *second = slow->next;
	slow->next = NULL;   // 断开链表
	second->prev = NULL; // 断开链表
	
	return second; 
}

ListNode *merge_sort(ListNode *Node, List_compare cmp)
{
	if(!Node || !Node->next) return Node; // 递归出口
	
	ListNode *left = Node;
	ListNode *right = List_split(Node);

	ListNode *left_sorted = merge_sort(left, cmp);
	ListNode *right_sorted = merge_sort(right, cmp);

	return List_merge(left_sorted, right_sorted, cmp);
}

List *List_merge_sort(List *list, List_compare cmp)
{
	if(!list) return list;
	if(list->count < 2) return list;

	ListNode *first = merge_sort(list->first, cmp);

	ListNode *cur = first; // 循环变量
	while(cur->next) cur = cur->next;
	
	list->first = first;
	list->last = cur;
	
	return list;
}



/*
List *List_merge_sort(List *list, List_compare cmp)
{
    if(List_count(list) <= 1) {
        return list;
    }

    List *left = List_create();
    List *right = List_create();
    int middle = List_count(list) / 2;

    LIST_FOREACH(list, first, next, cur) {
        if(middle > 0) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }

        middle--;
    }

    List *sort_left = List_merge_sort(left, cmp);
    List *sort_right = List_merge_sort(right, cmp);

    if(sort_left != left) List_destroy(left);
    if(sort_right != right) List_destroy(right);

    return List_merge(sort_left, sort_right, cmp);
}
*/
