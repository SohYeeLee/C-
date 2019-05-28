#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
	int test;
	cin >> test;
	int count = 0;
	
	bool prime[2001];
		
	memset(prime, true, sizeof(prime));
	prime[0] = prime[1] = false;
	
	for (int i = 2; i <= sqrt(2000.0); i++)
	{
		if (prime[i])
			for (int j = i * i; j < 2000.0; j+= i)
				prime[j] = false;
	}
	
	while (test--) 
	{
		count++;
		string a;
		cin >> a;
		int number[10];
		int lower[26];
		int upper[26];
		
		memset(number, 0, sizeof(number));
		memset(lower, 0, sizeof(lower));
		memset(upper, 0, sizeof(upper));
		
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] >= 48 && a[i] <= 57)
				number[a[i] - 48]++;
			
			else if (a[i] >= 65 && a[i] <= 90)
				upper[a[i] - 65]++;
				
			else
				lower[a[i] - 97]++;
		}

		
		bool found = false;
		
		cout << "Case " << count << ": ";
		
		for (int i = 0; i < 10; i++)
			if (number[i] && prime[number[i]])
			{
				found = true;
				cout << char(i + 48);
			}
		
		for (int i = 0; i < 26; i++)
			if (upper[i] && prime[upper[i]])
			{
				found = true;
				cout << char(i+ 65);
			}
		for (int i = 0; i < 26; i++)
			if (lower[i] && prime[lower[i]])
			{
				found = true;
				cout << char(i + 97);
			}
		
		if (!found)
			cout << "empty";
		cout << endl;
	}
	return 0;
}	