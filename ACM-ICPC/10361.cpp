#include <iostream>
#include <string>
using namespace std;

int main()
{
	int testcase;
	cin >> testcase;		// No of test case.
	cin.ignore();
	
	while (testcase != 0)
	{	
		string a, b, f1, f2, d1, d2;
		getline(cin, a);
		getline(cin, b);
			
		int i = 0;
		while (a[i] != '<' && i < a.size())
		{
			cout << a[i];
			i++;
		}

		i++;		// get next char.
		
		while (a[i] != '>' && i < a.size())
		{
			cout << a[i];
			f1 = f1 + a[i];
			i++;
		}
		
		i++;
		while (a[i] != '<' && i < a.size())
		{
			cout << a[i];
			d1 = d1 + a[i];
			i++;
		}
		
		i++;
		
		while (a[i] != '>' && i < a.size())
		{
			cout << a[i];
			f2 = f2 + a[i];
			i++;
		}
		i++;
		
		while (i < a.size())
		{
			cout << a[i];
			d2 = d2 + a[i];
			i++;
		}
		cout << endl;
		string c = b.substr(0, b.size() - 3);
		cout << c << f2 << d1 << f1 << d2 << endl;
		testcase--;
	}
	return 0;
}
