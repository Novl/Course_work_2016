#include "../include/headers.h"

void menu()
{
	printf("\n*****************************");
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
	printf("\n \'gmptp\' to check is top(last) number prime by probability test by GMPLIB");
	printf("\n \'b\' to check is top(last) number prime by my checker");
	printf("\n \'r\' to find primitive root");
	printf("\n \'gs\' to generate \'short\' prime");
    printf("\n \'gl\' to generate \'long\' prime");
	printf("\n");
    
    printf("\n --Op-s with stack");
    printf("\n//-------------------");
    printf("\n \'h\' to get top(last) number");
	printf("\n \'d\' to delete top");
    printf("\n \'c\' to clear all stack");
	printf("\n \'a\' to show all stack");
    printf("\n \'w\' to write(append) all stack to file");
    printf("\n \'v\' to write(append) only head of stack to file");
    printf("\n \'re\' to read file and add to stack");
	printf("\n \'m\' to show this menu");
    printf("\n \'sm\' to show short menu");
	printf("\n \'e\' or smth else not in list above to exit");
    printf("\n\n");
};

void short_menu()
{
	printf("\n*****************************");
	printf("\n");

    printf("\n --Miscellaneous");
    printf("\n//-------------------");
	printf("\n \'gmptp\' to check is top(last) number prime by probability test by GMPLIB");
	printf("\n \'b\' to check is top(last) number prime by my checker");
	printf("\n \'r\' to find primitive root");
	printf("\n \'gs\' to generate \'short\' prime");
    printf("\n \'gl\' to generate \'long\' prime");
	printf("\n");
    
	printf("\n \'m\' to show this menu");
    printf("\n \'sm\' to show short menu");
	printf("\n \'e\' or smth else not in list above to exit");
    printf("\n\n");
};