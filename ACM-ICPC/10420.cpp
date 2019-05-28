#include <iostream>
#include <map>

using namespace std;

int main()
{
	int a;
	cin >> a;
	
	string c;		// country name;
	string dum;		// dummmy
	map <string, int> m;
	map<string,int>::iterator it;
	
	while (a--)
	{
		cin >> c;
		getline(cin, dum);
		
		it = m.find(c);

		if (it == m.end())
			m.insert(pair <string, int> (c, 1));
		else
			it->second++;
	}
	
	for (it = m.begin(); it != m.end(); it++)
		cout << it->first << " " << it->second << endl;
	return 0;
}
