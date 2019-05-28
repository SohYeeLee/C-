#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main()
{
	bool a[1000001];
	
	memset(a, true, sizeof(a));
	a[1] = false;		// 1 is not a prime.
	
	for (int i = 2; i <= sqrt(1000001); i++)
	{
		if (a[i])		// If a is a prime.
			for (int j = i * 2; j < 1000001; j = j + i)
				a[j] = false;			
	}
	
	string b;
	while (getline(cin, b))
	{
		int temp1 = atoi(b.c_str());
		if (!a[temp1])		// not a prime.
			cout << b << " is not prime." << endl;
	
		else			// is a prime
		{
			string c;
			for(int i = b.size() - 1; i >= 0; i--)
				c = c + b[i];
			
			int temp2;
			temp2 = atoi(c.c_str());
			
			if (a[temp1] && a[temp2] && temp1 != temp2)
				cout << temp1 << " is emirp." << endl;
				
			else	
				cout << temp1 << " is prime." << endl;
		}
	}
	
	return 0;
}
