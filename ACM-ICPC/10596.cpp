#include <iostream>

using namespace std;

int main ()
{
	int N, R;
	while (cin >> N >> R)
	{
		int G[N][N];
		int v1, v2;
		
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				G[i][j] = 0;
				
		for (int k = 0; k < R; k++)
		{
			cin >> v1 >> v2;
			G[v1][v2]++;
			G[v2][v1]++;
		}
		
		bool possible = true;
		
		for (int i = 0; i < N; i++)
		{
			int degree = 0;
			int j = 0;
			for (j = 0; j < N; j++)
			{
				if (G[i][j] > 0)
				{
					degree = degree + G[i][j];
				}
			}
			if (i != j)
			{
				if (degree == 0 || degree % 2 != 0)
					possible = false;
			}
		}
		
		if (possible)
			cout << "Possible" << endl;
		else
			cout << "Not Possible" << endl;
	}
	return 0;
}
