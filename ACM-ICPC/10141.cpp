#include <cstdio>
#include <iostream>

using namespace std;

#define LOOP(i, a)	for (int i = 0; i < a; i++)

int main()
{
	int n, p;
	string a;
	int z = 0;
	
	while (scanf("%d%d", &n, &p) && n != 0)
	{
		string pr;		// name of proposal.
		string maxpr;
		int met;		// number of met requirement.
		int maxmet = 0;
		double price;
		double minprice = 0;
		
		if (z != 0)
			printf("\n");
		
		cin.ignore();
		
		LOOP(i, n)
			getline(cin, a);			// no need to store.
		
		LOOP(j, p)
		{
			getline(cin, pr);
			cin >> price >> met;
			cin.ignore(100, '\n');			
			
			LOOP(i, met)
			{
				getline(cin, a);
			}
	
			if (maxmet < met)
			{
				maxmet = met;
				maxpr = pr;
				minprice = price;
			}	
			
			else if (maxmet == met && price < minprice)
			{
				maxpr = pr;
				minprice = price;
			}
		}
		z++;
		printf("RFP #%d\n", z);
		cout << maxpr << endl;
	}
	
	return 0;
}
