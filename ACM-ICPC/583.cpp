#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;

vector <long> primefactors(long x)
{
	long i;			/* counter */
	long c;			/* remaining product to factor */
	vector <long> fac;
	c = x;

	while ((c % 2) == 0) {
		fac.push_back(2);
		c = c / 2;
	}
	i = 3;

	while (i <= (sqrt(c)+1)) {
		if ((c % i) == 0) {
			fac.push_back(i);
			c = c / i;
		}
		else
			i = i + 2;
	}

	if (c > 1) 
		fac.push_back(c);
	return fac;
}

int main()
{
	long a;
	long b;
	vector <long> f;
	while (cin >> a && a != 0)
	{
		b = a;
		if (b < 0)
			b = -b;
		
		f = primefactors(b);
		
		cout << a << " = ";
		if (!f.empty())
		{
			if (a < 0)
				cout << "-1 x ";
			
			for (int i = 0; i < f.size() - 1; i++)
				cout << f[i] << " x ";
					
			cout << f[f.size() - 1] << endl;
		}
		else
			cout << a << endl;
	}
	return 0;
}
