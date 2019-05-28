#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	int input;
	cin >> input;
	while (input != 0)
	{		
		int a = input * input;
		int b = input;
		bool found = false;
		vector<int> v;
		v.push_back(input);
		
		while (!found)
		{
			stringstream ss;
			ss << a;
			string s = ss.str();
			string temp;
			
			if (s.size() != 8)
			{
				int i = 0;
				for (i; i < 8 - s.size(); i++)
					temp = temp + '0';
				for (i = 0; i < s.size(); i++)
					temp = temp + s[i];

				s.clear();
				s = temp;
			}
			temp.clear();
			temp = "0000";
			temp[0] = s[2];
			temp[1] = s[3];
			temp[2] = s[4];
			temp[3] = s[5];
			
			b = atoi(temp.c_str());
			
			for (int i = 0; i < v.size(); i++)
			{
				if (v[i] == b)
					found = true;
			}
			if (!found)
				v.push_back(b);
			a = b * b;
		}
		cout << v.size() << endl;
		cin >> input;
	}
	
	return 0;
}
