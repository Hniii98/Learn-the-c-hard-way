#include <stdio.h>

int main(int argc, char* argv[])
{
	/*
	 * 将int类型赋值给char会发生隱式转换
	 * 其中2，3的ASCII码对应的是控制字符
	 * 打印时不会显示为可见字符
	 * 然而将char赋值给int时，int根据ASCII码
	 * 表隐式转换为对应的字符（0-255范围内）
	 * 
	 *int numbers[4] = {0, 'a', 'a', 'a'};
	 *char name[4] = {'a', 2, 3, 3}; 
	*/
	char name[4] = {'a', 'b'};
	int numbers[4] = {0, 'a', 'a', 'a'};
	
	printf("numbers: %d %d %d %d\n",
			numbers[0], numbers[1],
			numbers[2], numbers[3]);

	printf("name each: %c %c %c %c \n",
			name[0], name[1],
			name[2], name[3]);

	printf("name:%s\n",name);

	numbers[0] = 1;
	numbers[1] = 2;
	numbers[2] = 3;
	numbers[3] = 4;

	name[0] = 'Z';
	name[1] = 'e';
	name[2] = 'd';
	name[3] = '\0';

	char* another = "Zed";

	printf("another: %s \n", another);
	
	printf("anthoner each: %c %c %c %c\n",
			another[0], another[1],
			another[2], another[3]);

	printf("name : %c", *( name + 1));
	return 0;
}
