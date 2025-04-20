#include <stdio.h>


void print_name(char **name_ptr, int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		printf("The string is: %s\n", *(name_ptr + i));
	}
}

int main(int argc, char *argv[])
{
	int ages[] = {23, 43, 12, 89, 2};
	char *names[] = 
	{
		"Alan", "Frank",
		"Mary", "john", "Lisa"
	};

	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	for(int i = 0; i < count; i++)
	{
		printf("%s has %d years alive.\n",
				//names[i], ages[i]);
				*(names + i), *(ages + i));
	}

	printf("---\n");


	int *cur_age = ages;
	char **cur_name = names;

	for(i = 0; i < count; i++)
	{
		printf("%s is %d years old.\n",
				//*(cur_name+i), *(cur_age+i));
				cur_name[i], cur_age[i]);
	}

	printf("---\n");

	for(i = 0; i < count; i++)
	{
		printf("%s is %d years old again.\n",
				//cur_name[i], cur_age[i]);
				*(&names[0] + i), *(cur_age + i));
	}

	printf("---\n");

	for(cur_name = names, cur_age = ages;
					(cur_age - ages) < count; // 指针运算被定义为元素个数差
					cur_name++, cur_age++)
	{
		printf("%s lived %d years so far. \n",
				//*cur_name, *cur_age);
				names[cur_age - ages], ages[cur_age - ages]);
	}	

	for(cur_name = names, cur_age = ages;
					(cur_age - ages) < count;
					cur_name++,  cur_age++)
	{
		printf("The address of ptr is cur_name: %p, cur_age: %p\n", cur_name, cur_age);
	}
	
	int len = sizeof(names) / sizeof(names[0]);
	print_name(&names[0], len);i // 如果传入&name, 那类型是函数指针。
								 // names 是一个 char* 类型的数组，即 char *names[]. 当你传递 names 到函数时，
								 // 它会被隐式地转换为 char** 类型。这是因为数组名在表达式中总是会被转换为指向其
								 // 第一个元素的指针。所以 names 实际上会被转换为 char**，即 &names[0]。

	return 0;
}

/*
 *  #1 2 3 4
 *
 *  #5
 *  *(&names[0] + i)
 *  
 *  #6
 *  
 *  int i = 0;
 *  while(i < count)
 *  {
 *     // print 
 *     i++;
 *  }
 *  
 *  
 *		
 *  
 */
