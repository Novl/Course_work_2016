#include <stdio.h>

void menu()
{
	printf("\n---------------------------");
	printf("\n");
	printf("Enter string of digits(number) to add to stack");
    printf("\n\n --CALCULATIONS");
	printf("\n//-------------------");
    printf("\n or \'+\' to get summ of two top numbers");
	printf("\n or \'-\' to get substraction of two top numbers");
	printf("\n or \'*\' to get multiplication of two top numbers");
	printf("\n or \'\\\' to get division of two top numbers");
	printf("\n or \'^\' to pow last number in \'number1\' and mod \'number2\'");
	printf("\n");
	
    printf("\n --Miscellaneous");
    printf("\n//-------------------");
	printf("\n \'I\' to check is top(last) number prime by probability test by GMPLIB");
	printf("\n \'B\' to check is top(last) number prime by my checker");
	printf("\n \'F\' to find primitive root");
	printf("\n \'G\' to generate prime");
	printf("\n");
    
    printf("\n --Op-s with stack");
    printf("\n//-------------------");
    printf("\n \'L\' to get top(last) number");
	printf("\n \'D\' to delete top");
	printf("\n \'A\' to show all stack");
    printf("\n \'W\' to write(append) all stack to file");
    printf("\n \'V\' to write(append) only head of stack to file");
    printf("\n \'R\' to read file and add to stack");
	printf("\n \'M\' to show this menu");
	printf("\n \'E\' to exit\n\n");
}