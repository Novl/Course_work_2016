#include "../include/stack.h"
// - ----- -----------------------------------------------------------------------------------------

// !!!!! THE FIRST PRIME SHOULD be '2' !!!!!

void stack::gen_prime()
{
    int mytestlocale = 0;
	long long i, j, number, MAX_DEG, MIN_DEG, all;
    time_t TIMER;
    int MaxNumberOfPrimes = 10000, NumberOfPrimes;
	mpz_t primes[MaxNumberOfPrimes];
	int degs[MaxNumberOfPrimes];
    int DoneProgress;
	mpz_t now;
	mpz_t mult;
    mpz_t variableForRoot;
	mpz_init(now);
	mpz_init(mult);
    mpz_init(variableForRoot);
    mpf_t total_amount, prime_amount, prime_amount_probabilty_test;
    mpf_init_set_ui(total_amount, 0);
    mpf_init_set_ui(prime_amount, 0);
    mpf_init_set_ui(prime_amount_probabilty_test, 0);
    
	char str[250];
	string s;

	FILE *f1;
// reading basic using primes 
    cout<<"Enter name of file or '-' to read default 'primes.txt':";
    scanf("%s",str);
    if (strcmp(str, "-") == 0) 
        strcpy(str, "primes.txt\0");
    f1 = fopen(str, "r");

    mpz_init(primes[0]);
	for (i = 0; i < 10000  && gmp_fscanf(f1,"%Zd\n", primes[i]) > 0 ; ++i) 
    {
        mpz_init(primes[i+1]);
    }
    NumberOfPrimes = i;
    cout<<"Number of readed primes:"<<NumberOfPrimes<<endl;
	fclose(f1);
	
    
	printf("Enter name(path) of file or \'-\' to read options from console:");
	scanf("%s",str);
	if (str[0] != '-' ) 
    {
        ifstream IN(str);
        if (IN.is_open())
            IN>>number>>MAX_DEG>>MIN_DEG>>all;
        IN.close();
    }
    else
    {
        cout<<"Enter number of using primes: ";
        cin>>number;
        cout<<"Enter MAX_DEG: ";
        cin>>MAX_DEG;
        cout<<"Enter MIN_DEG: ";
        cin>>MIN_DEG;
        cout<<"///////////////////////////////"<<endl;
        cout<<"Enter \'3\' to see all checked numbers with options\n";
        cout<<"Enter \'2\' all checked numbers with decomposition and storing\n";
        cout<<"Enter \'1\' to see only primes\n";
        cout<<"Enter \'0\' to see only amount\n";
        cin>>all;
    }
    
    if (MIN_DEG > MAX_DEG) 
        MAX_DEG = MIN_DEG;
    if (number > NumberOfPrimes)
    {
        cout<<"Too many numbers entered(using only permited)"<<endl;
        number = NumberOfPrimes;
    }
    
	printf("Entered number of using primes : %I64d\n", number);
	printf("Entered MAX_DEG : %I64d\n", MAX_DEG);
	printf("Entered MIN_DEG : %I64d\n", MIN_DEG);
	cout<<endl;
    
	for (i = 0; i < number;  ++i) 
        degs[i] = MIN_DEG;	
    j = 0;
    
 //  GENERATION
    DoneProgress = 1;
    TIMER = clock();
    if (all == 0)
    {
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        cout<<"Started - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
    }
	while (j < number)
	{
		j=0;
		while ((degs[j] == MAX_DEG) && (j < number))
		{
			degs[j] = MIN_DEG;
			++j;
		}
        if (all == 0 && j == DoneProgress)
        {
            time_t rawtime;
            struct tm * timeinfo;
            time (&rawtime);
            timeinfo = localtime (&rawtime);
            cout<<"# "<<100*(float)DoneProgress/number<<"%"<<" - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
            time_t TIMER1 = clock() - TIMER;
            TIMER1 = TIMER1/CLOCKS_PER_SEC;
            cout<<"Took time - "<<TIMER1/3600<<" hours:"<<(TIMER1%3600)/60<<" minutes:"<<(TIMER1%3600)%60<<" seconds"<<endl;
    
            ++DoneProgress;
        }
        
		if (j < number)
		{
            mpf_add_ui(total_amount, total_amount, 1);
			++(degs[j]);
			// making number
            mpz_set_ui(now, 1);
			for (i = 0; i < number; ++i)
                if (degs[i] != 0)
                {
                    mpz_pow_ui(mult, primes[i], degs[i]);
                    mpz_mul(now, now, mult);
                }
			mpz_add_ui(now, now, 1);
			if (all >= 2) 
			{
				cout<<"Testing for prime:"<<endl<<now<<endl;
			}
			// done
            
			int t = mpz_probab_prime_p(now, 25);
            
            if (t == 2) 
            {
                if (all >= 2)
                    cout<<"Definitely prime by GMP prob test"<<endl;
            }
            else
            if (t == 1) 
            {
                mpf_add_ui(prime_amount_probabilty_test, prime_amount_probabilty_test, 1);
                if (this->root(variableForRoot, 50, now, number, primes, degs))
                {
                    //comment HERE
                    mpf_add_ui(prime_amount, prime_amount, 1);
                    if (all >= 2)
                    {
                        printf("DEGS:\n");
                        for (i = 0; i < number; ++i) 
                        gmp_printf("%Zd - %d\n", primes[i], degs[i]);
                        printf("Digits(base = 10) = %d\n", mpz_sizeinbase(now,10));
                        printf("Digits(base = 2) = %d\n", mpz_sizeinbase(now,2));
                    }
                    if (all >= 1)
                    {
                        cout<<now<<endl;
                        cout<<"Primitive root:"<<variableForRoot<<endl;;
                        if (mpz_cmp_ui(variableForRoot, 1) == 0)
                        {
                            cout<<endl;
                            cout<<"ERRRRRRRRRRRRRRRRRRRRRRRRROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                            cout<<endl;
                           
                            mytestlocale = 1;
                        }
                    }
                    
                    if (all >= 3)
                    {
                        this->add(now);
                        this->add(variableForRoot);
                        cout<<"New root and number in stack"<<endl;
                        cout<<"Enter kp to seed result of Konyagin-Pomerance test"<<endl;
                        cin>>s;
                        if (s.compare("kp") == 0) KP(now, number, primes, degs);
                    }
                    if (all >= 2)
                    {
                        cout<<"Enter 's' to stop"<<endl;
                        cin>>s;
                        if (s.compare("s") == 0) goto END;
                    }
                }   
                else
                    if (all >= 2)
                        printf("Didn't find primive root\n");
            }
            else
                if (all >= 2)
                    cout<<"Definitely composite"<<endl;
 		}
	}
    END:
    printf("\nEnd of generation\n");
    if (all == 0)
    {
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        cout<<"Ended - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
    }
    cout<<"Number of primes:"<<prime_amount<<endl;
    cout<<"Total:"<<total_amount<<endl;
    mpf_t percent;
    mpf_init(percent);
    if (mpf_cmp_ui(total_amount, 0) > 0)
    {
        mpf_div(percent, prime_amount, total_amount);
        cout<<"Percent of found:"<<percent<<endl;
        mpf_div(percent, prime_amount_probabilty_test, total_amount);
        cout<<"Percent of probable:"<<percent<<endl;
    }
    
    TIMER = clock() - TIMER;
    cout<<"Took time - "<<TIMER/CLOCKS_PER_SEC<<" seconds"<<endl;
    cout<<"Took time - "<<(TIMER/CLOCKS_PER_SEC)/3600<<" hours:"<<((TIMER/CLOCKS_PER_SEC)%3600)/60<<" minutes:"<<((TIMER/CLOCKS_PER_SEC)%3600)%60<<" seconds"<<endl;
    cout<<"mytestlocale = "<<mytestlocale<<endl;
    
    mpf_clear(percent);
	mpz_clear(now);
	mpz_clear(mult);
    mpf_clear(total_amount);
    mpf_clear(prime_amount);
    mpf_clear(prime_amount_probabilty_test);
    for (i = 0; i <= NumberOfPrimes ; ++i) 
        mpz_clear(primes[i]);
}