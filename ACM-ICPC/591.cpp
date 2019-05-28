#include <iostream>

using namespace std;

int main()
{
	int n, c = 0;
	while (cin >> n && n != 0)
	{
		int h[n], sum = 0;
		
		for (int i = 0; i < n; i++)
		{
			cin >> h[i];
			sum += h[i];
		}
		int ave = sum / n;
		int move = 0;
		
		for (int i = 0; i < n; i++)
			if (h[i] > ave)
				move += h[i] - ave;
		
		cout << "Set #" << ++c << endl;
		cout << "The minimum number of moves is " << move << "."<< endl << endl;
	}	
	return 0;
}
