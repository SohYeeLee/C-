#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	string a;
	printf("         NAME");
	printf("                     SOUNDEX CODE\n");
	
	while (cin >> a)
	{
		int len = 0;		// Length of current soundex code.
		short last = 0;
		
		printf("         ");
		cout << setw(25) << left << a;
		cout << a[0];
		for (int i = 0; i < a.size(); i++)
		{
			if (len < 3)
			{
				if (a[i] == 'B' || a[i] == 'P' || a[i] == 'F' || a[i] == 'V')
				{
					if (last != 1 && i != 0)
					{
						printf("1");
						len++;
					}
					last = 1;
				}
				
				else if (a[i] == 'C' || a[i] == 'S' || a[i] == 'K' || a[i] == 'G' || a[i] == 'J' || 
						 a[i] == 'Q' || a[i] == 'X' || a[i] == 'Z' )
				{
					if (last != 2 && i != 0)
					{
						printf("2");
						len++;
					}
					last = 2;
				}
				
				else if (a[i] == 'D' || a[i] == 'T' )
				{
					if (last != 3 && i != 0)
					{
						printf("3");
						len++;
					}
					last = 3;
				}
				
				else if (a[i] == 'L')
				{
					if (last != 4 && i != 0)
					{
						printf("4");
						len++;
					}
					last = 4;
				}
				
				else if (a[i] == 'M' || a[i] == 'N')
				{
					if (last != 5 && i != 0)
					{
						printf("5");
						len++;
					}
					last = 5;
				}
				
				else if (a[i] == 'R')
				{
					if (last != 6 && i != 0)
					{
						printf("6");
						len++;
					}
					last = 6;
				}
				else
					last = 0;
			}
		}
		while (len < 3)
		{
			printf("0");
			len++;
		}
		printf("\n");		
	}
	printf("                   END OF OUTPUT\n");
	
	return 0;
}
