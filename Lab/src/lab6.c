#include <stdio.h>

int main()
{
	int distance =100;
	float power = 2.345f;
	double super_power = 56789.4532;
	char initial = 'A';
	char first_name[] = "Zed";
	char last_name[] = "Shaw";
	int hex_num  = 0x3fff;
	char null_str[] = " ";

	printf("You are %d miles away. \n", distance);
	printf("You are %f levels of power. \n", power);
	printf("You have %f awesome super power. \n", super_power);
	printf("I hava an initial %c. \n", initial);
	printf("I have first name %s. \n", first_name);
	printf("I have a last name %s. \n", last_name);
	printf("My whole name is %s %c. %s.\n",
			first_name, initial, last_name);
	printf("Hex numer:%x. \n", hex_num);
	printf("%s\n", null_str);

	return 0;

}
