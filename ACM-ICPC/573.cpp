#include <iostream>

using namespace std;

int main()
{
	float h, u, d, f;	// h = height of well, u = distance that the snail can climb, d = sliding distance, f = fatigue factor.
	float c;			// current height of the snail.
	int i;
	float sh = 0;		// fatigue height.
	
	while (cin >> h >> u >> d >> f && h != 0)
	{
		sh = f * u / 100.0;		// fatigue height.
		
		for (i = 1,c = 0; ;i++)
		{
			c += u;
			if( c > h )
				break;
				
			c -= d;
			
			if( c < 0)
				break;
				
			u -= sh;
			
			if (u < 0)
				u = 0;
		} 
		
		if (c > h)
			cout << "success on day " << i << endl;
		else
			cout << "failure on day " << i << endl;
	}
	
	return 0;
}
