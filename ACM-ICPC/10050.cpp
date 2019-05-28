#include <iostream>

using namespace std;

int main()
{
    int test;
    cin >> test;

    while (test--)
    {
        int day, numparty;
        cin >> day >> numparty;

        int party[numparty];
        bool hartal[day + 1];           // number of working days lose
        memset (hartal, false, sizeof(hartal));

        for (int i = 0; i < numparty; i++)
        {
            cin >> party[i];
            int mul = party[i];

            for (int j = 1; mul <= day; j++)
            {
                if (mul % 7 != 6 && mul % 7 != 0)
                hartal[mul] = true;
                mul = party[i] * j;
            }
        }

        int sum = 0;
        for (int i = 1; i <= day; i++)
            if (hartal[i] == true)
                sum++;

        cout << sum << endl;
    }

    return 0;
}
