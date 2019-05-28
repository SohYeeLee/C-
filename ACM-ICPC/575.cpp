#include <iostream>
#include <math.h>
#include <string>

using namespace std;

int main()
{
	string a;
	while (cin >> a && a != "0")
	{
		long deci = 0;
		int p = 1;
		for (int i = a.length() - 1; i >= 0; i--)
		{
			if (a[i] != '0')
				deci += (a[i] - 48) * (pow(2.0, p) - 1);
			p++;
		}
		cout << deci << endl;
	}
	return 0;
}
