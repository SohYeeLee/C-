#include <stdio.h>
#include <algorithm>

using namespace std;

int main()
{
	int test;
	int a[3];
	scanf("%d", &test);
	int c = 0;
	
	while (test--)
	{
		scanf("%d", &a[0]);
		scanf("%d", &a[1]);
		scanf("%d", &a[2]);
		sort(a, a+3);
		
		printf("Case %d: %d\n", ++c, a[1]);
	}
	return 0;
}
