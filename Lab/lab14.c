#include <stdio.h>
#include <ctype.h>
#include <string.h>


// int can_print_it(char ch);
void print_letters(char arg[], int len);

void print_arguments(int argc, char *argv[])
{
	int i = 0;

	for(i = 0; i < argc; i++)
	{
		print_letters(argv[i], strlen(argv[i]));
	}
}

void print_letters(char arg[], int len)
{
	int i = 0;

	for(i = 0; i < len; i++) // strlen doesn't include '\0'
	{
		char ch = arg[i];
		
		if(isalpha(ch) || isblank(ch))
		{
			printf(" '%c' == %d ", ch, ch);
		}
		
		printf("\n");

	}
}

/*
int can_print_it(char ch)
{
	return isalpha(ch) || isblank(ch);
}
*/

int main(int argc, char *argv[])
{
	print_arguments(argc, argv);
	return 0;
}

/*  #1 
 *  不需要
 *
 *  #2
 *  参数传入strlen(argv[i])即可
 *
 *  #3
 *  isdigit() : 是否为数字
 *  isprint() : 是否为ch或空格
 *
 *  #4
 *  ？？？本书不就是用K&R语法吗 迷惑。。。
 *
 */

