#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a, b;

    while (getline(cin, a) && getline(cin, b))
    {
        int xa[26] = {0};
        int xb[26] = {0};

        for (int i = 0; i < a.size(); i++)
        {
            int temp = a[i];
            xa[temp - 97]++;
        }

        for (int i = 0; i < b.size(); i++)
        {
            int temp = b[i];
            xb[temp - 97]++;
        }

        for (int i = 0; i < 26; i++)
        {
            int time = 0;

            if (xa[i] == xb[i])
                time = xa[i];

            else if (xa[i] > xb[i])
                time = xb[i];

            else if (xa[i] < xb[i])
                time = xa[i];

            for (int j = 0; j < time; j++)
                cout << char(97 + i);
        }
        cout << endl;
    }
    return 0;
}
