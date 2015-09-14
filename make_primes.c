#include <stdio.h>

int main()
{
	freopen("primes.txt","w",stdout);
	unsigned long long i,n,t,f;
	n=2;
	for (i=0; i<10000; i++)
	{
		t=2;
		f=1;
		while (t*t<=n && f)
		{
			if (n % t == 0) f=0;
			else t++;
		}
		if (f) 
		{
			printf("%d\n",n);
			i++;
		}
		n++;
	}

	return 0;
}

