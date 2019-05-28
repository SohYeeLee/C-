#include <iostream>
using namespace std;

int gcd(int a, int b)
{
  int c = a % b;
  while(c != 0)
  {
    a = b;
    b = c;
    c = a % b;
  }
  return b;
}

/*int gcd(int a, int b)
{
	if (a == 0)
		   return b;
	else
	{
		while (b != 0)
		{
			if (a > b)
			   a = a - b;
			else
			   b = b - a;
		}
		return a;
	}
}*/

/*int gcd(int a, int b)
{
    if (b == 0)
       return a;
    else
       return gcd(b, a % b);
}*/


int main()
{
	int input;
	cin >> input;
	while (input != 0)
	{
		long G = 0;

		for (int i = 1; i < input; i++)
			for (int j = i + 1; j <= input; j++)	
				G += gcd(i, j);
		cout << G << endl;
		cin >> input;
	}

	return 0;
}
