#ifndef _STACK_H_
#define _STACK_H_
#include "headers.h"
#include <string.h>
#include <string>

const int SIZE_STACK=40;
const int NUM_DIV_1=200;
const int NUM_DIV_2=100;

class stack
{
    private:
    int num;
    std::string stream;
    mpz_t array[SIZE_STACK];
    mpz_t variable;
    gmp_randstate_t	state;
     
    public:
    stack();
    ~stack();
    bool is_full();
    bool is_empty();
    void add(const char* str, int sys);
    void add(mpz_t num);
    void del();
    void clear();
    void last();
    void show();
    void writeOne();
    void writeAll();
    void read();
    void summ();
    void sub();
    void mul();
    void cdiv();
    void powm();
    bool gmp_test();
    void root();
    void gen_short_prime();
    void gen_long_prime();
};
#endif
