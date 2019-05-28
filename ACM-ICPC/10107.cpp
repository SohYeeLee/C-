#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
	vector <long> v;
	long long a;
	while (cin >> a)
	{
		v.push_back(a);
		sort(v.begin(), v.end());
		if (v.size() & 1)	// Odd
			cout << v[ceil(v.size() / 2)] << endl;
		else
		{
			long long t1 = v[v.size() / 2 - 1];
			long long t2 = v[v.size() / 2];
			unsigned long long b = (t1 + t2) / 2;
			cout << b << endl;
		}
	}
	return 0;
}
