#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;


	if(argc == 1)
	{
		printf("You only have one argument. You suck \n");
	}
	else if(argc > 1 && argc < 4)
	{
		printf("Here's your arguments:\n");
	
		for(i = 1; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		
		printf("\n");
	}
	else
	{
		printf("You have too many arguments. You suck.\n");
	}
	

	return 0;
}


/* #1 
 * C语言中的布尔运算符包括 & | ~ ^ 
 * 分别为按位与，按位或，按位非，按位异或（相同为0，反之为1）
 *
 * #2
 * 测试用例1：./ex12 one 
 * 测试用例2：./ex12 one two
 * 测试用例3：./ex12 one two three
 * 测试用例4：./ex12
 */ 
