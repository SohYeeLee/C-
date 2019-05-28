#include <iostream>

using namespace std;

int main()
{
	int c;
	cin >> c;
		
	while (c--)
	{
		short x = 0;
		short o = 0;
		char a[3][3];
		int winx = 0;
		int wino = 0;
		
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				cin >> a[i][j];				
				if (a[i][j] == 'X')
					x++;
				else if (a[i][j] == 'O')
					o++;
			}
				
		// For row
		for (int i = 0; i < 3; i++)
		{
			if (a[i][0] == 'X' && a[i][1] == 'X' && a[i][2] == 'X')
				winx++;
			
			if (a[i][0] == 'O' && a[i][1] == 'O' && a[i][2] == 'O')
				wino++;
		}
		
		// for column
		for (int i = 0; i < 3; i++)
		{
			if (a[0][i] == 'X' && a[1][i] == 'X' && a[2][i] == 'X')
				winx++;
			
			if (a[0][i] == 'O' && a[1][i] == 'O' && a[2][i] == 'O')
				wino++;
		}
		
		// for diagonal
		if (a[0][0] == 'X' && a[1][1] == 'X' && a[2][2] == 'X')
			winx++;
			
		if (a[0][0] == 'O' && a[1][1] == 'O' && a[2][2] == 'O')
			wino++;
			
		if (a[0][2] == 'X' && a[1][1] == 'X' && a[2][0] == 'X')
			winx++;
		
		if (a[0][2] == 'O' && a[1][1] == 'O' && a[2][0] == 'O')
			wino++;
		
		
		if (winx && wino == 0 && x == (o + 1))			// there maybe a situation where the final placement of 'x' can win 2 lines
			cout << "yes" << endl;
		
		else if (winx == 0 && wino == 1 && x == o)
			cout << "yes" << endl;
			
		else if (winx == 0 && wino == 0 && (x == (o + 1) || x == o))
			cout << "yes" << endl;
			
		else
			cout << "no" << endl;
	}
	return 0;
}
