#include <iostream>
#include <string>

using namespace std;

int main()
{	
	string s;
	int i = -1;
	while (getline(cin, s))
	{
		size_t t = s.find("\"");
		string temp;
		
		while (t != string::npos)
		{
			i++;
			if (i % 2 == 0)
				temp = "``";
			else
				temp = "''";
				
			s.replace(t, 1, temp);
			t = s.find("\"", t);
		}
		cout << s << endl;
	}
	
	return 0;
}
