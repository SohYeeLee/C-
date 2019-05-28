#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

int main()
{
	string name;
	
	while (cin >> name)
	{
		vector<string> v;
		
		string a = name;
		string b = name;
	
		for (int j = 0; j < 10; j++)
		{
			prev_permutation(a.begin(), a.end());
			v.push_back(a);
		}
		
		reverse(v.begin(), v.end());
		v.push_back(name);
		
		for (int i = 0; i < 10; i++)
		{
			next_permutation(b.begin(), b.end());
			v.push_back(b);
		}
		
		vector <pair<int, int> > aa;
		for (int i = 0; i < v.size(); i++)
		{
			vector<int> temp;
			string z = v[i];
			for (int j = 0; j < z.size() - 1; j++)
				temp.push_back(abs(z[j] - z[j + 1]));
			sort(temp.begin(), temp.end());
			aa.push_back(make_pair(i, temp[0]));
		}
		
		int max = 0;
		for (int i = 0; i < aa.size(); i++)
		{
			if (aa[i].second > max)
				max = aa[i].second;
		}
		
		for (int i = 0; i < aa.size(); i++)
		{
			if (aa[i].second == max)
			{
				cout << v[i] << aa[i].second << endl;
				break;
			}
		}
	}
	return 0;
}
