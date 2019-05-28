#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
	int n, m, c;
	bool state[20];
	int con[20];
	int z = 0;
	
	while (scanf("%d%d%d", &n, &m, &c) && n != 0)
	{
		memset(state, false, sizeof(state));
		memset(con, 0, sizeof(con));
		for (int i = 0; i < n; i++)
			scanf("%d", &con[i]);
		
		bool blown = false;
		int temp;
		int current = 0;
		int max = 0;
		
		for (int i = 0; i < m; i++)
		{
			scanf("%d", &temp);
			temp--;			// Array start from 0.
			state[temp] = state[temp] ^ true;
			
			if (!blown)
			{
				if (state[temp])
					current += con[temp];
				
				else
					current -= con[temp];
				
				if (current > c)
					blown = true;
				
				else
					if (max < current)
						max = current;
			}
		}
		printf("Sequence %d\n", ++z);
		if (blown)
			printf("Fuse was blown.\n\n");
		else
		{
			printf("Fuse was not blown.\n");
			printf("Maximal power consumption was %d amperes.\n\n", max);
		}
	}
	return 0;
}
