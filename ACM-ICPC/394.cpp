#include <iostream>
#include <vector>

using namespace std;

struct a
{
	string name;
	int base;
	int size;
	int d;
	int lb[10];
	int ub[10];
};

int main()
{
	int aa, ref;
	cin >> aa >> ref;
	
	vector <a> array;
	while (aa--)
	{
		a temp;
		cin >> temp.name;
		cin >> temp.base;
		cin >> temp.size;
		cin >> temp.d;
		for (int i = 0; i < temp.d; i++)
		{
			cin >> temp.lb[i];
			cin >> temp.ub[i];
		}
			
		array.push_back(temp);
	}
	
	while (ref--)
	{
		string b;
		cin >> b;
		for (int i = 0; i < array.size(); i++)
			if (b == array[i].name)
			{
				int temp[array[i].d];
				
				cout << b << "[";
				
				for (int j = 0; j < array[i].d; j++)
				{
					cin >> temp[j];			
					cout << temp[j];
					
					if (j != array[i].d - 1)
						cout << ", ";
				}
				
				int add = array[i].base;
				int CD = array[i].size;
				
				for (int j = array[i].d - 1; j >= 0; j--)
				{
					add += CD * (temp[j] - array[i].lb[j]);
					CD = CD * (array[i].ub[j] - array[i].lb[j] + 1);
				}
				
				cout << "] = " << add << endl;
				
				break;
			}
	}
	return 0;
}
