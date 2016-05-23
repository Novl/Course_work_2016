#include "../include/stack.h"

stack::stack()
{
    this->num = 0;
    srand(time(NULL));
    mpz_init(variable);
    unsigned long curtime = (unsigned long)time(NULL);
    gmp_randinit_default(state);
    gmp_randseed_ui(state, curtime);
    for (int i=0; i<SIZE_STACK; i++) 
    {
        mpz_init(this->array[i]);
        mpz_set_ui(this->array[i], 0);
    }
}

stack::~stack()
{
    mpz_clear(variable);
    gmp_randclear(state);
    for (int i=0; i<SIZE_STACK; i++) 
        mpz_clear(this->array[i]);
}

bool stack::is_empty()
{
    if (this->num > 0)
        return false;
    else
    {
        cout<<"Stack is empty"<<endl;
        return true;
    }
}

bool stack::is_full()
{
    if (this->num < SIZE_STACK)
        return false;
    else
    {
        cout<<"Stack is full"<<endl;
        return true;
    }
}

bool stack::add(mpz_t num)
{
    if (!this->is_full()) 
        mpz_set(this->array[this->num++], num);
    else
        return false;
    return true;
}

bool stack::add(const char* str, int sys)
{
    if (!this->is_full())
        mpz_set_str(this->array[this->num++], str, sys);
    else
        return false;
    return true;
}

bool stack::del()
{
    if (!this->is_empty())
    {
        this->num--;
        mpz_set_ui(this->array[this->num], 0);
    }
    else
        return false;
    cout<<"Last number deleted"<<endl;
    return true;
}

void stack::clear()
{
    if (!this->is_empty())
    {
        this->num = 0;
    }
    cout<<"Stack is cleared"<<endl;
}

void stack::last()
{
    if (!this->is_empty())
        cout<<"Last number is - "<<this->array[this->num-1]<<endl;
}

void stack::head()
{
    if (!this->is_empty())
        cout<<"Last number is - "<<this->array[this->num-1]<<endl;
}

void stack::show()
{
    cout<<endl;
    cout<<"Size of stack is: "<<this->num<<endl;
    cout<<"All stack from bottom:"<<endl;
    for (int i = 0; i < this->num; ++i)
		cout<<this->array[i]<<endl;
}

void stack::writeOne()
{
    fstream OUT;
    string stream;
    cout<<"Enter name(path) of file(appending writing): ";
    cin>>stream;
    OUT.open(stream.c_str(), fstream::app | fstream::out);
    OUT<<this->array[this->num-1]<<endl;
    OUT.close();
    cout<<endl;
}

void stack::writeAll()
{
    fstream OUT;
    cout<<"Enter name(path) of file(appending writing): ";
    cin>>stream;
    OUT.open(stream.c_str(), fstream::app | fstream::out);
    for (int i = this->num; i > 0; --i)
        OUT<<this->array[i-1]<<endl;
    OUT.close();
    cout<<endl;
}

void stack::read()
{
    int number;
    ifstream IN;
    cout<<endl<<"Enter name(path) of file: ";
    cin>>stream;
    cout<<"Enter number of numbers or '0' to read all(max = "<<SIZE_STACK<<"):";
    cin>>number;
    if (number == 0)
        number = SIZE_STACK;
    
    IN.open(stream.c_str());
    while (!IN.eof() && IN.good() && this->num < SIZE_STACK && number > 0)
    {
        IN>>this->array[this->num++];
        --number;
    }
    IN.close();
    cout<<endl;
}

void stack::summ()
{
    if (this->num < 2)
        cout<<"Not enought elements"<<endl;
    else
    {
        mpz_add(variable, this->array[this->num-2], this->array[this->num-1]);
        mpz_set(this->array[this->num-2], variable);
        this->num--;
        cout<<"Summ of last two numbers is = "<<variable<<endl;
        cout<<"2 last numbers erased, result stored"<<endl;
    }
}

