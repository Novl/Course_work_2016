#include "../include/stack.h"


// Algorithm from O.N.Vasilenko page 30 
// Finding ord of element a in Z/nZ

void stack::ord(mpz_t uns, const mpz_t a, const mpz_t N, const int num_divisors, const mpz_t* divisors, const int* degs)
{
    mpz_sub_ui(uns, N, 1);
    mpz_t var;
    mpz_init(var);
    mpz_t var1;
    mpz_init(var1);
    for (int j = 0; j < num_divisors; ++j)
    {
        mpz_pow_ui(var, divisors[j], degs[j]);
        mpz_cdiv_q(uns, uns, var);
        mpz_powm(var1, a, uns, N);
        while (mpz_cmp_ui(var1, 1) != 0)
        {
            mpz_mul(uns, uns, divisors[j]);
            mpz_powm(var1, var1, divisors[j], N);
        }
    }
    mpz_clear(var);
    mpz_clear(var1);
}