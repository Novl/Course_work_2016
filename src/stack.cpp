#include "../include/stack.h"

using namespace std;

stack::stack()
{
    this->num = 0;
    mpz_init(variable);
    gmp_randinit_default(state);
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

void stack::add(mpz_t num)
{
    if (!this->is_full()) 
        mpz_set(this->array[this->num++], num);
}

void stack::add(const char* str, int sys)
{
    if (!this->is_full())
        mpz_set_str(this->array[this->num++], str, sys);
}

void stack::del()
{
    if (!this->is_empty())
    {
        this->num--;
        mpz_set_ui(this->array[this->num], 0);
    }
    cout<<"Last number deleted"<<endl;
}

void stack::clear()
{
    if (!this->is_empty())
    {
        this->num=0;
    }
    cout<<"Stack is cleared"<<endl;
}

void stack::last()
{
    if (!this->is_empty())
        cout<<"Last number is - "<<this->array[this->num-1]<<endl;
}

void stack::show()
{
    cout<<"Size of stack is: "<<this->num<<endl;
    cout<<"All stack from bottom :"<<endl;
    for (int i=0; i<this->num; i++)
		cout<<this->array[i]<<endl;
}

void stack::writeOne()
{
    fstream OUT;
    string stream;
    cout<<"Enter name(path) of file: ";
    cin>>stream;
    OUT.open(stream.c_str(), fstream::app | fstream::out);
    OUT<<this->array[this->num-1]<<endl;
    OUT.close();
    cout<<endl;
}

void stack::writeAll()
{
    fstream OUT;
    cout<<endl<<"Enter name(path) of file: ";
    cin>>stream;
    OUT.open(stream.c_str(), fstream::app | fstream::out);
    for (int i=this->num; i>0; i--)
        OUT<<this->array[i-1]<<endl;
    OUT.close();
    cout<<endl;
}

void stack::read()
{
    ifstream IN;
    cout<<endl<<"Enter name(path) of file: ";
    cin>>stream;
    IN.open(stream.c_str());
    while (!IN.eof() && IN.good() && this->num < SIZE_STACK)
    {
        IN>>this->array[this->num++];
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

bool stack::gmp_test()
{
    if (this->num == 0)
        cout<<"Stack is empty"<<endl;
    else
    {
        unsigned long long t = mpz_probab_prime_p(this->array[this->num-1], 20);
        cout<<this->array[this->num-1]<<endl;
        if (t==2) 
        {
            cout<<"Definitely prime"<<endl;
            return true;
        }
        else
            if (t==1)
            {
                cout<<"Undetermined"<<endl;
                return false;
            }
            else 
            {
                cout<<"Composite"<<endl;
                return false;
            }
    }
}

void stack::root()
{
    if (!this->gmp_test())
        cout<<"Not exist for not prime"<<endl;
    else
    {
        mpz_t r;
        mpz_init(r);
        int FLAG = 0;
        cout<<"Enter '1' to see result one by one or '0' to skip"<<endl;
        cin>>FLAG;
        cout<<endl;
        if (this->num == 0)
        {
            cout<<"Stack is empty"<<endl;
        }
        else
        {
            int num_divisors=0;
            mpz_t divisors[NUM_DIV_1];
            for (int i=0; i<NUM_DIV_1; i++) 
                    mpz_init(divisors[i]);
                
            mpz_t local;
            mpz_init_set(local, this->array[this->num-1]);
            mpz_sub_ui(local, local, 1);
            for (int i=2; i<400000; i++)
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
            
            mpz_sub_ui(local, this->array[this->num-1], 1);
            
            while (f!=1 && R<100)
            {
                f=1;
                mpz_sub_ui(variable, this->array[this->num-1], 1); // p-1
                mpz_urandomm(variable,  state,  variable); // from 0 to p-2 
                mpz_add_ui(variable,  variable,  1); // from 1 to p-1
                for (int i=0; (i<num_divisors) && f;i++)
                {	
                    mpz_cdiv_q(deg,  local, divisors[i]);
                    mpz_powm(variable1,  variable ,  deg, this->array[this->num-1]);
                    if (mpz_cmp_ui(variable1, 1)==0) f=0;
                }
                if (f==1)
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
                    gmp_printf("%Zd is not primitive root\n", variable);
                if (FLAG == 1)
                //cin >> EMPTY_VARIABLE;
                    getchar();
                R++;
            }
        }
    }
    cout<<"Returned to main menu"<<endl;
}

void stack::gen_short_prime()
{
	long long i,j,number,MAX_DEG,MIN_DEG,all,t;
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
	string S;
    
	FILE *f1;
	
    f1=fopen("primes.txt", "r");
	for (i=0; i<10000; ++i) gmp_fscanf(f1,"%Zd\n", primes[i]);
	fclose(f1);
	
	printf("Enter \'f\' to read from file \'test.txt\'  ");
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



void stack::gen_long_prime()
{
	long long i, j, number, MAX_DEG, MIN_DEG, all, t, border;
	mpz_t primes[10000];
	long long degs[10000];
	mpz_t var;
	mpz_t var1;
	mpz_t now;
	mpz_t now1;
	mpz_t mult;
	mpz_t MAX;
    mpz_init(var);
	mpz_init(var1);
	mpz_init(now);
	mpz_init(now1);
	mpz_init(mult);
    mpz_init(MAX);
    
	string S;
    
    mpz_set_str(MAX, "10000000000000000000000000000", 10);
    
	//freopen("result.txt", "w", stdout);
	//printf("Enter number of using primes : ");
	
    cout<<"Enter number using numbers from stack or 0 to use all"<<endl;
    cin>>border;
    if (border==0)
        number = this->num;
    else
        number = border;
    
    for (i=0; i<number; i++) mpz_set(primes[i], this->array[i]);
	cout<<"Enter MAX_DEG: ";
	cin>>MAX_DEG;
	cout<<"Enter MIN_DEG: ";
	cin>>MIN_DEG;
    
	cout<<"Number of using primes : "<<number<<endl;
	printf("Entered MAX_DEG : %lld\n",MAX_DEG);
	printf("Entered MIN_DEG : %lld\n",MIN_DEG);
	
	cout<<"\nEnter \'1\' to see all checked numbers or \'0\' to see only prime\n";
	cin>>all;
	cout<<endl;
    
	for (i = 0; i < number && mpz_cmp(this->array[i], MAX) < 0; i++) degs[i]=MIN_DEG;	
    for (; i < number; i++) degs[i]=1;
    j=0;
	while (j<number && mpz_cmp(this->array[j], MAX) < 0)
	{
		j=0;
		while ((degs[j]==MAX_DEG) && (j<number) && mpz_cmp(this->array[j], MAX)  < 0)
		{
			degs[j]=MIN_DEG;
			++j;
		}

		if (j<number && mpz_cmp(this->array[j], MAX)  < 0)
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
                    gmp_randclear(NewState);    
                }
		}
	}
    END:
    printf("\nEnd of generation\n");
}