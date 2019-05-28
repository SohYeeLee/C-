#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int test;
    int c = 0;
    cin >> test;

    while (c < test)
    {
        int a, b, sum = 0;
        cin >> a >> b;
        if (a % 2 == 0)
            a++;

        if (b % 2 == 0)
            b--;

        for (; a <= b; a += 2)
            sum += a;

        cout << "Case " << ++c << ": " << sum << endl;
    }
    return 0;
}
