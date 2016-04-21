/*
    Generates primes numbers up to 1000000 or first input parametr
    and print in file primes.txt at the same directory
*/

#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <vector>
#include <fstream>

#define OUTPUT "primes.txt"

long CEIL = 1000000;
using namespace std;

int main(int argc, char* argv[])
{
    if (argc > 1)
        CEIL = atol(argv[1]);
    vector<int> UNS(CEIL);
    
	ofstream OutStream(OUTPUT);
    
	unsigned long long i,n,t;
	n = 1;
    UNS[0] = 2;
	for (i = 3; i < CEIL; i += 2)
	{
		t=0;
		while (t < n && UNS[t]*UNS[t] <= i &&  i % UNS[t] != 0)
		    ++t;
		if (t == n || UNS[t]*UNS[t] > i) 
		{
			UNS[n] =  i;
            ++n;
		}
	}

    for (i = 0; i < n; ++i)
        OutStream<<UNS[i]<<endl;
    OutStream.close();
    
	return 0;
}

