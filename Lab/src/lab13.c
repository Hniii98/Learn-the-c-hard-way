#include <stdio.h>



// 命令行 ./lab13 aaa  和  ./lab13 "aaa" 完全等价

int main(int argc, char *argv[])
{
	int i = 0;

	for(i = 1; i < argc; i++)
	{
		printf("The %d argument is : %s\n", i, argv[i]);
	}
	
	if(argc != 2)
	{
		printf("ERROR: You need one argument.\n");
		return 1;
	}
	
	
	char letter;

	/*
	for(i = 0, letter = argv[1][i]; argv[1][i] != '\0'; i++)
	{
		//char letter = argv[1][i];

		switch(letter)
		{
			case 'a':
			case 'A':
				printf("%d: 'A'\n", i);
				break;

			case 'e':
			case 'E':
				printf("%d: 'E'\n", i);
			   	break;

			case 'i':
			case 'I':
				printf("%d: 'I'\n", i);
				break;

			case 'o':
			case 'O':
				printf("%d: 'O'\n", i);
				break;
		
			case 'u':
			case 'U':
				printf("%d: 'U'\n", i);
				break;

			case 'y':
			case 'Y':
				if(i > 2)
				{
					printf("%d: 'Y'\n", i);

				}
				break;

			default:
				printf("%d: %c is not a vowel\n", i, letter);



		}
	}
	*/
	for(i = 0, letter = argv[1][i]; argv[1][i] != '\0'; i++)
	{
		if(letter == 'a' || letter == 'A') printf("%d: 'A'\n", i);
		else if(letter == 'e' || letter == 'E') printf("%d: 'E'\n", i);
		else if(letter == 'i' || letter == 'I') printf("%d: 'I'\n", i);
		else if(letter == 'o' || letter == 'O') printf("%d: 'O'\n", i);
		else if(letter == 'u' || letter == 'U') printf("%d: 'U'\n", i);
		else printf("%d: %c is not a vowel\n", i, letter);
	
	}
	// to lower case
	for(int i = 0; argv[1][i] != '\0'; i++)
	{
		if(argv[1][i] >= 'A' && argv[1][i] <= 'Z') argv[1][i] += 'a' - 'A'; // 通过字母之间的关系进行算术运算

	}
	printf("The lower case:%s\n", argv[1]); 

	return 0;
}

/* #1
 * 通过字母之间的ASCII码关系进行大小写的转换，避免对ASCII的死记硬背～
 *
 * #2
 * 在初始化表达式中对letter进行初始化，记得先对letter进行声明。
 *
 * #3
 * 
 * #4
 * 哈哈哈，当然是if
 *
 * #5
 * 如果在if代码块外写了个braek,那么不会进入if块.如果把它移进if代码块，当if条件不满足时，default模块的代码始终会运行。
 */
