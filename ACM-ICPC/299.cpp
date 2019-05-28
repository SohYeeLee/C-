#include <iostream>

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void sort(int a[], int size, int &times)
{
	bool sorted = false;
	
	for (int i = 1; i < size && !sorted; i++)
	{
		sorted = true;
		for (int j = 0; j < size - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
				sorted = false;
				times++;
			}
		}
	}
}
				
using namespace std;

int main()
{
	int input;		// number of test case.
	
	cin >> input;
	while (input > 0)
	{
		int c;
		int order[50];
		int times = 0;
		
		cin >> c;			// number of catridge.
		
		for(int i = 0; i < c; i++)
			cin >> order[i];		// order of the catridge.
		
		sort(order, c, times);
		
		cout << "Optimal train swapping takes " << times << " swaps." << endl;
		input--;
		
	}
	
	return 0;
}
