#include <iostream>
using namespace std;

int main()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	
	while (a != 0 && b != 0 && c != 0 && d != 0)
	{
		int move = 0;
		bool diagonal = false;
		
		while (a != c && b != d)
		{
			diagonal = true;
			if (a > c && b > d)
			{
				a--;
				b--;
			}
			
			else if (a > c && b < d)
			{
				a--;
				b++;
			}
			
			else if (a < c &&  b < d)
			{
				a++;
				b++;
			}
			
			else if (a < c && b > d)
			{
				a++;
				b--;
			}
		}
		if (diagonal)
			move++;
		
		if (a == c && b == d)
		{}
		
		else
			move++;
		
		cout << move << endl;
		cin >> a >> b >> c >> d;
	}
						
	return 0;
}
