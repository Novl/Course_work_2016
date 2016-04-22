#include "../include/stack.h"
// - ----- -----------------------------------------------------------------------------------------
void stack::gen_short_prime()
{
	long long i, j, number, MAX_DEG, MIN_DEG, all, t;
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
	char str[250];
	string S;
    
	FILE *f1;
// reading basic using primes 
    cout<<"Enter name of file or '-' to read defaul 'primes.txt':";
    scanf("%s",str);
    if (strcmp(str, "-") == 0) 
        strcpy(str,  "primes.txt\0");
    
    f1 = fopen(str, "r");
	for (i=0; i<10000; ++i) 
    {
        mpz_init(primes[i]);
        gmp_fscanf(f1,"%Zd\n", primes[i]);
    }
	fclose(f1);
	
    
	printf("Enter \'f\' to read from file \'test.txt\'\n  ");
	scanf("%s",str);
	if (str[0]=='f') freopen("test.txt", "r", stdin);
	//freopen("result.txt", "w", stdout);
	//printf("Enter number of using primes : ");
	
	cout<<"Enter number of using primes: ";
    cin>>number;
	cout<<"Enter MAX_DEG: ";
	cin>>MAX_DEG;
	cout<<"Enter MIN_DEG: ";
	cin>>MIN_DEG;
    
	printf("Entered number of using primes : %lld\n",number);
	printf("Entered MAX_DEG : %lld\n",MAX_DEG);
	printf("Entered MIN_DEG : %lld\n",MIN_DEG);
	
	cout<<"\nEnter \'1\' to see all checked numbers or \'0\' to see only prime\n";
	cin>>all;
	cout<<endl;
    
	for (i=0; i<number;  ++i) degs[i]=MIN_DEG;	
    j=0;
	while (j<number)
	{
		j=0;
		while ((degs[j]==MAX_DEG) && (j<number))
		{
			degs[j]=MIN_DEG;
			++j;
		}

		if (j<number)
		{
			++(degs[j]);
			//comment HERE
			printf("\n DEGS \n");
			for (i=0; i<number; ++i) gmp_printf("%Zd - %d\n",primes[i],degs[i]);
			
			// make number
            mpz_set_ui(now, 1);
			for (i=0; i<number; ++i)
                if (degs[i]!=0)
                {
                    mpz_pow_ui(mult, primes[i], degs[i]);
                    mpz_mul(now, now, mult);
                }
			mpz_add_ui(now1, now, 1);
			if (all==1) 
			{
				cout<<"Testing for prime: "<<now1;
			}
			// done
			t=mpz_probab_prime_p(now1,20);
            if ((t==2) && all) 
                cout<<" - Definitely prime"<<endl;
            else
                if ((t==0) && all) 
                    cout<<" - Composite: "<<endl;
                else
                {
                    gmp_randstate_t	NewState;
                    gmp_randinit_default(NewState);
                    
                    int f=0,R=0;
                    mpz_t deg;
                    mpz_init(deg);
                    while (f!=1 && R<50)
                    {
                        f=1;
                        mpz_urandomm(var, NewState, now);
                        mpz_add_ui(var, var, 2);
                        for (i=0; (i<number) && f; i++)
                        if (degs[i]!=0)
                        {	
                            mpz_cdiv_q(deg,now,primes[i]);
                            mpz_powm(var1, var , deg, now1);
                            if (mpz_cmp_ui(var1, 1)==0) f=0;
                        }
                        mpz_powm(var1, var , now, now1);
                        if (mpz_cmp_ui(var1,1)!=0) f=0;
                        if (f==1)
                        {
                            gmp_printf("\n%Zd - primitive root of \n %Zd = \n =",var,now1);
                            for (i=0; (i<number-1) && f; i++)
                                if (degs[i]!=0)
                                    gmp_printf("%Zd^(%d)*", primes[i], degs[i]);
                                gmp_printf("%Zd^(%d)\n", primes[i], degs[i]);
                            /*
                            for (j=0; j<degs[i]; j++)
                            {	
                                gmp_printf("%Zd*",primes[i]);
                            }
                            */
                            //printf("1+1\n");
                            printf("Digits(base = 10) = %d\n", mpz_sizeinbase(now1,10));
                            printf("Digits(base = 2) = %d\n", mpz_sizeinbase(now1,2));
                            cout<<"New number is here."<<endl;
                            
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
                    if (f!=1)
                        printf("Didn't find primive root\n");
                    else
                    {
                        cout<<"If want to store press \'s\'"<<endl;
                        cin>>S;
                        if (S.compare("s") == 0)
                            this->add(now1);
                        cout<<"Enter \'e\' to exit"<<endl;
                        cin>>S;
                        if (S.compare("e") == 0)
                            goto END;
                    }
                }
		}
	}
    END:
    printf("\nEnd of generation\n");
}