#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define LOOP(i, n)	for (int i = 0; i < n; i++)

class a
{
	public:
		double x;
		bool state;			// true = begin, false = end.
		double coe;
		bool operator<(const a & A) const
		{
			return x < A.x;
		}
};

bool cmp (a A, a B)
{
	return (A.x < B.x);
}

int main()
{
	int c, line;
	double temp, x1, x2;

	scanf("%d", &c);
	
	while (c--)
	{
		scanf("%d", &line);
		vector <a> v;
		
		while (line--)
		{
			scanf("%lf%lf%lf%lf%lf", &x1, &temp, &x2, &temp, &temp);
			if (x1 > x2)
				swap(x1, x2);
				
			v.push_back((a){x1, true, temp});
			v.push_back((a){x2, false, temp});
		}
		sort(v.begin(),v.end());
		
		printf("%d\n", v.size() + 1);
		printf("-inf ");
		if (v.size() == 0)
			printf("+inf 1.000\n");
			
		else
		{
			printf("%.3lf 1.000\n", v[0].x);
			float cc = 1;			// current coefficient.
			
			LOOP(i, v.size() - 1)				// for (int i = 0; i < v.size(); i++)
			{
				if (v[i].state == true)			// it is begin of line.
					cc *= v[i].coe;

				
				else if (v[i].state == false)		// it is end of line.
					cc /= v[i].coe;
				
				printf("%.3lf %.3lf %.3lf\n", v[i].x, v[i + 1].x, cc);
			}
			printf("%.3lf +inf 1.000\n", v[v.size() - 1].x);
		}
		if (c)
			printf("\n");
	}
	return 0;
}
