#include <iostream>

using namespace std;

int main()
{	
	int testcase;
	
	cin >> testcase;
	while (testcase != 0)
	{
		int farmer;
		
		cin >> farmer;
		
		double total = 0;
		while (farmer != 0)
		{
			double area, animal, envi;
			
			cin >> area >> animal >> envi;
			total = total + ((area / animal) * envi * animal);
			
			farmer--;
		}
		cout << total << endl;
		testcase--;
	}
			
	return 0;
}
