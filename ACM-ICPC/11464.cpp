#include <iostream>
using namespace std;

int main()
{
	int input;
	cin >> input;
	
	while (input != 0)
	{
		int num;
		cin >> num;
		int a[num][num];
		int b[num][num];
		
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				cin >> a[i][j];
				b[i][j] = 0;
			}
		}
		
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				if (i - 1 >= 0)
					b[i][j] = b[i][j] + a[i - 1][j];
				if (i + 1 < num)
					b[i][j] = b[i][j] + a[i + 1][j];
				if (j - 1 >= 0)
					b[i][j] = b[i][j] + a[i][j - 1];
				if (j + 1 < num)
					b[i][j] = b[i][j] + a[i][j + 1];
			}
		}
		bool even = true;
		int min = 0;
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				if (b[i][j] % 2 != 0)
					even = false;
			}
		}
		
		if (even)
			min = 0;
		else
		{
			int k = 0;
			for (int i = 0; i < num; i++)
			{
				for (int j = 0; j < num; j++)
				{
					
						
		}
		input--;
	}
	
	return 0;
}
