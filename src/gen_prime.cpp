#include "../include/stack.h"
// - ----- -----------------------------------------------------------------------------------------

// !!!!! FIRST PRIME SHOULD be '2' !!!!!

const int MAX_TRIES = 20;

void stack::gen_prime()
{
    ofstream REPORT("report.txt", ofstream::out);
    time_t TIMER, TIMER1, rawtime;
    struct tm * timeinfo;
    
    int ERRORlocale = 0;
	int i, j;
    int number = 0, MAX_DEG = 0, MIN_DEG = 0, all = 0;
    int MaxNumberOfPrimes = 100000, NumberOfPrimes = 0;
	int degs[MaxNumberOfPrimes];
    int DoneProgress;
    
    mpz_t primes[MaxNumberOfPrimes];
	mpz_t now; // assumed prime
	mpz_t mult;
    mpz_t variableForRoot;
    mpf_t total_amount, prime_amount, prime_amount_probabilty_test;
    mpf_t percent;
     
	mpz_init(now);
	mpz_init(mult);
    mpz_init(variableForRoot);
    mpf_init_set_ui(total_amount, 0);
    mpf_init_set_ui(prime_amount, 0);
    mpf_init_set_ui(prime_amount_probabilty_test, 0);
    mpf_init(percent);
   
    
	char str[250];
	string s;

	
// reading basic using primes 
    {
        FILE *f1;
        cout<<"Enter name of file or '-' to read default 'primes.txt':";
        cin>>str;
        if (strcmp(str, "-") == 0) 
            strcpy(str, "primes.txt\0");
        f1 = fopen(str, "r");
        if (f1 == NULL) 
        {
            cout<<"No such file"<<endl;
            return;
        }
        
        mpz_init(primes[0]);
        for (i = 0; i < MaxNumberOfPrimes  && gmp_fscanf(f1,"%Zd\n", primes[i]) > 0 ; ++i) 
        {
            mpz_init(primes[i+1]);
        }
        
        NumberOfPrimes = i;
        cout<<"Number of readed primes:"<<NumberOfPrimes<<endl;
        REPORT<<"Number of readed primes:"<<NumberOfPrimes<<endl;
        fclose(f1);
    }
	
// reading parametrs:
// number - amount of using primes
// MAX_DEG, MIN_DEG,
// all - parametr for specific output
    {
        cout<<"Enter name(path) of file or \'-\' to read options from console:";
        cin>>str;
        if (strcmp(str, "-") != 0)  
        {
            ifstream IN(str, ifstream::in);
            if (IN.is_open())
                IN>>number>>MIN_DEG>>MAX_DEG>>all;
            IN.close();
        }
        else
        {
            cout<<"Enter number of using primes: ";
            cin>>number;
            cout<<"Enter MIN_DEG: ";
            cin>>MIN_DEG;
            cout<<"Enter MAX_DEG: ";
            cin>>MAX_DEG;
            cout<<"///////////////////////////////"<<endl;
            cout<<"Enter \'3\' to see all checked numbers with options\n";
            cout<<"Enter \'2\' all checked numbers with decomposition and storing\n";
            cout<<"Enter \'1\' to see only primes with roots(without storing and pauses)\n";
            cout<<"Enter \'0\' to see only amount\n";
            cin>>all;
        }
    }
 

// check 
    if (MIN_DEG > MAX_DEG) 
        MAX_DEG = MIN_DEG;
    if (number > NumberOfPrimes)
    {
        cout<<"Too many numbers entered(using only permited)"<<endl;
        number = NumberOfPrimes;
    }
    
// printing out
	cout<<"Entered number of using primes :"<<number<<endl;
	cout<<"Entered MIN_DEG :"<<MIN_DEG<<endl;
    cout<<"Entered MAX_DEG :"<<MAX_DEG<<endl;
	cout<<endl;
    
    REPORT<<"Entered number of using primes :"<<number<<endl;
	REPORT<<"Entered MIN_DEG :"<<MIN_DEG<<endl;
    REPORT<<"Entered MAX_DEG :"<<MAX_DEG<<endl;
    REPORT<<endl;
    
// initialization
    {
        for (i = 0; i < number;  ++i) 
            degs[i] = MIN_DEG;	
        j = 0;
        DoneProgress = 1;
        TIMER = clock();
        
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        REPORT<<"Started - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
        if (all >= 0)
        {
            cout<<"Started - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;   
        }
    }
 //  GENERATION
	while (j < number)
	{
		j=0;
		while ((degs[j] == MAX_DEG) && (j < number))
		{
			degs[j] = MIN_DEG;
			++j;
		}
        if (all >= 0 && j == DoneProgress)
        {
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            cout<<"# "<<100*(float)DoneProgress/number<<"%"<<" - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
            REPORT<<"# "<<100*(float)DoneProgress/number<<"%"<<" - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
            
            TIMER1 = clock() - TIMER;
            TIMER1 = TIMER1/CLOCKS_PER_SEC;
            cout<<"Took time - "<<TIMER1/3600<<" hours:"<<(TIMER1%3600)/60<<" minutes:"<<(TIMER1%3600)%60<<" seconds"<<endl;
            REPORT<<"Took time - "<<TIMER1/3600<<" hours:"<<(TIMER1%3600)/60<<" minutes:"<<(TIMER1%3600)%60<<" seconds"<<endl;
            
            mpf_div(percent, prime_amount, total_amount);
            cout<<"Percent of found:"<<percent<<endl;
            REPORT<<"Percent of found:"<<percent<<endl;
            
            mpf_div(percent, prime_amount_probabilty_test, total_amount);
            cout<<"Percent of probable:"<<percent<<endl;
            REPORT<<"Percent of probable:"<<percent<<endl;
            
            ++DoneProgress;
        }
        
		if (j < number)
		{
            mpf_add_ui(total_amount, total_amount, 1);
			++(degs[j]);
			// making new number
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
				cout<<"Testing for prime: "<<now<<endl;
                REPORT<<"Testing for prime: "<<now<<endl;
			}
			// done N = now
            
			int t = mpz_probab_prime_p(now, 25);
            
            if (t == 2) 
            {
                mpf_add_ui(prime_amount_probabilty_test, prime_amount_probabilty_test, 1);
                mpf_add_ui(prime_amount, prime_amount, 1);
                REPORT<<"Definitely prime by GMP prob test"<<endl;
                if (all >= 2)
                {
                    cout<<"Definitely prime by GMP prob test"<<endl;
                }
            }
            else
            if (t == 1) 
            {
                mpf_add_ui(prime_amount_probabilty_test, prime_amount_probabilty_test, 1);
                if (this->root(variableForRoot, MAX_TRIES, now, number, primes, degs))
                {
                    //comment HERE
                    mpf_add_ui(prime_amount, prime_amount, 1);
                    REPORT<<"DEGS:"<<endl;
                    for (i = 0; i < number; ++i) 
                    {
                        if (degs[i] > 0)
                            REPORT<<primes[i]<<" - "<<degs[i]<<endl;
                    }
                    REPORT<<"Digits(base = 10) = "<<mpz_sizeinbase(now, 10)<<endl;
                    REPORT<<"Digits(base = 2) = "<<mpz_sizeinbase(now, 2)<<endl;
                    
                    if (all >= 2)
                    {
                        cout<<"DEGS:"<<endl;
                        for (i = 0; i < number; ++i) 
                        {
                            if (degs[i] > 0)
                                cout<<primes[i]<<" - "<<degs[i]<<endl;
                        }
                        cout<<"Digits(base = 10) = "<<mpz_sizeinbase(now, 10)<<endl;
                        cout<<"Digits(base = 2) = "<<mpz_sizeinbase(now, 2)<<endl;
                    }
                    
                    REPORT<<"Primitive root: "<<variableForRoot<<endl<<endl;
                    
                    if (all == 1)
                    {
                        cout<<now<<endl;
                        cout<<"Primitive root:"<<variableForRoot<<endl;
                    }
                    if (mpz_cmp_ui(variableForRoot, 1) == 0)
                    {
                        cout<<endl;
                        cout<<"ERRRRRRRRRRRRRRRRRRRRRRRRROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        cout<<endl;
                       
                        REPORT<<endl;
                        REPORT<<"ERRRRRRRRRRRRRRRRRRRRRRRRROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        REPORT<<endl;
                        
                        ERRORlocale = 1;
                    }
                    
                    
                    if (all >= 3)
                    {
                        cout<<"Enter 's' to store new number and root"<<endl;
                        cin>>s;
                        if (s.compare("s") == 0)
                        {
                            this->add(now);
                            this->add(variableForRoot);    
                            cout<<"New root and number in stack"<<endl;
                        }
                        
                        cout<<"Enter 'k' to seed result of Konyagin-Pomerance test"<<endl;
                        cin>>s;
                        if (s.compare("k") == 0) 
                        {
                            if (KP(now, number, primes, degs))
                            {
                                cout<<"KP-prime"<<endl;
                                REPORT<<"KP-prime"<<endl;
                            }
                            else
                            {
                                cout<<"KP-composite"<<endl;
                                REPORT<<"KP-composite"<<endl;   
                            }
                        }
                    }
                    if (all >= 2)
                    {
                        cout<<"Enter 's' to stop"<<endl;
                        cin>>s;
                        if (s.compare("s") == 0) goto END;
                    }
                }   
                else
                {
                    REPORT<<"Didn't find primitive root"<<endl;
                    if (all >= 2)
                    {
                        printf("Didn't find primive root\n");
                        
                    }
                }
            }
            else
                if (all >= 2)
                {
                    cout<<"Definitely composite"<<endl;
                    REPORT<<"Definitely composite"<<endl;
                }
 		}
	}
    END:
    cout<<endl<<"End of generation"<<endl;
    REPORT<<endl<<"End of generation"<<endl;
    
    if (all >= 0)
    {
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        cout<<"Ended - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
        REPORT<<"Ended - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
    }
    
    cout<<"Number of primes:"<<prime_amount<<endl;
    cout<<"Total:"<<total_amount<<endl;
    
    REPORT<<"Number of primes:"<<prime_amount<<endl;
    REPORT<<"Total:"<<total_amount<<endl;
    
    if (mpf_cmp_ui(total_amount, 0) > 0)
    {
        mpf_div(percent, prime_amount, total_amount);
        cout<<"Percent of found:"<<percent<<endl;
        REPORT<<"Percent of found:"<<percent<<endl;
        mpf_div(percent, prime_amount_probabilty_test, total_amount);
        cout<<"Percent of probable:"<<percent<<endl;
        REPORT<<"Percent of probable:"<<percent<<endl;
    }
    
    TIMER = clock() - TIMER;
    cout<<"Took time - "<<TIMER/CLOCKS_PER_SEC<<" seconds"<<endl;
    cout<<"Took time - "<<(TIMER/CLOCKS_PER_SEC)/3600<<" hours:"<<((TIMER/CLOCKS_PER_SEC)%3600)/60<<" minutes:"<<((TIMER/CLOCKS_PER_SEC)%3600)%60<<" seconds"<<endl;
    cout<<"ERRORlocale = "<<ERRORlocale<<endl;
    REPORT<<"Took time - "<<TIMER/CLOCKS_PER_SEC<<" seconds"<<endl;
    REPORT<<"Took time - "<<(TIMER/CLOCKS_PER_SEC)/3600<<" hours:"<<((TIMER/CLOCKS_PER_SEC)%3600)/60<<" minutes:"<<((TIMER/CLOCKS_PER_SEC)%3600)%60<<" seconds"<<endl;
    REPORT<<"ERRORlocale = "<<ERRORlocale<<endl;
    
    
    mpf_clear(percent);
	mpz_clear(now);
	mpz_clear(mult);
    mpz_clear(variableForRoot);
    mpf_clear(total_amount);
    mpf_clear(prime_amount);
    mpf_clear(prime_amount_probabilty_test);
    for (i = 0; i <= NumberOfPrimes ; ++i) 
        mpz_clear(primes[i]);
    REPORT.close();
}

