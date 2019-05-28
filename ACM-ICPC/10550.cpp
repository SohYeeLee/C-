#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a[4];
    while (cin >> a[0] >> a[1] >> a[2] >> a[3] && (a[0] != 0 || a[1] != 0 || a[2] != 0 || a[3] != 0))
    {
        int temp = 0;
        //temp += 40 - a[1] + a[0];

        if (a[0] < a[1])
            temp += 40 - a[1] + a[0];
        else
            temp += a[0] - a[1];

        if (a[2] < a[1])
            temp += 40 + a[2] - a[1];
        else
            temp += a[2] - a[1];

        if (a[2] < a[3])
            temp += 40 - a[3] + a[2];
        else
            temp += a[2] - a[3];

        cout << temp * 9 + 1080 << endl;

    }
    return 0;
}
