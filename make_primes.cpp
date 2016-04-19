#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

#define CEIL 10000000
#define OUTPUT "primes.txt"

using namespace std;

int main()
{
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

