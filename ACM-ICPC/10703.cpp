#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int main()
{
	int w, h, n, x1, x2, y1, y2;
	int a[501][501];
	
	while (scanf("%d %d %d", &w, &h, &n) && w != 0)
	{
		for (int i = 0; i < 501; i++)
			memset(a[i], false, sizeof(a[i]));
			
		int s = 0;			// number of spots.
		
		while (n--)
		{
			scanf ("%d %d %d %d", &x1, &y1, &x2, &y2);
			
			if ( x1 > x2 && y1 <= y2 ) 
				swap (x1, x2);
 
			else if ( x1 >= x2 && y1 >= y2 )
			{
				swap (x1, x2);
	        	swap (y1, y2);
	    	}
 
			else if (x1 <= x2 && y1 > y2 ) 
				swap (y1, y2);
			
			for ( int j = x1; j <= x2; j++) 
				for ( int k = y1; k <= y2; k++) 
					a[j][k] = true; 			
		}
		
		for ( int i = 1; i <= w; i++) 
			for ( int j = 1; j <= h; j++) 
				if (a[i][j] == false)
					s++;
					
		if (s == 0)
			printf ("There is no empty spots.\n");
	    
		else if (s == 1)
			printf ("There is one empty spot.\n");
	       
		else 
			printf ("There are %d empty spots.\n", s);
	}
	
	return 0;
}
