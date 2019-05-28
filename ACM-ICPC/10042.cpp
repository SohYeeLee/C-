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
	int test;
	long a;
	
	cin >> test;
	while (test--)
	{
		vector <long> fac;	
		cin >> a;
		for (unsigned long long i = a + 1; i <= 10000000000; i++)
		{
			long long s1 = 0, s2 = 0;
			
			fac = primefactors(i);
			
			if (fac.size() > 1)
			{
				stringstream s;
				s << i;
				string temp;
				s >> temp;
				for (int j = 0; j < temp.size(); j++)
					s2 = (temp[j] - 48) + s2;
				
				for (int j = 0; j < fac.size(); j++)
				{
					if (fac[j] > 9)
					{
						stringstream s;
						s << fac[j];
						string temp;
						s >> temp;
						for (int j = 0; j < temp.size(); j++)
							s1 = (temp[j] - 48) + s1;
					}
					
					else
						s1 += fac[j];
				}
					
				if (s1 == s2)
				{
					cout << i << endl;
					break;
				}
			}
		}
	}	
	return 0;
}
