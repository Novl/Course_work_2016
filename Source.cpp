#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gmp.h>
#include <gmpxx.h>

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>


#include "menu.h"


using namespace std;

const int SIZE_STACK=40;
const int NUM_DIV_1=200;
const int NUM_DIV_2=100;

char str[200];
char str1[200];

string stream;


/*

void elementary_divisors(const mpz_t* A,  mpz_t* mass,  mpz_t* local)
{
	mpz_set(*local, A);
	mpz_sub_ui(*local, *local, 1);
	
	unsigned long int i;
	int size_mass=0;
	mpz_t r;
	mpz_init(r);
	printf("Divisors %Zd-1 :\n", A);
	for (i=2; i<400000; ++i)
	{	
		if (mpz_mod_ui(r, *local, i)==0)
		{
			while (mpz_mod_ui(r, *local, i)==0)
			{
				printf("Divisor - %d\n", i);
				mpz_cdiv_q_ui(*local, *local, i);
			}
			mpz_set_ui(mass[size_mass++], i);
		}
	}
	
	mpz_clear(r);
}
*/


void gen_prime()
{
    long long i,n,j,number,MAX_DEG,MIN_DEG,all,t;
	mpz_t primes[10000];
	long long degs[10000];
	mpz_t var;
	mpz_t var1;
	mpz_t now;
	mpz_t now1;
	mpz_t mult;
	mpz_init(var);
	mpz_init(var1);
	mpz_init(now);
	mpz_init(now1);
	mpz_init(mult);
	char str[20];
	
	FILE *f1;
	f1=fopen("primes.txt", "r");
	for (i=0; i<10000; ++i) gmp_fscanf(f1,"%Zd\n", primes[i]);
	fclose(f1);
	
	printf("Enter \'f\' to read from file \'test.txt\'  ");
	scanf("%s",str);
	if (str[0]=='f') freopen("test.txt", "r", stdin);
	//freopen("result.txt", "w", stdout);
	//printf("Enter number of using primes : ");
	
	printf("\nEnter number of using primes :");
	scanf("%lld", &number);
	printf("\nEnter MAX_DEG :");
	scanf("%lld", &MAX_DEG);
	printf("\nEnter MIN_DEG :");
	scanf("%lld", &MIN_DEG);
	printf("\nEntered number of using primes : %lld",number);
	printf("\nEntered MAX_DEG : %lld",MAX_DEG);
	printf("\nEntered MIN_DEG : %lld",MIN_DEG);
	
	printf("\n\nEnter \'1\' to see all checked numbers or \'0\' to see only prime ");
	scanf("%d",&all);
	printf("\n");
	
	for (i=0; i<number;  ++i) degs[i]=MIN_DEG;
	
	while (j<number)
	{
		if (all==1) //scanf("%s",str);
            getchar();
		mpz_set_ui(now, 1);
		j=0;
		while ((degs[j]==MAX_DEG) && (j<number))
		{
			degs[j]=MIN_DEG;
			++j;
		}
		
		
		if (j<number)
		{
			++(degs[j]);
			/*
			printf("\n DEGS \n");
			for (i=0; i<number; ++i) gmp_printf("%Zd - %d\n",primes[i],degs[i]);
			*/
			// make number
			for (i=0; i<number; ++i)
			if (degs[i]!=0)
			{
				mpz_pow_ui(mult, primes[i], degs[i]);
				mpz_mul(now, now, mult);
			}
			mpz_add_ui(now1, now, 1);
			if (all==1) 
			{
				gmp_printf("\nTesting for prime : -  %Zd ",now1);
				printf("\n");
			}
			// - done
			t=mpz_probab_prime_p(now1,20);
				if (t==2) gmp_printf("Definitely prime - %Zd\n",now1);
				else
					if (t==0 && all==1) 
                        gmp_printf("Composite - %Zd\n",now1);
                    else
                        if (t==0 && all==0) ;
                        else
                        {
                            gmp_randstate_t	state;
                            gmp_randinit_default(state);
                            
                            int f=0,R=0;
                            mpz_t deg;
                            mpz_init(deg);
                            while (f!=1 && R<10)
                            {
                                f=1;
                                mpz_urandomm(var,state,now);
                                mpz_add_ui(var,var,2);
                                for (i=0; (i<number) && f; i++)
                                if (degs[i]!=0)
                                {	
                                    mpz_cdiv_q(deg,now,primes[i]);
                                    mpz_powm(var1, var , deg, now1);
                                    if (mpz_cmp_ui(var1,1)==0) 
                                        f=0;
                                }
                                mpz_powm(var1, var , now, now1);
                                if (mpz_cmp_ui(var1,1)!=0) 
                                    f=0;
                                if (f==1)
                                {
                                    gmp_printf("\n%Zd - primitive root of \n %Zd = \n =",var,now1);
                                    for (i=0; (i<number) && f; i++)
                                    if (degs[i]!=0)
                                        gmp_printf("%Zd^(%d)*",primes[i],degs[i]);
                                    /*
                                    for (j=0; j<degs[i]; j++)
                                    {	
                                        gmp_printf("%Zd*",primes[i]);
                                    }
                                    */
                                    printf("1+1\n");
                                    printf(" digits = %d\n", mpz_sizeinbase(now1,10));
                                    /*
                                    for (i=0;(i<num_divisors) && f;i++)
                                    {	
                                        mpz_cdiv_q(deg,local,divisors[i]);
                                        gmp_printf("\n%Zd in power of %Zd by module %Zd = 1",var,deg,a[now-1]);
                                    }
                                    */
                                }
                                //else
                                //    if (all==1)
                                //    gmp_printf("\n%Zd is not primitive root",var);
                                R++;
                            }
						if (f!=1 && all==1) 
                            printf("Didn't find primitive root\n");
						gmp_randclear(state);
					}
		}
	}
}










