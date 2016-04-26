#include "../include/stack.h"

stack::stack()
{
    this->num = 0;
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
void stack::root()
{
    if (this->gmp_test() == 0)
        cout<<"Not exist for not prime"<<endl;
    else
    {
        int FLAG = 0;
        cout<<"Enter '1' to see results one by one or '0' to skip"<<endl;
        cin>>FLAG;
        
        if (this->num == 0)
        {
            cout<<"Stack is empty"<<endl;
        }
        else
        {
            int num_divisors = 0;
            mpz_t divisors[NUM_DIV_1];
            
            // copying initial number from stack
            mpz_t local;
            mpz_init_set(local, this->array[this->num-1]);
            mpz_sub_ui(local, local, 1);
            //
            // Trial division
            mpz_t r;
            mpz_init(r);
            for (int i = 2; i < 1000000 && num_divisors < NUM_DIV_1; ++i)
            {	
                if (mpz_mod_ui(r, local, i) == 0)
                {
                    while (mpz_mod_ui(r, local, i)==0)
                        mpz_cdiv_q_ui(local, local, i);
                    mpz_init(divisors[num_divisors]);
                    mpz_set_ui(divisors[num_divisors], i);
                    ++num_divisors;
                }
            }
            mpz_clear(r);
            //
            
            int f = 0, R = 0, max_tries = 100;
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
    
    while (f != 1 && R < max_tries)
    {
        f = 1;
        // set 'variable' as a possible root
        if (R == 0)
            mpz_set_ui(variable, 1);
        else
        {
        mpz_sub_ui(variable, N, 1); // p-1
        mpz_urandomm(variable,  state,  variable); // from 0 to p-2 
        mpz_add_ui(variable,  variable,  1); // from 1 to p-1
        }
        // Fermat's theorem
        mpz_powm(variable1, variable, localN1, N);
        //
        if (mpz_cmp_ui(variable1, 1) == 0)
            while (found_roots < num_divisors && f)
            {	
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
        if (found_roots == num_divisors)
        {
            // making root
            mpz_set_ui(variable, 1);
            mpz_t ordA;
            mpz_init(ordA);
            for (int i = 0; i < num_divisors; ++i)
            {
                if (degs[i] > 0)
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
        /*
        else
        {
            gmp_printf("%Zd is not primitive root\n", variable);
            if (FLAG == 1)
                getchar();
        }
        */
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



bool stack::isValid(string input)
{
    if (isdigit(input[0]))
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
    // find primitive root
    if (input.compare("r")==0)
    {
        this->root();
    }		
    else
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
    if (input.compare("g")==0)
    {
        this->gen_prime();
    }
    // else
    // if (input.compare("gl")==0)
    // {
        // this->gen_long_prime();
    // }
    else
    return false;

    return true;
}