void stack::gen_primes_file()
{
    ofstream REPORT("report.txt", ofstream::out);
    ofstream GENERATED("generatedPrimes.txt", ofstream::app);
    time_t TIMER, TIMER1, rawtime;
    struct tm * timeinfo;
    
    int amount;
    unsigned int size_bits;
    int ERRORlocale = 0;
	int i, j, t, flag;
    int number = 0;
    int MaxNumberOfPrimes = 100000, NumberOfPrimes = 0;
	int* degs = (int*)calloc(MaxNumberOfPrimes, sizeof(int));
    int DoneProgress = 0;
    
    mpz_t* primesBase = (mpz_t*)calloc(MaxNumberOfPrimes, sizeof(mpz_t));
    mpz_t primesUsed[MaxNumberOfPrimes];
	mpz_t now; // assumed prime
    mpz_t variableForRoot;
     
	mpz_init(now);
    mpz_init(variableForRoot);   
    
	char str[250];
	
    cout<<"Enter number of primes:";
    cin>>amount;
    cout<<"Enter the min number of bits in numbers:";
    cin>>size_bits;
    
// reading basic using primes 
    {
        FILE *f1;
        strcpy(str, "primes.txt\0");
        f1 = fopen(str, "r");
        if (f1 == NULL) 
        {
            cout<<"No such file"<<endl;
            return;
        }
        
        mpz_init(primesBase[0]);
        mpz_init(primesUsed[0]);
        for (i = 0; i < MaxNumberOfPrimes  && gmp_fscanf(f1,"%Zd\n", primesBase[i]) > 0 ; ++i) 
        {
            mpz_init(primesBase[i+1]);
            mpz_init(primesUsed[i+1]);
        }
        NumberOfPrimes = i;
        fclose(f1);
    }
	
// initialization
    {
    TIMER = clock();
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    REPORT<<"Started - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
    cout<<"Started - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
    }
 //  GENERATION
    while (DoneProgress < amount)
    {
        j = 0;
        mpz_set_ui(now, 2);
        while (mpz_sizeinbase(now, 2) < size_bits && MaxNumberOfPrimes >  j)
        {
            i = rand() % NumberOfPrimes;
            mpz_set(primesUsed[j], primesBase[i]); 
            mpz_mul(now, now, primesUsed[j]);
            degs[j] = 1;
            ++j;
        }

        if (j > MaxNumberOfPrimes) return;
        
        flag = 0;
        while (flag == 0 && MaxNumberOfPrimes > j && mpz_sizeinbase(now, 10) < 3000)
        {
            mpz_add_ui(now, now, 1);
            cout<<"Trying:"<<now<<endl;
            REPORT<<"Trying:"<<now<<endl;
            t = mpz_probab_prime_p(now, 25);
            if (t == 2) 
            {
                GENERATED<<now<<endl;
                flag = 1;
                ++DoneProgress;
            }
            else
            if (t == 1) 
            {
                if (this->root(variableForRoot, MAX_TRIES, now, j, primesUsed, degs))
                {
                    //comment HERE
                    GENERATED<<now<<endl;
                    ++DoneProgress;
                    flag = 1;
                    
                    REPORT<<now<<endl;
                    REPORT<<"DEGS:"<<endl;
                    for (i = 0; i < number; ++i) 
                    {
                        if (degs[i] > 0)
                            REPORT<<primesUsed[i]<<" - "<<degs[i]<<endl;
                    }
                    REPORT<<"Digits(base = 10) = "<<mpz_sizeinbase(now, 10)<<endl;
                    REPORT<<"Digits(base = 2) = "<<mpz_sizeinbase(now, 2)<<endl;
                    REPORT<<"Primitive root: "<<variableForRoot<<endl<<endl;
                    
                    if (mpz_cmp_ui(variableForRoot, 1) == 0)
                    {
                        cout<<endl;
                        cout<<"ERRRRRRRRRRRRRRRRRRRRRRRRROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        cout<<endl;
                       
                        REPORT<<endl;
                        REPORT<<"ERRRRRRRRRRRRRRRRRRRRRRRRROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        REPORT<<endl;
                        
                        ERRORlocale = 1;
                    }
                    if (mpz_sizeinbase(now, 10) < 100)
                    {
                        if (KP(now, j, primesUsed, degs))
                        {
                            REPORT<<"KP-prime"<<endl;
                        }
                        else
                        {
                            cout<<"KP-composite"<<endl;
                            ERRORlocale = 1;
                            REPORT<<"KP-composite"<<endl;   
                        }
                    }
                }   
                else
                {
                    REPORT<<"Didn't find primitive root"<<endl;
                }
            }
            
            if (flag == 1)
            {
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                cout<<"# "<<100*(float)DoneProgress/amount<<"%"<<" - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
                REPORT<<"# "<<100*(float)DoneProgress/amount<<"%"<<" - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
                
                TIMER1 = clock() - TIMER;
                TIMER1 = TIMER1/CLOCKS_PER_SEC;
                cout<<"Took time - "<<TIMER1/3600<<" hours:"<<(TIMER1%3600)/60<<" minutes:"<<(TIMER1%3600)%60<<" seconds"<<endl;
                REPORT<<"Took time - "<<TIMER1/3600<<" hours:"<<(TIMER1%3600)/60<<" minutes:"<<(TIMER1%3600)%60<<" seconds"<<endl;
               
                ++DoneProgress;
            }
            else
            {
                mpz_sub_ui(now, now, 1);
                i = rand() % NumberOfPrimes;
                mpz_set(primesUsed[j], primesBase[i]); 
                mpz_mul(now, now, primesUsed[j]);
                degs[j] = 1;
                ++j;
            }
 		}
	}
    cout<<endl<<"End of generation"<<endl;
    REPORT<<endl<<"End of generation"<<endl;
    
    {
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        cout<<"Ended - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
        REPORT<<"Ended - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
    }
    
    TIMER = clock() - TIMER;
    cout<<"Took time - "<<TIMER/CLOCKS_PER_SEC<<" seconds"<<endl;
    cout<<"Took time - "<<(TIMER/CLOCKS_PER_SEC)/3600<<" hours:"<<((TIMER/CLOCKS_PER_SEC)%3600)/60<<" minutes:"<<((TIMER/CLOCKS_PER_SEC)%3600)%60<<" seconds"<<endl;
    cout<<"ERRORlocale = "<<ERRORlocale<<endl;
    REPORT<<"Took time - "<<TIMER/CLOCKS_PER_SEC<<" seconds"<<endl;
    REPORT<<"Took time - "<<(TIMER/CLOCKS_PER_SEC)/3600<<" hours:"<<((TIMER/CLOCKS_PER_SEC)%3600)/60<<" minutes:"<<((TIMER/CLOCKS_PER_SEC)%3600)%60<<" seconds"<<endl;
    REPORT<<"ERRORlocale = "<<ERRORlocale<<endl;
    
    free(degs);
	mpz_clear(now);
    mpz_clear(variableForRoot);
    for (i = 0; i <= NumberOfPrimes ; ++i) 
    {
        mpz_clear(primesBase[i]);
        mpz_clear(primesUsed[i]);
    }
    REPORT.close();
    GENERATED.close();
}

