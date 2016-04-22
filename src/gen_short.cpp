#include "../include/stack.h"
// - ----- -----------------------------------------------------------------------------------------
void stack::gen_short_prime()
{
	long long i, j, number, MAX_DEG, MIN_DEG, all, t;
    int MaxNumberOfPrimes = 10000, NumberOfPrimes;
	mpz_t primes[MaxNumberOfPrimes];
	long long degs[MaxNumberOfPrimes];
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
	char s;

	FILE *f1;
// reading basic using primes 
    cout<<"Enter name of file or '-' to read defaul 'primes.txt':";
    scanf("%s",str);
    if (strcmp(str, "-") == 0) 
        strcpy(str, "primes.txt\0");
    f1 = fopen(str, "r");

	for (i = 0; i < 10000  && gmp_fscanf(f1,"%Zd\n", primes[i]) > 0 ; ++i) 
    {
        mpz_init(primes[i+1]);
    }
    NumberOfPrimes = i;
    cout<<"Number of readed primes:"<<NumberOfPrimes<<endl;
	fclose(f1);
	
    
	printf("Enter \'f\' to read from file \'test.txt\':");
	scanf("%s",str);
	if (str[0] == 'f' ) 
    {
        ifstream IN("test.txt");
        IN>>number>>MAX_DEG>>MIN_DEG>>all;
    }
    else
    {
        cout<<"Enter number of using primes: ";
        cin>>number;
        cout<<"Enter MAX_DEG: ";
        cin>>MAX_DEG;
        cout<<"Enter MIN_DEG: ";
        cin>>MIN_DEG;
        cout<<"\nEnter \'1\' to see all checked numbers or \'0\' to see only primes\n";
        cin>>all;
    }
    
	printf("Entered number of using primes : %I64d\n", number);
	printf("Entered MAX_DEG : %I64d\n", MAX_DEG);
	printf("Entered MIN_DEG : %I64d\n", MIN_DEG);
	cout<<endl;
    
    if (number > NumberOfPrimes)
    {
        cout<<"Too many numbers entered(using only permited)"<<endl;
        number = NumberOfPrimes;
    }
	for (i = 0; i < number;  ++i) 
        degs[i] = MIN_DEG;	
    j = 0;
	while (j < number)
	{
		j=0;
		while ((degs[j] == MAX_DEG) && (j < number))
		{
			degs[j] = MIN_DEG;
			++j;
		}

		if (j < number)
		{
			++(degs[j]);
			// making number
            mpz_set_ui(now, 1);
			for (i = 0; i < number; ++i)
                if (degs[i] != 0)
                {
                    mpz_pow_ui(mult, primes[i], degs[i]);
                    mpz_mul(now, now, mult);
                }
			mpz_add_ui(now1, now, 1);
			if (all == 1) 
			{
				cout<<"Testing for prime:"<<endl<<now1<<endl;
			}
			// done
            
            this->add(now1);
			t = stack::gmp_test();
            
            if (t == 1) 
            {
                if (this->root(50, number, primes))
                {
                    //comment HERE
                    printf("DEGS:\n");
                    for (i = 0; i < number; ++i) 
                    gmp_printf("%Zd - %d\n", primes[i], degs[i]);
                    printf("Digits(base = 10) = %d\n", mpz_sizeinbase(now1,10));
                    printf("Digits(base = 2) = %d\n", mpz_sizeinbase(now1,2));
                    cout<<"New number and root in stack"<<endl;
                    cout<<"Enter 's' to stop"<<endl;
                    cin>>s;
                    if (s == 's') goto END;
                }   
                else
                {
                    printf("Didn't find primive root\n");
                    this->del();
                }
            }
            else
                this->del();
 		}
	}
    END:
    printf("\nEnd of generation\n");
    mpz_clear(var);
	mpz_clear(var1);
	mpz_clear(now);
	mpz_clear(now1);
	mpz_clear(mult);
    for (i = 0; i <= NumberOfPrimes ; ++i) 
        mpz_clear(primes[i]);
}