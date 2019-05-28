#include <iostream>

void swap(long long &a, long long &b)
{
	long long temp = a;
	a = b;
	b = temp;
}

using namespace std;

int main()
{
	long long input[2];
	bool s = false;
	while (cin >> input[0] >> input[1])
	{
		s = false;
		if (input[0] > input[1])
		{
			swap(input[0], input[1]);
			s = true;
		}
			
		long long i = input[0];
		long long max = 0;
		
		while (i <= input[1])
		{
			long long a = i;
			long long counter = 1;
			
			while (a != 1)
			{			
				if (a % 2 == 0)
					a = a / 2;
				
				else 
					a = 3 * a + 1;
				
				counter++;	
			}
			if (counter > max)
				max = counter;
	
			i++;
		}
		if (s)
			swap(input[0],input[1]);
		cout << input[0] << " " << input[1] << " " << max << endl;
		
	}
	return 0;
}
