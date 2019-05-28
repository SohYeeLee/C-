#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	string input, a, b;
	int count = 0;
	while (cin >> a >> b)
	{
		if (count != 0)
			cout << endl;
		cout << a << " (to " << b << ")" << endl;		
		string s;
		
		if (a.size() - 1 > 0)
			for (int i = 0; i < a.size() - 2; i++)		// Copy the root word.
				s = s + a[i];
				
		if (a.size() - 1 > 0 && a[a.size() - 1] == 'r')
		{
			char m = 243;
			string n;
			
			if (a[a.size() - 2] == 'a')			// First
			{
				cout << left << setw(10) << "eu" << s << 'o' << endl;
				cout << left << setw(10) << "tu" <<  s << "as" << endl;
				cout << left << setw(10) << "ele/ela" << s << 'a' << endl;
				cout << left << 'n' << m << setw(8) << 's' << s << "amos" << endl;
				cout << left << 'v' << m << setw(8) << 's' << s << "ais" << endl;
				cout << left << setw(10) << "eles/elas" << s << "am" << endl;
			}
			else if (a[a.size() - 2] == 'e')		// Second
			{
				cout << left << setw(10) << "eu" << s << 'o' << endl;
				cout << left << setw(10) << "tu" <<  s << "es" << endl;
				cout << left << setw(10) << "ele/ela" << s << 'e' << endl;
				cout << left << 'n' << m << setw(8) << 's' << s << "emos" << endl;
				cout << left << 'v' << m << setw(8) << 's' << s << "eis" << endl;
				cout << left << setw(10) << "eles/elas" << s << "em" << endl;
			}
			else if (a[a.size() - 2] == 'i')		// Third
			{
				cout << left << setw(10) << "eu" << s << 'o' << endl;
				cout << left << setw(10) << "tu" <<  s << "es" << endl;
				cout << left << setw(10) << "ele/ela" << s << 'e' << endl;
				cout << left << 'n' << m << setw(8) << 's' << s << "imos" << endl;
				cout << left << 'v' << m << setw(8) << 's' << s << "is" << endl;
				cout << left << setw(10) << "eles/elas" << s << "em" << endl;
			}
			else
				cout << "Unknown conjugation" << endl;		
		}
		else
			cout << "Unknown conjugation" << endl;
		count++;
	}
	
	return 0;
}