void stack::sub()
{
    if (this->num < 2)
        cout<<"Not enought elements"<<endl;
    else
    {
        mpz_sub(variable, this->array[this->num-2], this->array[this->num-1]);
        mpz_set(this->array[this->num-2], variable);
        this->num--;
        cout<<"Subtraction of last two numbers is = "<<variable<<endl;
        cout<<"2 last numbers erased, result stored"<<endl;
    }
}

void stack::mul()
{
    if (this->num < 2)
        cout<<"Not enought elements"<<endl;
    else
    {
        mpz_mul(variable, this->array[this->num-2], this->array[this->num-1]);
        mpz_set(this->array[this->num-2], variable);
        this->num--;
        cout<<"Multiplication of last two numbers is = "<<variable<<endl;
        cout<<"2 last numbers erased, result stored"<<endl;
    }
}

void stack::cdiv()
{
    if (this->num < 2)
        cout<<"Not enought elements"<<endl;
    else
    {
        mpz_cdiv_q(variable, this->array[this->num-2], this->array[this->num-1]);
        mpz_set(this->array[this->num-2], variable);
        this->num--;
        cout<<"Division of last two numbers is = "<<variable<<endl;
        cout<<"2 last numbers erased, result stored"<<endl;
    }
}

void stack::powm()
{
    if (this->num == 0)
        cout<<"Stack is empty"<<endl;
    else
    {
        mpz_t module;
        mpz_t exp;
        mpz_init(exp);
        mpz_init(module);
        cout<<"Enter exponent: "<<endl;
        cin>>exp;
        cout<<"Enter module: "<<endl;
        cin>>module;
        mpz_powm(variable, this->array[this->num-1],  exp,  module);
        gmp_printf("\n%Zd\n in power \n%Zd\n    mod\n%Zd\n=%Zd\n", this->array[this->num-1], exp, module, variable);
        mpz_set(this->array[this->num-1], variable);
        cout<<"1 last number erased, result stored"<<endl;
    }
}

int stack::gmp_test()
{
    if (this->num == 0)
        cout<<"Stack is empty"<<endl;
    else
    {
        int accuracy = 25;
        int t = mpz_probab_prime_p(this->array[this->num-1], accuracy);
        cout<<this->array[this->num-1]<<endl;
        cout<<"Accuracy = "<<accuracy<<"(probability fail less 2^"<<2*accuracy<<")"<<endl;
        if (t == 2) 
        {
            cout<<"Definitely prime"<<endl;
            //return true;
        }
        else
            if (t == 1)
            {
                cout<<"Undetermined"<<endl;
                //return false;
            }
            else 
            {
                cout<<"Composite"<<endl;
                //return false;
            }
        return t;
    }
    return -1;
}


// with  trial divisions up to 1000000
bool stack::factorize(const mpz_t N, mpz_t* factors, int& num_factors, int* degs)
{
    mpz_t i;
    mpz_init_set_ui(i, 2);
    num_factors = 0;
    mpz_t N1;
    mpz_init_set(N1, N);
    
    while (mpz_cmp_ui(N1, 1) > 0 && mpz_cmp_ui(i, 1000000) < 0 && num_factors < 1000)
    {
        if (mpz_divisible_p(N1, i))
        {
            mpz_init_set(factors[num_factors], i);
            degs[num_factors] = 0;
            while (mpz_divisible_p(N1, i))
            {
                mpz_cdiv_q(N1, N1, i);
                ++degs[num_factors];
            }
            ++num_factors;
        }
        mpz_add_ui(i, i, 1);
    }
    
    int uns = mpz_cmp_ui(N1, 1);
    mpz_clear(i);
    mpz_clear(N1);
    
    if (uns == 0)
        return true;
    else
        return false;
}

