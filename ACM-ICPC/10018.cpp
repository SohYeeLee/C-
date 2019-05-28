#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

bool ispali(string s)
{
	if (s.size() % 2 == 0)		// even char
	{
		for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--)
		{
			if (s[i] != s[j])
				return false;
		}
	}

	else
	{
		int limit = floor(s.size() / 2);
		for (int i = 0, j = s.size() - 1; i < limit; i++, j--)
		{
			if (s[i] != s[j])
				return false;
		}
	}
	return true;
}

int main()
{
	int test;
	cin >> test;

	while (test > 0)
	{
		string s;
		cin >> s;

		int c = 0;
		bool pali = ispali(s);
		unsigned long sum = atol(s.c_str());
		unsigned long a;
		unsigned long b;
		while(!pali)
		{
			a = atol(s.c_str());
			reverse(s.begin(), s.end());
			b = atol(s.c_str());
			sum = a + b;
			stringstream ss;
			ss << sum;
			s = ss.str();
			pali = ispali(s);
			c++;
		}
		test--;
		cout << c << " " << sum << endl;
	}
	return 0;
}