int main()
{	
	unsigned long int i, j, now, t;
	mpz_t variable;
	mpz_t a[SIZE_STACK];
	mpz_t r;
	mpz_init(r);
	
	for (i=0;i<SIZE_STACK;i++) mpz_init(a[i]);
	gmp_randstate_t	state;
	gmp_randinit_default(state);
				
	mpz_init(variable);
	now=0;
	
	
	menu();
	while (scanf("%s", str)>0) 
	{
// -- CALCULATIONS --------------------------------------------------------------------
		if (isdigit(str[0]))
		{
			if (now<SIZE_STACK)
			{
                mpz_set_str(a[now], str, 10);
                now++;
            }
			else
				printf("Stack if full\n");
			
		}
		else
		if (str[0]=='+')
		{
			if (now>1)
			{
				mpz_add(variable, a[now-2], a[now-1]);
				mpz_set(a[now-2], variable);
				now--;
				gmp_printf("Summ of last two numbers is = %Zd\n", variable);
			}
			else
			gmp_printf("Stack have not enough elements\n");
		}
		else
		if (str[0]=='-')
		{
			if (now>1)
			{
				mpz_sub(variable, a[now-2], a[now-1]);
				mpz_set(a[now-2], variable);
				now--;
				gmp_printf("Subtraction of last two numbers is = %Zd\n", variable);
			}
			else
			gmp_printf("Stack have not enough elements\n");
		}
		else
		if (str[0]=='*')
		{
			if (now>1)
			{
				mpz_mul(variable, a[now-2], a[now-1]);
				mpz_set(a[now-2], variable);
				now--;
				gmp_printf("Multiplication of last two numbers is = %Zd\n", variable);
			}
			else
			gmp_printf("Stack have not enough elements\n");
		}
		else
		if (str[0]=='/')
		{
			if (now>1)
			{
				mpz_cdiv_q(variable, a[now-2], a[now-1]);
				mpz_set(a[now-2], variable);
				now--;
				gmp_printf("Division of last two numbers is = %Zd\n", variable);
			}
			else
			gmp_printf("Stack have not enough elements\n");
		}
		else
		if (str[0]=='^')
		{
			if (now>0)
			{
				mpz_t module;
				mpz_t exp;
				mpz_init(exp);
				mpz_init(module);
				gmp_printf("Enter exp :\n");
				gmp_scanf("%Zd", exp);
				gmp_printf("Enter module :\n");
				gmp_scanf("%Zd", module);
				mpz_powm(variable,  a[now-1] ,  exp,  module);
				gmp_printf("\n%Zd\n in power \n%Zd\nmod\n%Zd\n=%Zd\n", a[now-1], exp, module, variable);
				mpz_set(a[now-1], variable);
			}
			else printf("Stack is empty\n");
		}
//------- Op-s with stack ------------------------------------------------------		
		else
		// Top of stack
		if (str[0]=='L')
		{
			if (now>0)
                gmp_printf("Last number is  = %Zd\n", a[now-1]);
			else
                gmp_printf("Stack is clear\n");
		}
		else
        // Menu
		if (str[0]=='M')
		{
            menu();
		}
		else
		// Delete
		if (str[0]=='D')
		{
			if (now>0)
            {
                mpz_set_ui(a[now-1], 0);
				now--;
            }
			else
				printf("Stack is empty\n");
		}
		else
        // ALL
		if (str[0]=='A')
		{
			printf("\nAll stack from bottom : \n");
			for (i=0;i<now;i++)
			gmp_printf("%Zd\n", a[i]);
		}
		else
        if (str[0]=='W')
        {
            fstream OUT;
            printf("Enter name(path) of file\n");
            cin>>stream;
            OUT.open(stream.c_str(),fstream::app | fstream::out);
            for (i=now; i>0; i--)
                OUT<<a[i-1]<<endl;
            OUT.close();
        }
        else
        if (str[0]=='V')
        {
            fstream OUT;
            printf("Enter name(path) of file\n");
            cin>>stream;
            OUT.open(stream.c_str(),fstream::app | fstream::out);
            OUT<<a[now-1]<<endl;
            OUT.close();
        }
        else
        if (str[0]=='S')
        {
            ifstream IN;
            printf("Enter name(path) of file\n");
            cin>>stream;
            IN.open(stream.c_str());
            while (!IN.eof() && IN.good() && now<SIZE_STACK)
            {
                cin>>a[now];
                //cin>>variable;
                //mpz_set(a[now],variable);
                now++;
            }
            IN.close();
        }
        else
//  ----------------------------------------- Miscellanious--------------------------------------------            
		// GMPLIB TEST probable prime
		if (str[0]=='I')
		{
			if (now>0)
			{
				t=mpz_probab_prime_p(a[now-1], 20);
				if (t==2) printf("Definitely prime\n");
				else
					if (t==1) printf("Undetermined\n");
					else printf("Composite\n");
			}
			else
			gmp_printf("Stack is clear\n");
		}
        else
        // find primitive root
		if (str[0]=='F')
		{
			int FLAG = 0;
			cout << "Enter '1' to see result one by one or '0' to skip" << endl;
			cin >> FLAG;
			if (now>0)
			{
				int num_divisors=0;
				mpz_t divisors[NUM_DIV_1];
				for (i=0;i<NUM_DIV_1;i++) 
						mpz_init(divisors[i]);

				mpz_t local;
				mpz_init_set(local, a[now-1]);
				mpz_sub_ui(local, local, 1);
				for (i=2;i<400000;i++)
				{	
					if (mpz_mod_ui(r, local, i)==0)
					{
						while (mpz_mod_ui(r, local, i)==0)
							mpz_cdiv_q_ui(local, local, i);
						mpz_set_ui(divisors[num_divisors], i);
						++num_divisors;
					}
				}
				int f=0, R=0;
				mpz_t variable1;
				mpz_init(variable1);
				mpz_t deg;
				mpz_init(deg);
				
				mpz_sub_ui(local, a[now-1], 1);
				
				while (f!=1 && R<100)
				{
					f=1;
					mpz_sub_ui(variable,  a[now-1], 1); // p-1
					mpz_urandomm(variable,  state,  variable); // from 0 to p-2 
					mpz_add_ui(variable,  variable,  1); // from 1 to p-1
					for (i=0;(i<num_divisors) && f;i++)
					{	
						mpz_cdiv_q(deg,  local, divisors[i]);
						mpz_powm(variable1,  variable ,  deg,  a[now-1]);
						if (mpz_cmp_ui(variable1, 1)==0) f=0;
					}
					if (f==1)
					{
						gmp_printf("\n%Zd - primitive root of %Zd", variable, a[now-1]);
						for (i=0;(i<num_divisors) && f;i++)
						{	
							mpz_cdiv_q(deg, local, divisors[i]);
							mpz_powm(variable1, variable , deg, a[now-1]);
							gmp_printf("\n%Zd in power of %Zd by module %Zd =  %Zd", variable, deg, a[now-1], variable1);
						}
					}
					else
					gmp_printf("\n%Zd is not primitive root", variable);
					printf("\n");
					if (FLAG == 1)
					//cin >> EMPTY_VARIABLE;
					getchar();
					R++;
				}
			}
			else 
				cout<<"Stack is empty\n";
		}		
		else
		// My test
		/*
			Показывает разложение числа p-1 на простые числа до 400000 ,
            показывает получившееся произведение и остаток, 
            потом итеративно применяется к остатку.
		*/
		if (str[0]=='B')
		{
			//mpz_set(result_ad, elementary_divisors(a[now], divisors));
			//elementary_divisors(a[now], divisors, result_ad);
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
			
			t=mpz_probab_prime_p(a[now-1], 20);
			if (t==2) printf("Definitely prime\n");
				else
					if (t==0) printf("Composite\n");
					else 
					{
						mpz_set(result_ad[0], a[now-1]);
						//mpz_sub_ui(result_ad[0], a[now-1], 1);
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
        if (str[0]=='G')
        {
            gen_prime();
        }
        else
		goto END;
	}
	
	END:
	gmp_randclear(state);
	for (i=0;i<SIZE_STACK;i++) mpz_clear(a[i]);
	//for (i=0;i<NUM_DIV;i++) mpz_clear(divisors[i]);
	mpz_clear(variable);
	//mpz_clear(result_ad);
	return 0;
}