void stack::fact()
{
    if (!this->is_empty())
    {
        mpz_t factors[MAX_FACTORS];
        int degs[MAX_FACTORS];
        int num_factors;
        if (factorize(this->array[this->num-1], factors, num_factors, degs))
        {
            cout<<"Factors:"<<endl;
            for (int i = 0; i < num_factors; ++i)
                cout<<factors[i]<<" - "<<degs[i]<<endl;
        }
        else
        {
            cout<<"Found factors:"<<endl;
            for (int i = 0; i < num_factors; ++i)
                cout<<factors[i]<<" - "<<degs[i]<<endl;
            cout<<"But divisors N higher than 1000000"<<endl;
        }
    }
}

void stack::root()
{
    if (this->gmp_test() == 0)
        cout<<"Not exist for not prime"<<endl;
    else
    if (this->num == 0)
    {
        cout<<"Stack is empty"<<endl;
    }
    else
    {
        int FLAG = 0;
        cout<<"Enter '1' to see results one by one or '0' to skip"<<endl;
        cin>>FLAG;
        
        {
            mpz_t local;
            mpz_init(local);
            mpz_sub_ui(local, this->array[this->num], 1);
            
            int num_divisors;
            mpz_t divisors[MAX_FACTORS];
            int degs[MAX_FACTORS];
            factorize(local, divisors, num_divisors, degs);
            
            int f = 0, R = 0, max_tries = 20;
            mpz_t variable1;
            mpz_init(variable1);
            mpz_t deg;
            mpz_init(deg);
            
            mpz_sub_ui(local, this->array[this->num-1], 1);
            
            while (f != 1 && R < max_tries)
            {
                f = 1;
                // set 'variable' as a possible root
                mpz_sub_ui(variable, this->array[this->num-1], 1); // p-1
                mpz_urandomm(variable,  state,  variable); // from 0 to p-2 
                mpz_add_ui(variable,  variable,  1); // from 1 to p-1
                for (int i = 0; (i < num_divisors) && f; ++i)
                {	
                    mpz_cdiv_q(deg,  local, divisors[i]);
                    mpz_powm(variable1,  variable ,  deg, this->array[this->num-1]);
                    // all modules shoud be non '1'
                    if (mpz_cmp_ui(variable1, 1) == 0) 
                        f = 0;
                }
                //
                if (f == 1)
                {
                    gmp_printf("%Zd - primitive root of %Zd\n", variable, this->array[this->num-1]);
                    for (int i=0;(i<num_divisors) && f;i++)
                    {	
                        mpz_cdiv_q(deg, local, divisors[i]);
                        mpz_powm(variable1, variable , deg, this->array[this->num-1]);
                        gmp_printf("%Zd in power of %Zd by module %Zd =  %Zd\n", variable, deg, this->array[this->num-1], variable1);
                    }
                }
                else
                {
                    gmp_printf("%Zd is not primitive root\n", variable);
                    if (FLAG == 1)
                        getchar();
                }
                ++R;
            }
            mpz_clear(variable1);
            mpz_clear(deg);
            mpz_clear(local);
        }
    }
    cout<<"Returned to main menu"<<endl;   
}


