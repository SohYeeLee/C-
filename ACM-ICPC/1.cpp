#include <iostream>
using namespace std;

int main()
{
    long long n;
    long long n1;
    long long size;
    long long max = 0;
    long long large;
    long long small;
    while (cin >> n >> n1)
    {
        if (n > n1)
        {
            large = n;
            small = n1;
        }

        else
        {
            large = n1;
            small = n;
        }
        max = 0;

        for (long long j = small; j <= large; j++)
        {
            long long i = j;
            long long loop = 1;
            while (i != 1)
            {
                if (i % 2 == 0)
                    i = i / 2;
                else
                    i = 3 * i + 1;

                loop++;
            }
                if (loop > max)
                    max = loop;
        }
            cout << n << " " << n1 << " " << max << endl;
    }

    return 0;
}
