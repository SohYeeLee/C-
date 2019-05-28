#include <iostream>

using namespace std;

int main()
{
	string a;
	
	while (getline (cin, a))
	{
		for (int i = 0; i < a.size(); i++)
		{
			string b;
			while (a[i] != ' ' && i < a.size())
			{
				b += a[i];
				i++;
			}
			for (int j = b.size() - 1; j >= 0; j--)
				cout << b[j];
			
			if (a[i] == ' ' && i < a.size())
				cout << ' ';
		}
		cout << endl;
	}
	return 0;
}