// for generation with parametrs
// without trial divisions
// based on factorization N
bool stack::root(mpz_t uns, const int max_tries, const mpz_t N, const int num_divisors, const mpz_t* divisors, const int* degs)
{
    // roots[] for using Theorem 1.23 from Vasilenko O.N.
    // N - assuming prime number
    mpz_t roots[num_divisors];
    int f = 0, R = 0, found_roots = 0;
    // variable1 - for computing
    mpz_t variable1;
    mpz_init(variable1);
    mpz_t degree;
    mpz_init(degree);
    mpz_t localN1;  // N-1
    mpz_init(localN1);
    
    mpz_sub_ui(localN1, N, 1);
    
    for (int i = 0; i < num_divisors; ++i)
        mpz_init_set_ui(roots[i], 0);
    
    //cout<<"num_d : "<<num_divisors<<endl;
    while (f != 1 && R < max_tries)
    {
        //cout<<"R = "<<R<<endl;
        //cout<<"fr = "<<found_roots<<endl;
        f = 1;
        // set 'variable' as a possible root
        mpz_sub_ui(variable, N, 1); // p-1
        mpz_urandomm(variable,  state,  variable); // from 0 to p-2 
        mpz_add_ui(variable,  variable,  1); // from 1 to p-1
        // Fermat's theorem
        mpz_powm(variable1, variable, localN1, N);
        //
        //cout<<"root: "<<variable<<endl;
        if (mpz_cmp_ui(variable1, 1) == 0)
            while (found_roots < num_divisors && f)
            {	
                //cout<<"fr = "<<found_roots<<endl;
                if (degs[found_roots] != 0)
                {
                    mpz_cdiv_q(degree,  localN1, divisors[found_roots]);
                    mpz_powm(variable1,  variable ,  degree, N);
                    // all modules shoud be non '1'   -  // a[i] ^ ((n - 1) / p[i]) != 1 (mod n)
                    if (mpz_cmp_ui(variable1, 1) == 0) 
                        f = 0;
                    else
                        mpz_set(roots[found_roots++], variable);
                }
                else
                    ++found_roots;
            }
        else
        {
            //cout<<"Not prime from Fermat's little theorem"<<endl;
            return false;
        }
        //
        //cout<<"fr = "<<found_roots<<endl;
        //cout<<"f = "<<f<<endl;
        if (found_roots == num_divisors)
        {
            //cout<<"MAKING"<<endl;
            // making root
            mpz_set_ui(variable, 1);
            mpz_t ordA;
            mpz_init(ordA);
            for (int i = 0; i < num_divisors; ++i)
            {
                //cout<<"MAKING:"<<i<<endl;
                if (degs[i] > 0 && (i > 0 ? mpz_cmp(roots[i], roots[i-1]) != 0: true))
                {
                    ord(ordA, roots[i], N, num_divisors, divisors, degs);
                    mpz_set(degree, ordA);
                    mpz_pow_ui(variable1, divisors[i], degs[i]); // p[i] ^ deg[i]
                    mpz_cdiv_q(variable1, degree, variable1);  // ord / (p[i] ^ deg[i])
                    mpz_powm(variable1, roots[i], variable1, N);
                    mpz_mul(variable, variable, variable1);
                    mpz_mod(variable, variable, N);
                }
            }
            
            //
            //gmp_printf("%Zd - primitive root of %Zd\n", variable, N);
            //this->add(variable);
            /*
            cout<<endl;
            for (int i=0;(i<num_divisors);i++)
            {	
                mpz_cdiv_q(degree, localN1, divisors[i]);
                mpz_powm(variable1, variable , degree, N);
                gmp_printf("%Zd in power of %Zd by module %Zd =  %Zd\n", variable, degree, N, variable1);
            }
            */
            mpz_clear(ordA);
            mpz_set(uns, variable1);
        }
        ++R;
    }
    mpz_clear(variable1);
    mpz_clear(degree);
    mpz_clear(localN1);
    for (int i = 0; i < num_divisors; ++i)
        mpz_clear(roots[i]);
    
    //cout<<"Returned to main menu"<<endl;
    if (f == 1)
        return true;
    return false;
}

