#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int i = 0;

	
	char *states[] = {
			NULL, "Oregon",
		"Washington", "Texas"
		};
	
	argv[0] = states[1];		
	if(argc > 1) states[2] = argv[1];

	for(i = 0; i < argc; i++){
		printf("arg %d: %s\n", i, argv[i]);
	}

	int num_states = 4;

	for(i = 0; i < num_states; i++){
		printf("state %d: %s\n", i, states[i]);
		if(states[i] != NULL) // strcmp()参数传入空指针会引发seg fault
		{
			if(strcmp(states[i], "Washington") == 0) break;
		}
	}
	
	return 0;
}

/* #1
 * for(INITIALIZER; TEST; INCREMENTER)
 *
 * INITIALIZER:(可省）初始化表达式，在循环开始时执行一次
 * TEST:(可省)条件表达式，在每次循环开始前进行判断
 * INCREMENTAL：（可省）增量表达式，在每次循环结束时执行。
 * 
 * 三个部分都可省，此时与while(true)等价，但其中的；必须保留
 *
 * #2
 * int i, j;
 * for(i = 0, j =1; i < 20, j < 20; i++, j++)
 * C语言中，多个表达式可以用逗号分开（表达式1， 表达式2， 表达式3），各表达
 * 式的值分开计算，整个表达式的直以末尾表达式的值作为整个表达式的值。
 * TIPS： 此时这个循环的条件表达式以j<20的值为准，i<20无用。
 * 		  例如i=2；j=（i=3，i+1）；此时j的值为4而不是其他。
 *
 * #3
 * c语言中NULL用来表示空指针，也即指向地址0 的指针，如果将states[0]赋值为
 * NULL表示字符串指针为空。采用%s占位符打印出为：（null) 
 * TIPS: 如果采用其他占位符，如%c，则为未定义行为。
 *
 * #4
 * 只要数组的索引合法，state和argv数组可以相互赋值。
*/
