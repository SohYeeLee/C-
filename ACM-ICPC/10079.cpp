#include <iostream>

using namespace std;

int main()
{
	long long a;
	
	while (cin >> a && a >= 0)
		cout << (a + 1) * a / 2 + 1 << endl;
		
	return 0;
}
