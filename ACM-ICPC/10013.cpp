#include <iostream>
using namespace std;

int main()
{
	long input;
	cin >> input;
	
	while (input != 0)
	{
		long long line;
		cin >> line;
		long long j = 0;
		long long z[line];
		
		while (j != line)
		{
			long long a;
			long long b;			
			cin >> a;
			cin >> b;
			z[j] = a + b;
			j++;
		}
		
		for (long long i = line - 1; i >= 0; i--)
		{
			long c = 0;
			while (z[i] >= 10)
			{
				z[i] = z[i] - 10;
				c++;
			}
			z[i - 1] = z[i - 1] + c;
		}
		
		if (z[0] > 0)
			cout << z[0];
		for (long long i = 1; i < line; i++)
			cout << z[i];
		
		input--;
		
		if (input != 0)
			cout << endl << endl;
		else
			cout << endl;
	}
	return 0;
}
