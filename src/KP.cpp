#include "../include/stack.h"

// Algorithm  Konyagin-Pomerance for factorization

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
    mpz_init(KPgcd);
    mpz_t KProot;
    mpz_init(KProot);
    mpz_root(KProot, N, 2);
    
    // a ::= primes[step]
    while (mpz_cmp(up, primes[step]) >= 0)
    {
        mpz_powm(KPvariable, primes[step], F, N);
        cout<<"a ^ F:"<<KPvariable<<endl;
        if (mpz_cmp_ui(KPvariable, 1) == 0) goto NEXT;
        mpz_sub_ui(KPvariable, N, 1);
        mpz_powm(KPvariable1, primes[step], KPvariable, N);
        cout<<"a ^ N:"<<KPvariable<<endl;
        if (mpz_cmp_ui(KPvariable1, 1) != 0) goto NO;
        
        this->ord(KPord, primes[step], N, num_divisors, divisors, degs);
        cout<<"a ord N:"<<KPord<<endl;
        for (i = 0; i < num_divisors; ++i)
            if (degs[i] > 0 && mpz_divisible_p(KPord, divisors[i]))
            {
                mpz_cdiv_q(KPvariable, KPord, divisors[i]);
                mpz_powm(KPvariable1, primes[step], KPvariable, N);
                mpz_gcd(KPgcd, KPvariable1, N);
                if (mpz_cmp_ui(KPgcd, 1) > 0) goto NO;
            }
        mpz_lcm(KPvariable, F, KPord);
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
    
    if (uns)
        cout<<"KP-prime"<<endl;
    else
        cout<<"KP-composite"<<endl;
    return uns;
}