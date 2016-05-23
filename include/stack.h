#ifndef _STACK_H_
#define _STACK_H_

#include "../include/headers.h"

const int SIZE_STACK = 400000;
const int NUM_DIV_2 = 100;
const int MAX_FACTORS = 1000;

class stack
{
    private:
    int num;
    string stream;
    mpz_t array[SIZE_STACK];
    mpz_t variable;
    gmp_randstate_t	state;
     
    public:
    stack();
    ~stack();
    bool isNumber(const string);
    bool isValid(std::string input);
    bool is_full();
    bool is_empty();
    bool add(const char* str, int sys);
    bool add(mpz_t num);
    bool del();
    void clear();
    void last();
    void head();
    void show();
    void writeOne();
    void writeAll();
    void read();
    void summ();
    void sub();
    void mul();
    void cdiv();
    void powm();
    int gmp_test();
    void fact();
    bool factorize(const mpz_t, mpz_t*, int&, int*);
    void root();
    bool root(mpz_t, const int, const mpz_t, const int, const mpz_t*,const int* );
    void ord(mpz_t, const mpz_t, const mpz_t, const int, const mpz_t*, const int*);
    void gen_prime();
    void gen_primes_file();
    void gen_prime_testing(mpf_t, const mpz_t* , const int , const int , const int );
    void test();
    void KP();
    bool KP(const mpz_t);
    bool KP(const mpz_t, const int, const mpz_t*, const int*);
};
#endif
