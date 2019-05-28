#include <iostream>

using namespace std;

int main()
{
	long long a, b;
	
	while (cin >> a >> b && (a != 0 || b != 0))
	{
		int time = 0;
		short carry = 0;
		
		while (a > 0 || b > 0)
		{
			int r1 = a % 10;
			int r2 = b % 10;
			
			if (r1 + r2 + carry > 9)
			{
				time++;
				carry = 1;
			}
			
			else
				carry = 0;
			
			a = a / 10;
			b = b / 10;
		}
		
		if (time == 0)
			cout << "No carry operation." << endl;
		
		else if (time == 1)
			cout << "1 carry operation." << endl;
		
		else
			cout << time << " carry operations." << endl;
	}
	return 0;
}