void stack::test()
{
    unsigned int numberOfTests, numberOfPrimesForTest, numberOfStartPrimes, NumberOfPrimes, MaxNumberOfPrimes = 100000, MIN_DEG, MAX_DEG;
    string OUTPUTdir;
    unsigned int i, j;
    char buff[10];
    time_t TIMER, rawtime;
    struct tm * timeinfo;
    char str[250];
    
    cout<<"Enter number of tests:"<<endl;
    cin>>numberOfTests;
    
    cout<<"Enter number of primes:"<<endl;
    cin>>numberOfPrimesForTest;
    
    cout<<"Enter number of starting primes:"<<endl;
    cin>>numberOfStartPrimes;
    if (numberOfStartPrimes > 10 || numberOfStartPrimes <1)
        numberOfStartPrimes = 1;
    cout<<"Enter MIN_DEG:"<<endl;
    cin>>MIN_DEG;
    
    cout<<"Enter MAX_DEG:"<<endl;
    cin>>MAX_DEG;
    
    mpf_t minResult, maxResult;
    mpf_t* results = (mpf_t*)calloc(numberOfTests, sizeof(mpf_t));
    mpz_t* primes = (mpz_t*)calloc(MaxNumberOfPrimes, sizeof(mpz_t));
    mpz_t* primesForTest = (mpz_t*)calloc(numberOfPrimesForTest, sizeof(mpz_t));
    
    mpf_init_set_ui(minResult, 1);
    mpf_init_set_ui(maxResult, 0);
    
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
        fclose(f1);
    }
    
    system("mkdir Tests(automated)");
    ofstream OUTPUTreport("Tests(automated)\\TotalReport.txt");
    {
        TIMER = clock();
        
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        OUTPUTreport<<"Started - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
    }
    
    for (j = 0; j < numberOfPrimesForTest; ++j)
    {
        mpz_init(primesForTest[j]);
        if (j < numberOfStartPrimes)
            mpz_set(primesForTest[j], primes[j]);
    }
    
    
    for (i = 0; i < numberOfTests; ++i)
    {
        cout<<"testing: "<<i<<endl;
        itoa(i, buff, 10);
        OUTPUTdir = string("Tests(automated)\\Test")+string(buff);
        system((string("mkdir ")+OUTPUTdir).c_str());
        ofstream OUTPUTprimes((OUTPUTdir+string("\\primes.txt")).c_str());
        ofstream OUTPUTtest((OUTPUTdir+string("\\test.txt")).c_str());
        ofstream OUTPUTpercent((OUTPUTdir+string("\\percent.txt")).c_str());
        
        for (j = 0; j < numberOfStartPrimes; ++j)
            OUTPUTprimes<<primesForTest[j]<<endl;
        for (j = numberOfStartPrimes; j < numberOfPrimesForTest; ++j)
        {
            mpz_set(primesForTest[j], primes[ numberOfStartPrimes + (rand() % (NumberOfPrimes - numberOfStartPrimes)) ]);
            OUTPUTprimes<<primesForTest[j]<<endl;
        }
        mpf_init(results[i]);
        this->gen_prime_testing(results[i], primesForTest, numberOfPrimesForTest, MIN_DEG, MAX_DEG);   
        OUTPUTtest<<numberOfPrimesForTest<<endl<<MIN_DEG<<endl<<MAX_DEG<<endl<<"0";
        OUTPUTpercent<<results[i];
        OUTPUTprimes.close();
        OUTPUTtest.close();
        OUTPUTpercent.close();
        cout<<results[i]<<endl;
    }
    mpf_t totalAvarage;
    mpf_init_set(totalAvarage, results[0]);
    for (i = 1; i < numberOfTests; ++i)
    {
        if (mpf_cmp(minResult, results[i]) > 0) mpf_set(minResult, results[i]);
        if (mpf_cmp(maxResult, results[i]) < 0) mpf_set(maxResult, results[i]);
        mpf_add(totalAvarage, totalAvarage, results[i]);
    }
    mpf_div_ui(totalAvarage, totalAvarage, numberOfTests);
    
    {        
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        cout<<"Ended - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
        OUTPUTreport<<"Ended - "<<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec<<endl;
        
        TIMER = clock() - TIMER;
        cout<<"Took time - "<<TIMER/CLOCKS_PER_SEC<<" seconds"<<endl;
        cout<<"Took time - "<<(TIMER/CLOCKS_PER_SEC)/3600<<" hours:"<<((TIMER/CLOCKS_PER_SEC)%3600)/60<<" minutes:"<<((TIMER/CLOCKS_PER_SEC)%3600)%60<<" seconds"<<endl;
        
        OUTPUTreport<<"Took time - "<<TIMER/CLOCKS_PER_SEC<<" seconds"<<endl;
        OUTPUTreport<<"Took time - "<<(TIMER/CLOCKS_PER_SEC)/3600<<" hours:"<<((TIMER/CLOCKS_PER_SEC)%3600)/60<<" minutes:"<<((TIMER/CLOCKS_PER_SEC)%3600)%60<<" seconds"<<endl;
    }
    cout<<"min_percent = "<<minResult<<endl;
    cout<<"max_percent = "<<maxResult<<endl;
    cout<<endl<<"Average percent = "<<totalAvarage<<endl;
    OUTPUTreport<<endl;
    OUTPUTreport<<"Used base file = "<<str<<endl;
    OUTPUTreport<<"Used start primes = "<<numberOfStartPrimes<<endl;
    OUTPUTreport<<"numberOfTests = "<<numberOfTests<<endl;
    OUTPUTreport<<"numberOfPrimesForTest = "<<numberOfPrimesForTest<<endl;
    OUTPUTreport<<"MIN_DEG = "<<MIN_DEG<<endl<<"MAX_DEG = "<<MAX_DEG<<endl;
    OUTPUTreport<<"min_percent = "<<minResult<<endl;
    OUTPUTreport<<"max_percent = "<<maxResult<<endl;
    OUTPUTreport<<"Average percent = "<<totalAvarage<<endl;
    OUTPUTreport.close();
    
    for (i = 0; i < numberOfTests; ++i) mpf_clear(results[i]);
    for (i = 0; i < NumberOfPrimes; ++i) mpz_clear(primes[i]);
    for (i = 0; i < numberOfPrimesForTest; ++i) mpz_clear(primesForTest[i]);  
    mpf_clears(minResult, maxResult, totalAvarage, NULL);
}

