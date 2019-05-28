#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    long long a;					// input
    bool prime[1000000];			// For storing the sieve result.

    memset(prime, true, sizeof(prime));		// Assume all number is prime.
    prime[0] = prime[1] = false;			// 0 and 1 is not prime.

	int storeprime[78498];
	int z = 0;
	// Generate sieve.

    for (int i = 2; i < 1000000; i++)
    {
		if (prime[i])
		{
			for (int j = i + i; j < 1000000; j += i)
				prime[j] = false;
			storeprime[z] = i;
			z++;
		}
    }
    while (cin >> a && a != 0)
    {
        long long largest = -1;			// largest prime.
		if(a < 0)
			a = -a;
		long long input = a;
		
		short second = 0;
		for (int i = 0; i < 78498 && storeprime[i] <= sqrt(input); i++)
		{
			if (a % storeprime[i] == 0)		// If it is prime and a can be divided by it
			{
				while (a % storeprime[i] == 0)		
					a /= storeprime[i];	
				largest = storeprime[i];
				second++;					// to determine the number of divisor.
			}
		}
		if (a == 1)				// it can be fully divided by the current prime.
		{
			if (second >= 2)
				cout << largest << endl;	// got more than 2 divisor
			else
				cout << -1 << endl;
		}
		else
		{
			if(second >= 1)
				cout << a << endl;			
			else
				cout << -1 << endl;
		}
    }
    return 0;
}
