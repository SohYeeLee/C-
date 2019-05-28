#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct dictionary {
	string word;
	string arrangement;
};

bool myfunction (dictionary a, dictionary b)
{
	return a.word < b.word;
}

int main()
{
    string a;
    vector <dictionary> d;  // Store dictionary

    while (cin >> a && a != "XXXXXX")
    {
		dictionary temp;
		int count[26];
		memset(count, 0, sizeof(count));
		
		temp.word = a;
		for (int i = 0; i < a.size(); i++)
			count[(a[i] - 97)]++;
		
		for (int i = 0; i < 26; i++)
			temp.arrangement += (count[i] + 48);
		
        d.push_back(temp);
    }

    sort(d.begin(), d.end(), myfunction);

    while (cin >> a && a != "XXXXXX")
    {
		int count[26];
		memset(count, 0, sizeof(count));
		
		for (int i = 0; i < a.size(); i++)
			count[(a[i] - 97)]++;
		
		string s = "";
		for (int i = 0; i < 26; i++)
			s += (count[i] + 48);
		
		bool found = false;
		for (int i = 0; i < d.size(); i++)
			if (strcmp(d[i].arrangement.c_str(), s.c_str()) == 0) 
			{
				found = true;
				cout << d[i].word << endl;
			}
		
		if (!found)
			cout << "NOT A VALID WORD" << endl;
		cout << "******" << endl;
    }
    return 0;
}
