#include <iostream>
#include <vector>
using namespace std;

int main()
{
	string a, b;
	
	while (getline(cin, a), getline(cin, b))
	{
		vector<char> v1;
		vector<char> v2;
		
		for (int i = 0; i < a.size(); i++)
			v1.push_back(a[i]);
		
		for (int i = 0; i < b.size(); i++)
			v2.push_back(b[i]);
		
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
			
		vector<char> final;
		int i = 0;
		int j = 0;
		
		for (i, j; i < v1.size() && j < v2.size(); )
		{
			if (v1[i] == v2[j])
			{
				final.push_back(v1[i]);
				i++;
				j++;	
			}
			
			else if (v1[i] > v2[j])
				j++;
			else
				i++;
		}
		
		sort(final.begin(), final.end());
		
		for (int k = 0; k < final.size(); k++)
			cout << final[k];
		cout << endl;
	}
	return 0;
}