void stack::gen_prime_testing(mpf_t uns, const mpz_t* primes, const int num_primes, const int MIN_DEG, const int MAX_DEG)
{
    ofstream REPORT("report.txt", ofstream::app);
    ofstream GENERATED("generatedPrimesTest().txt", ofstream::app);
    time_t TIMER, TIMER1, rawtime;
    struct tm * timeinfo;
    
    int ERRORlocale = 0;
	int i, j;
	int degs[num_primes];
    int DoneProgress;
    
	mpz_t now; // assumed prime
	mpz_t mult;
    mpz_t variableForRoot;
    mpf_t total_amount, prime_amount, prime_amount_probabilty_test;
    mpf_t percent;
     
	mpz_init(now);
	mpz_init(mult);
    mpz_init(variableForRoot);
    mpf_init_set_ui(total_amount, 0);
    mpf_init_set_ui(prime_amount, 0);
    mpf_init_set_ui(prime_amount_probabilty_test, 0);
    mpf_init(percent);
    
    REPORT<<"Entered number of using primes :"<<num_primes<<endl;
	REPORT<<"Entered MIN_DEG :"<<MIN_DEG<<endl;
    REPORT<<"Entered MAX_DEG :"<<MAX_DEG<<endl;
    REPORT<<endl;
    
// initialization
    {
        for (i = 0; i < num_primes;  ++i) 
            degs[i] = MIN_DEG;	
        j = 0;
        DoneProgress = 1;
        TIMER = clock();
        
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        REPORT<<"Started - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
        //cout<<"Started - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
    }
 //  GENERATION
	while (j < num_primes)
	{
		j=0;
		while ((degs[j] == MAX_DEG) && (j < num_primes))
		{
			degs[j] = MIN_DEG;
			++j;
		}
        
        if (j == DoneProgress)
        {
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            //cout<<"# "<<100*(float)DoneProgress/num_primes<<"%"<<" - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
            REPORT<<"# "<<100*(float)DoneProgress/num_primes<<"%"<<" - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
            
            TIMER1 = clock() - TIMER;
            TIMER1 = TIMER1/CLOCKS_PER_SEC;
            //cout<<"Took time - "<<TIMER1/3600<<" hours:"<<(TIMER1%3600)/60<<" minutes:"<<(TIMER1%3600)%60<<" seconds"<<endl;
            REPORT<<"Took time - "<<TIMER1/3600<<" hours:"<<(TIMER1%3600)/60<<" minutes:"<<(TIMER1%3600)%60<<" seconds"<<endl;
            
            mpf_div(percent, prime_amount, total_amount);
            //cout<<"Percent of found:"<<percent<<endl;
            REPORT<<"Percent of found:"<<percent<<endl;
            
            mpf_div(percent, prime_amount_probabilty_test, total_amount);
            //cout<<"Percent of probable:"<<percent<<endl;
            REPORT<<"Percent of probable:"<<percent<<endl;
            
            ++DoneProgress;
        }
        
		if (j < num_primes)
		{
            mpf_add_ui(total_amount, total_amount, 1);
			++(degs[j]);
			// making new number
            mpz_set_ui(now, 1);
			for (i = 0; i < num_primes; ++i)
                if (degs[i] != 0)
                {
                    mpz_pow_ui(mult, primes[i], degs[i]);
                    mpz_mul(now, now, mult);
                }
			mpz_add_ui(now, now, 1);
			// done N = now
			int t = mpz_probab_prime_p(now, 25);
            if (t == 2) 
            {
                mpf_add_ui(prime_amount_probabilty_test, prime_amount_probabilty_test, 1);
                mpf_add_ui(prime_amount, prime_amount, 1);
                GENERATED<<now<<endl;
                REPORT<<"Definitely prime by GMP prob test"<<endl;
            }
            else
            if (t == 1) 
            {
                mpf_add_ui(prime_amount_probabilty_test, prime_amount_probabilty_test, 1);
                if (this->root(variableForRoot, MAX_TRIES, now, num_primes, primes, degs))
                {
                    //comment HERE
                    GENERATED<<now<<endl;
                    mpf_add_ui(prime_amount, prime_amount, 1);
                    REPORT<<now<<endl;
                    REPORT<<"DEGS:"<<endl;
                    for (i = 0; i < num_primes; ++i) 
                    {
                        if (degs[i] > 0)
                            REPORT<<primes[i]<<" - "<<degs[i]<<endl;
                    }
                    REPORT<<"Digits(base = 10) = "<<mpz_sizeinbase(now, 10)<<endl;
                    REPORT<<"Digits(base = 2) = "<<mpz_sizeinbase(now, 2)<<endl;                    
                    REPORT<<"Primitive root: "<<variableForRoot<<endl<<endl;
                    
                    if (mpz_cmp_ui(variableForRoot, 1) == 0)
                    {
                        REPORT<<endl;
                        REPORT<<"ERRRRRRRRRRRRRRRRRRRRRRRRROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        REPORT<<endl;
                        
                        ERRORlocale = 1;
                    }
                    
                    if (mpz_sizeinbase(now, 10) < 100)
                    {
                        if (KP(now, num_primes, primes, degs))
                        {
                            REPORT<<"KP-prime"<<endl;
                        }
                        else
                        {
                            cout<<"KP-composite"<<endl;
                            REPORT<<"KP-composite"<<endl;   
                        }
                    }
                    
                }   
                else
                {
                    REPORT<<"Didn't find primitive root"<<endl;
                }
            }
 		}
	}
    REPORT<<endl<<"End of generation"<<endl;
    
    {
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        REPORT<<"Ended - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
    }
    
    
    REPORT<<"Number of primes:"<<prime_amount<<endl;
    REPORT<<"Total:"<<total_amount<<endl;
    
    if (mpf_cmp_ui(total_amount, 0) > 0)
    {
        mpf_div(percent, prime_amount, total_amount);
        mpf_div(uns, prime_amount, total_amount);
        REPORT<<"Percent of found:"<<percent<<endl;
        mpf_div(percent, prime_amount_probabilty_test, total_amount);
        REPORT<<"Percent of probable:"<<percent<<endl;
    }
    
    TIMER = clock() - TIMER;
    REPORT<<"Took time - "<<TIMER/CLOCKS_PER_SEC<<" seconds"<<endl;
    REPORT<<"Took time - "<<(TIMER/CLOCKS_PER_SEC)/3600<<" hours:"<<((TIMER/CLOCKS_PER_SEC)%3600)/60<<" minutes:"<<((TIMER/CLOCKS_PER_SEC)%3600)%60<<" seconds"<<endl;
    REPORT<<"ERRORlocale = "<<ERRORlocale<<endl;
    
    
    mpf_clear(percent);
	mpz_clear(now);
	mpz_clear(mult);
    mpz_clear(variableForRoot);
    mpf_clear(total_amount);
    mpf_clear(prime_amount);
    mpf_clear(prime_amount_probabilty_test);
    REPORT.close();
    GENERATED.close();
}

