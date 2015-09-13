#include <gmp.h>
#include <stdio.h>


int main()
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
		if (all==1) scanf("%s",str);
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
			/// make number
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
			/// - done
			t=mpz_probab_prime_p(now1,20);
				if ((t==2) && all) gmp_printf("Definitely prime - %Zd\n",now1);
				else
					if ((t==0) && all) ;//gmp_printf("Composite - %Zd\n",now1);
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
								if (mpz_cmp_ui(var1,1)==0) f=0;
							}
							mpz_powm(var1, var , now, now1);
							if (mpz_cmp_ui(var1,1)!=0) f=0;
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
							//gmp_printf("\n%Zd is not primitive root",var);
							R++;
						}
						//if (f!=1) printf("Didn't find primive root\n");
						gmp_randclear(state);
					}
		}
	}
	return 0;
}