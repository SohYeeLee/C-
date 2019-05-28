#include <stdio.h>
#include <sstream>
#include <iostream>

using namespace std;

int main()
{
	long a;
	
	while (cin >> a)
	{
		int h = a / 1000000;
		
		long m = a % 1000000;
		m /= 10000;
		
		int s = a % 10000;
		s /= 100;
		
		int c = a % 100;	
		long ans = ((h * 360000.0) + (m * 6000) + (s * 100) + c) / 0.864;
		
		string d;
		stringstream ss;
		ss << ans;
		d = ss.str();
		
		for (int i = 0; i < 6; i++)
		{
			ans = ans / 10;
			if (ans == 0)
				cout << "0";
		}
		cout << d << endl;
	}
	return 0;
}
