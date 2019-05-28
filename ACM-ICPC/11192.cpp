#include <iostream>

using namespace std;

int main()
{
	string s; int g;
	while (cin >> g >> s && g != 0)
	{
		int d = s.size() / g;
		for (int i = d - 1; i < s.size(); i+=d)
		{
			for (int j = i; j > i - d; j--)
				cout << s[j];
		}
		cout << endl;
	}
	
	return 0;
}