bool stack::isValid(string input)
{
    if (isNumber(input))
    {
        this->add(input.c_str(), 10);
    }
    else
    if (input.compare("+")==0)
    {
        this->summ();
    }
    else
    if (input.compare("-")==0)
    {
        this->sub();
    }
    else
    if (input.compare("*")==0)
    {
        this->mul();
    }
    else
    if (input.compare("/")==0)
    {
        this->cdiv();
    }
    else
    if (input.compare("^")==0)
    {
        this->powm();
    }
//------- Op-s with stack ------------------------------------------------------		
    else
    // Top of stack
    if (input.compare("h")==0)
    {
        this->last();
    }
    else
    // Menu
    if (input.compare("m")==0)
    {
        menu();
    }
    else
    if (input.compare("sm")==0)
    {
        short_menu();
    }
    else
    // Delete
    if (input.compare("d")==0)
    {
        this->del();
    }
    else
    if (input.compare("c")==0)
    {
        this->clear();
    }
    else
    // ALL
    if (input.compare("a")==0)
    {
        this->show();
    }
    else
    if (input.compare("w")==0)
    {
        this->writeAll();
    }
    else
    if (input.compare("v")==0)
    {
        this->writeOne();
    }
    else
    if (input.compare("re")==0)
    {
        this->read();
    }
    else
//  ----------------------------------------- Miscellanious--------------------------------------------            
    // GMPLIB TEST probable prime
    if (input.compare("gmptp")==0)
    {
        this->gmp_test();
    }
    else
    if (input.compare("f")==0)
    {
        this->fact();
    }
    else
    // find primitive root
    if (input.compare("r")==0)
    {
        this->root();
    }
    else
    // KP algo
    if (input.compare("kp")==0)
    {
        this->KP();
    }
    else
    // default gen_prime
    if (input.compare("g")==0)
    {
        this->gen_prime();
    }
    else
    // random primes generation prime to file
    if (input.compare("gf")==0)
    {
        this->gen_primes_file();
    }
    else
    // testing
    if (input.compare("t")==0)
    {
        this->test();
    }
    else
    return false;

    return true;
}

bool stack::isNumber(const string s)
{
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
        if (*it < '0' || *it > '9')
            return false;
    return true;
}