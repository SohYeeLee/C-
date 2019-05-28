#include <iostream>
#include <cctype>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

struct sort_pred {
    bool operator()(const std::pair<char,int> &left, const std::pair<char,int> &right) {
        return left.second > right.second;
    }
};

int main()
{
	vector <pair <char, int> >v;
	
	for (int i = 0; i < 26; i++)
	{
		v.push_back(make_pair(65 + i, 0));
	}
	
	int line;
	cin >> line;
	cin.ignore('1000', '\n');
	
	string a[line];
	int i = 0;
	
	while (i < line)
	{
		string b;
		getline(cin, b);
		a[i] = b;
		
		for (int j = 0; j < a[i].size(); j++)
		{
			if (isalpha(a[i][j]))
			{
				char z = toupper(a[i][j]);
				v[z - 65].second++;
			}
			
		}
		i++;
	}
	
	stable_sort(v.begin(), v.end(), sort_pred() );
	
	for (int i = 0; i < 26; i++)
	{
		if (v[i].second > 0)
			cout << v[i].first << " " << v[i].second << endl;
	}
	return 0;
}
