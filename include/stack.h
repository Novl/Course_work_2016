#ifndef _STACK_H_
#define _STACK_H_

#include "../include/headers.h"

const int SIZE_STACK=400;
const int NUM_DIV_1=200;
const int NUM_DIV_2=100;

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
    void root();
    bool root(const int, const mpz_t, const int, const mpz_t*,const int* );
    void ord(mpz_t, const mpz_t, const mpz_t, const int, const mpz_t*, const int*);
    void gen_short_prime();
};
#endif
