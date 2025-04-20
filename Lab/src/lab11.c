#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	int i  = 0;
	
	char *states[] = {
		"California", "Oregon",
		"Washington", "Texa"
	};

	i = argc;
	while(i--){
		printf("arg %d: %s\n", i, argv[i]);
		if(i <= 3){
			states[i] = argv[i];
		}
	}


	int num_states = 4;
	i = 0;
	

	while(i < num_states){
		printf("state %d：%s\n", i, states[i]);
		i++;
		if(states[i] != NULL)
		{
			if(strcmp(states[i], "Washington") == 0) break;
		}
	}

	return 0;
}

/* #1 2 3
 * while(i--) 先判断i的合法性，然后对i递减
 * while(--i) 先递减i，然后判断其合法性
 * 因此，只需要在遍历argv数组时，判断索引是否在states数组的合法范围内，然后进行赋值。
 *
 * #4
 * argv[i]和state[i]都存放的是指向字符串的指针，states[i] = argv[i]只不过复制了对应指针的值，发生的是浅拷贝。
 * 如果想实现深拷贝，需要采用strcpy()函数 PS：通常情况下，还需要malloc()来分配对应足够的内存大小。
 */
