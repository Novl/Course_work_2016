#include "../include/stack.h"

// Algorithm  Konyagin-Pomerance for factorization
// returns 'true' if N is prime, 'false' if composite

bool stack::KP(const mpz_t N, const int num_divisors, const mpz_t* divisors, const int* degs)
{
    int i;
    mpz_t up;
    mpz_init_set_ui(up, mpz_sizeinbase(N, 2));
    mpz_mul(up, up, up);
    mpz_add_ui(up, up, 1);
    int MaxNumberOfPrimes = 10000, NumberOfPrimes;
	mpz_t primes[MaxNumberOfPrimes];
    
    FILE *f1;
// reading basic using primes less than log(N)^2+1
    f1 = fopen("primes.txt", "r");
    mpz_init(primes[0]);
	for (i = 0; (gmp_fscanf(f1, "%Zd\n", primes[i]) > 0) && (mpz_cmp(up, primes[i]) >= 0); ++i) 
    {
        mpz_init(primes[i+1]);
    }
    fclose(f1);
    NumberOfPrimes = i;

    cout<<"Number of readed primes:"<<NumberOfPrimes<<endl;
//
    int step = 0;
    bool uns;
    mpz_t F;
    mpz_init_set_ui(F, 1);
    mpz_t KPvariable;
    mpz_init(KPvariable);
    mpz_t KPvariable1;
    mpz_init(KPvariable1);
    mpz_t KPord;
    mpz_init(KPord);
    mpz_t KPgcd;
    mpz_init_set_ui(KPgcd, 1);
    mpz_t KProot;
    mpz_init(KProot);
    mpz_root(KProot, N, 2);
    cout<<"KProot = "<<KProot<<endl;
    
    // a ::= primes[step]
    while (mpz_cmp(up, primes[step]) >= 0)
    {
        cout<<"a = "<<primes[step]<<endl;
        mpz_powm(KPvariable, primes[step], F, N);
        cout<<"a ^ F:"<<KPvariable<<endl;
        if (mpz_cmp_ui(KPvariable, 1) == 0) goto NEXT;
        mpz_sub_ui(KPvariable, N, 1);
        mpz_powm(KPvariable1, primes[step], KPvariable, N);
        cout<<"a ^ (N-1):"<<KPvariable1<<endl;
        if (mpz_cmp_ui(KPvariable1, 1) != 0) goto NO;
        
        this->ord(KPord, primes[step], N, num_divisors, divisors, degs);
        cout<<"a ord N:"<<KPord<<endl;
        for (i = 0; i < num_divisors; ++i)
            if (degs[i] > 0 && mpz_divisible_p(KPord, divisors[i]))
            {
                mpz_cdiv_q(KPvariable, KPord, divisors[i]);
                mpz_powm(KPvariable1, primes[step], KPvariable, N);
                mpz_sub_ui(KPvariable1, KPvariable1, 1);
                mpz_mul(KPgcd, KPgcd, KPvariable1);
                mpz_mod(KPgcd, KPgcd, N);
            }
        mpz_gcd(KPgcd, KPvariable1, N);
        if (mpz_cmp_ui(KPgcd, 1) > 0) goto NO;
        mpz_lcm(KPvariable, F, KPord);
        cout<<"F = "<<F<<endl;
        cout<<"lcm(НОК) = "<<KPvariable<<endl;
        mpz_set(F, KPvariable);
        if (mpz_cmp(F, KProot) >= 0) goto YES;
        NEXT:++step;
    }
    NO: uns = false;
    goto END;
    YES: uns = true;
       
    END:
    mpz_clear(up);
    mpz_clear(F);
    mpz_clear(KPvariable);
    mpz_clear(KPvariable1);
    mpz_clear(KPord);
    mpz_clear(KPgcd);
    mpz_clear(KProot);
    for (i = 0; i <= NumberOfPrimes; ++i)
        mpz_clear(primes[i]);
    /*
    if (uns)
        cout<<"KP-prime"<<endl;
    else
        cout<<"KP-composite"<<endl;
    */
    return uns;
}

bool stack::KP(const mpz_t N)
{
    mpz_t factors[MAX_FACTORS];
    int degs[MAX_FACTORS];
    int num_factors;
    mpz_t N1;
    mpz_init(N1);
    mpz_sub_ui(N1, N, 1);
    
    if (factorize(N1, factors, num_factors, degs))
        {
            cout<<N<<endl;
            bool uns = KP(N, num_factors, factors, degs);
            if (uns)
                cout<<"KP-prime"<<endl;
            else
                cout<<"KP-composite"<<endl;
            return uns;
        }
        else
            cout<<"Divisors N-1 higher than 1000000"<<endl;
    return false;
}

void stack::KP()
{
    if (!this->is_empty())
    {
        this->KP(this->array[this->num-1]);
    }
}