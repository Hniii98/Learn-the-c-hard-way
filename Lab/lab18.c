#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


void die(const char *message)
{
	if(errno)
	{
		perror(message);
	}
	else
	{
		printf("ERROR: %s\n", message);
	}

	exit(1);
}


//typedef a function ptr
typedef int (*compare_cb)(int a, int b);
typedef int *(*sort_func)(int *numbers, int count, compare_cb cmp);

/*
 *  bubble sort
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;  // control loop times
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if(!target) die("Meory error.");

	memcpy(target, numbers, count * sizeof(int)); // deep copy origin array
	
	for(i = 0; i < count; ++i)
	{
		for(j = 0; j < count - 1; ++j)
		{
			if(cmp(target[j], target[j+1]) > 0)
			{
				temp = target[j+1];
				target[j+1] = target[j];
				target[j] = temp;
			}
		}
	}
	
	return target;
}

/*
 *  selection sort 
 */
int *selection_sort(int *numbers, int count, compare_cb cmp)
{
	int *target = malloc(count * sizeof(int));
	int tmp = 0;
	int i = 0;
	int j = 0;

	memcpy(target, numbers, count * sizeof(int));

	for(i = 0; i < count-1; ++i)
	{
		int guard_idx = i;
		for(j = i+1; j < count; ++j)
		{
			if(cmp(target[guard_idx], target[j]) > 0)
				guard_idx = j;
		}

		if(guard_idx != i) // swap
		{
			tmp = target[i];
			target[i] =  target[guard_idx];
			target[guard_idx] = tmp;
		}

	}
	
	return target;
}	


int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}


int strange_order(int a, int b)
{
	if(a == 0 || b == 0)
	{
		return 0;
	}
	else
	{
		return a % b;
	}
}

/*
 * Do the sorting and print it out to test it
 */
void test_sorting(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int *sorted = bubble_sort(numbers, count, cmp);

	if(!sorted) die("Failed to sort as requested");

	for(i = 0; i < count; i++)
	{
		printf("%d ", sorted[i]);
	}
	printf("\n");

	unsigned char *data = (unsigned char*)cmp;

	for(i = 0; i < 25; i++)
	{
		printf("%02x:", data[i]);
	}
	printf("\n");

	free(sorted);
}

void test_sorting_v2(int *numbers, int count, sort_func func, compare_cb cmp)
{
	int i = 0;
	int *sorted = func(numbers, count, cmp);

	if(!sorted) die("Faile to sort as requested");

	for(i = 0; i < count; ++i)
	{	
		printf("%d ", sorted[i]);
	}
	printf("\n");

	free(sorted);
}


int main(int argc, char *argv[])
{
	if(argc < 2) die("USAGE : ex18 4 3 1 5 6");

	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;

	int *numbers = malloc(count * sizeof(int));
	if(!numbers) die("Memory error.");

	for(i = 0; i < count; i++)
	{
		numbers[i] = atoi(inputs[i]); // transfer char to int
	}

	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);
	//test_sorting(numbers, count, die); 编译时报错，因为参数列表不匹配	
	//test_sorting(numbers, count, NULL); 段错误
	
	test_sorting_v2(numbers, count, bubble_sort, sorted_order);
	test_sorting_v2(numbers, count, selection_sort, sorted_order);
	test_sorting_v2(numbers, count, selection_sort, reverse_order);

	free(numbers);

	return 0;
}

/*
 * #1 
 * 通过如下命令：
 * objdump -d lab18 | grep -A 20 "reverse_order"
 * 对比命令行输出的机器码，二者完全一致，多个函数开始都有相同
 * 机器码“f3 0f 1e fa”，这串机器码代表endbr64指令，该指令通常
 * 插入在函数入口，用于保护程序的控制流。
 * 通过搜索objdump给出的偏移地址140a,直接在hexedit找到对应的机器码。
 *
 * #2
 * hexedit中，为了不应程序的正常使用，修改了main函数中对于参数个数不足的提示
 * ，USAGE : ex18 4 3 1 5 6将原来的"USAGE : ex18 4 3 1 5 6"通过修改16进制为2A 修改为==》"USAGE*: 
 * ex18 4 3 1 5 6",错误输入参数个数后，显示为修改后的提示
 *
 * #3
 * 将错误的函数传给compare_cb，编译时会报错，因为参数列表不匹配
 *
 * #4
 * 运行时，提示发生segment fault
 * 运行valgrind，提示jump into invalid address
 *
 * #5
 * 编写了新的test_sorting_v2,参数列表新增了排序函数，使得test_sorting_v2能够
 * 接受不同的排序算法及比较运算符
 *
 */
 * 
