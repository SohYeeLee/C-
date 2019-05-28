#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

int main()
{
	bool p[1041];
	memset (p, true, sizeof(p));
	p[0] = false;
	for (int i = 2; i <= sqrt(1040); i++)
		if (p[i])
			for (int j = i * i; j <= 1040; j+=i)
				p[j] = false;

	string a;
	while (cin >> a)
	{
		int sum = 0;
		int temp = 0;
		for (int i = 0; i < a.size(); i++)
		{	
			if (isalpha(a[i]))
			{
				temp = a[i] - 96;
				if (temp > 0)		 
					sum += temp;
				else
					sum += a[i] - 38;		
			}
		}
		if (p[sum])
			cout << "It is a prime word." << endl;
		else
			cout << "It is not a prime word." << endl;
	}
	return 0;
}
