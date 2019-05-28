#include <stdio.h>

int main()
{
	int test;
	int a;
	scanf("%d", &test);
	
	while (test--)
	{
		scanf("%d", &a);

		//((((a / 567 * 9) + 7492) * 235) / 47) - 498;
		a = (a * 63 + 7492) * 5 - 498;		// optimization
		if (a < 0)
			a = -a;
		
		printf("%d\n", ((a / 10) % 10));
	}
	return 0;
}
