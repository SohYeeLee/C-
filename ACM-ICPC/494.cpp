#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main()
{
	string a;
	while (getline(cin, a, '\n'))
	{
		if (a.size())
		{
			int count = 0;
			for (int i = 0; i < a.size();)
			{
				string s;
					
				while (isalpha(a[i]) && i < a.size())
				{
					s.push_back(a[i]);
					i++;
				}
					
				while (!isalpha(a[i]) && i < a.size())
					i++;	
				
				if (s.size())
					count++;
			}
			printf("%d\n", count);
		}
	}
	return 0;
}
