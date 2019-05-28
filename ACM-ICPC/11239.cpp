#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct project {
	string name;
	int num;
};

bool myfunction (project a, project b)
{
	return a.num > b.num;
}

bool myfunction2 (project a, project b)
{
	return a.name < b.name;
}

int main()
{
	string line;
	set <string> id[1000];
	vector <project> p;
	set <string> repeat;
	
	int count = -1;
	while (getline(cin, line) && line[0] != '0')
	{
		if (line[0] == '1')
		{
			for (int i = 0; i < p.size(); i++)
			{
				p[i].num = id[i].size();
				for (set<string>::iterator itt = id[i].begin(); itt != id[i].end(); itt++)
				{
					string temp1 = *itt;
					for (set<string>::iterator it = repeat.begin(); it != repeat.end(); it++)
					{
						string temp2 = *it;
						if (strcmp(temp1.c_str(), temp2.c_str()) == 0)
							p[i].num--;
					}
				}
			}
			sort (p.begin(), p.end(), myfunction2);
			stable_sort(p.begin(), p.end(), myfunction);
			
			for (int i = 0; i < p.size(); i++)
				cout << p[i].name << " " << p[i].num << endl;
			
			// clear id
			for (int i = 0; i < 1000; i++)
				id[i].clear();
			
			p.clear();
			count = -1;			// reset number of project.
		}
		
		else
		{
			if (isupper(line[0]))
			{
				/*if (count >= 0)
					p[count].num = id[count].size();*/
				count++;
				project temp;
				temp.name = line;
				temp.num = 0;
				p.push_back(temp);
			}
			
			else if (islower(line[0]))
			{
				id[count].insert(line);
				
				for (int i = 0; i < count; i++)
				{
					for (set<string>::iterator it = id[i].begin(); it != id[i].end(); it++)
					{
						string temp = *it;
						if (strcmp(temp.c_str(), line.c_str()) == 0)			// id repeated;
							repeat.insert(line);
					}
				}
			}	
		}
	}
	return 0;
}
