#include <iostream>
#include <valarray>
#include <queue>
#include <iomanip>
using namespace std;

int main()
{
	int test;
	cin >> test;
	
	while (test > 0)
	{
		int students;
		
		cin >> students;
		priority_queue<int> p;
		int a[students];
		
		for (int i = 0; i < students; i++)
		{
			cin >> a[i];
			p.push(a[i]);
		}
		
		valarray <int> v(a, students);
		double total = v.sum();
		double average = total / students;
		
		double k = 0;
		while (!p.empty())
		{
			int temp = p.top();
			p.pop();
			if (temp > average)
				k++;
			else
				break;
		}
		cout << fixed << setprecision(3) << showpoint << (k / students * 100) << "%" <<  endl;
		test--;
	}
	
	return 0;
}
