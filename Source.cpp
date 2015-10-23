#include "headers.h"
#include "stack.h"

using namespace std;

char str[200];
char str1[200];
string input;
stack Stack;


int main()
{		
	menu();
	while  (true) //(scanf("%s", str)>0) 
	{
        cin>>input;
// -- CALCULATIONS --------------------------------------------------------------------
		if (isdigit(input[0]))
        {
            Stack.add(input.c_str(), 10);
        }
		else
		if (input.compare("+")==0)
		{
            Stack.summ();
        }
		else
		if (input.compare("-")==0)
		{
			Stack.sub();
		}
		else
		if (input.compare("*")==0)
		{
			Stack.mul();
		}
		else
		if (input.compare("/")==0)
		{
			Stack.cdiv();
		}
		else
		if (input.compare("^")==0)
		{
			Stack.powm();
		}
//------- Op-s with stack ------------------------------------------------------		
		else
		// Top of stack
		if (input.compare("h")==0)
		{
			Stack.last();
		}
		else
        // Menu
		if (input.compare("m")==0)
		{
            menu();
		}
		else
		// Delete
		if (input.compare("d")==0)
		{
			Stack.del();
		}
		else
        if (input.compare("c")==0)
        {
            Stack.clear();
        }
        else
        // ALL
		if (input.compare("a")==0)
		{
			Stack.show();
		}
		else
        if (input.compare("w")==0)
        {
            Stack.writeAll();
        }
        else
        if (input.compare("v")==0)
        {
            Stack.writeOne();
        }
        else
        if (input.compare("re")==0)
        {
            Stack.read();
        }
        else
//  ----------------------------------------- Miscellanious--------------------------------------------            
		// GMPLIB TEST probable prime
		if (input.compare("gmptp")==0)
		{
			Stack.gmp_test();
		}
        else
        // find primitive root
		if (input.compare("r")==0)
		{
			Stack.root();
		}		
		else
		// My test
		/*
			Показывает разложение числа p-1 на простые числа до 400000 ,
            показывает получившееся произведение и остаток, 
            потом итеративно применяется к остатку.
		*
		if (input.compare("B")==0)
		{
			//mpz_set(result_ad, elementary_divisors(Stack[now], divisors));
			//elementary_divisors(Stack[now], divisors, result_ad);
			mpz_t result_ad[NUM_DIV_2];
			//mpz_init(result_ad);
			for (i=0; i<NUM_DIV_2; i++) mpz_init(result_ad[i]);
			mpz_t result_am[NUM_DIV_2];
			//mpz_init_set_ui(result_am, 1);
			for (i=0; i<NUM_DIV_2; i++) mpz_init_set_ui(result_am[i], 1);
			
			
			mpz_t divisors[NUM_DIV_1][NUM_DIV_2];
			for (i=0;i<NUM_DIV_1;i++) 
				for (j=0;j<NUM_DIV_2;j++)
					mpz_init(divisors[i][j]);
			
			int size_mass[NUM_DIV_1];
			for (i=0;i<NUM_DIV_1;i++)	size_mass[i]=0;
			
			// -- ----------------- prefunction ----------
			
			t=mpz_probab_prime_p(Stack[now-1], 20);
			if (t==2) printf("Definitely prime\n");
				else
					if (t==0) printf("Composite\n");
					else 
					{
						mpz_set(result_ad[0], Stack[now-1]);
						//mpz_sub_ui(result_ad[0], Stack[now-1], 1);
						j=0;
						//-----------------------
						
						printf("Enter \'S\' to next iteration or smth to exit  -  ");
						scanf("%s", str1);
						while (str1[0]=='S')
						{
								if (mpz_cmp_ui(result_ad[j], 2)>0)
								{
									//-------------------------------   function --------------------
									
									gmp_printf("Divisors %Zd-1 :\n", result_ad[j]);
									mpz_sub_ui(result_ad[j], result_ad[j], 1);
									mpz_set(result_ad[j+1], result_ad[j]);
									
									
									for (i=2;i<400000;i++)
									{	
										if (mpz_mod_ui(r, result_ad[j+1], i)==0)
										{
											printf("\nDivisor - %d", i);
											while (mpz_mod_ui(r, result_ad[j+1], i)==0)
											{
												mpz_cdiv_q_ui(result_ad[j+1], result_ad[j+1], i);
												mpz_mul_ui(result_am[j], result_am[j], i);
												printf("*%d", i);
											}
											//mpz_set_ui(divisors[j][size_mass[j]++], i);
										}
									}
									gmp_printf("\n result_ad = %Zd\n result_am = %Zd\n remainder = %Zd\n", result_ad[j], result_am[j], result_ad[j+1]);
								}
								else printf("Remainder is not prime\n");
							
							//mpz_mul(r, result_am[j], result_ad[j+1]);
							//gmp_printf("\n multiplication =  %Zd\n", r);
							printf("\nEnter \'S\' to next iteration or smth to exit  -  ");
							scanf("%s", str1);
							j++;	
						}
						//-----------------------------------     end function- ---------------------
						
					}
			//------------------------   need clear ---------------
		}
		else
        */
        if (input.compare("gs")==0)
        {
            Stack.gen_short_prime();
        }
        else
        if (input.compare("gl")==0)
        {
            Stack.gen_long_prime();
        }
        else
		goto END;
	}
	END:
	//for (i=0;i<SIZE_STACK;i++) mpz_clear(Stack[i]);
	//for (i=0;i<NUM_DIV;i++) mpz_clear(divisors[i]);
	//mpz_clear(result_ad);
	return 0;
}
