#include <iostream>
#include <set>

using namespace std;

int main()
{
	set <string> dictionary;
	string line;
	
	getline(cin, line);
	
	while (!cin.fail())
	{
		int i = 0;
		while (i < line.size())
		{
			string temp;
			
			while (!isalpha(line[i]) && i < line.size())
				i++;
				
			while(isalpha(line[i]) && i < line.size())
			{
				line[i] = tolower(line[i]);
				temp = temp + line[i];
				i++;
			}
			if (temp.size() > 0)
				dictionary.insert(temp);
		}
		getline(cin, line);
	}

	for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
		cout << *it << endl;
	return 0;
}
