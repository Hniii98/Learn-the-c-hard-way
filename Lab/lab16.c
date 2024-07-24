#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


struct Person
{
	char *name;
	int age;
	int height;
	int weight;
};

struct Person * Person_create(char *name, int age, int height, int weight)
{
	struct Person *who = malloc(sizeof(struct Person));	
	assert(who != NULL);

	who->name = strdup(name); // dynamic memory
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who)
{
	assert(who != NULL);
	
	free(who->name);
	free(who);
}

void Person_print(struct Person *who)
{
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

void Person_print_woptr(struct Person person)
{
	printf("Name: %s\n", person.name);
	printf("\tAge: %d\n", person.age);
	printf("\tHeight: %d\n", person.height);
	printf("\tWeight: %d\n", person.weight);
}

int main(int argc, char *argv[])
{
	/*
	struct Person *joe = Person_create("Joe Alex", 
						 				32, 64, 140);

	struct Person *frank = Person_create("Frank Blank",
										 20, 72, 180);
	*/
	
	struct Person joe;
	joe.name = strdup("Joe Alex");
	joe.age = 32;
	joe.height = 64;
	joe.weight = 140;
	
	struct Person frank;
	frank.name = strdup("Frank Blank");
	frank.age = 20;
	frank.height = 72;
	frank.weight = 180;


	printf("Joe is at memory location: %p \n",&joe);
	Person_print(&joe);

	printf("Frank is at memory location: %p \n", &frank);
	Person_print(&frank);

	
	joe.age += 20;
	joe.height -= 2;
	joe.weight += 40;
	Person_print(&joe);
	Person_print_woptr(joe);

	frank.age += 20;
	frank.weight += 20;
	Person_print(&frank);

	//Person_destroy(joe);
	//Person_destroy(frank);
	free(joe.name);
	free(frank.name);
	return 0;		
}


/*
 * #1
 * 先声明结构体，但后使用.运算符对结构体的成员进行赋值
 *
 * #2
 *
 * #3
 * 采用传值的方式进行参数传递，注意C语言中没有函数重载的概念，因此需要
 * 避免命名冲突。
