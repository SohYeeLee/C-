#include <iostream>

using namespace std;

int main()
{
    int a, b, count = 0;

    while (cin >> a >> b && a != 0 && b != 0)
    {
        count++;
        char x[a][b];

        for (int i = 0; i < a; i++)
            for (int j = 0; j < b; j++)
            cin >> x[i][j];

        if (count > 1)
            cout << endl;

        cout << "Field #" << count << ":";
        for (int i = 0; i < a; i++)
        {
            cout << endl;

            for (int j = 0; j < b; j++)
            {
                if (x[i][j] == '.')
                {
                    x[i][j] = '0';
                    // top left
                    if (i > 0 && j > 0 && x[i - 1][j - 1] == '*')
                        x[i][j]++;

                    // top
                    if (i > 0 && x[i - 1][j] == '*')
                        x[i][j]++;

                    // top right
                    if (i > 0 && j + 1 < b && x[i - 1][j + 1] == '*')
                        x[i][j]++;

                    // left
                    if (j > 0 && x[i][j - 1] == '*')
                        x[i][j]++;

                    // right
                    if (j + 1 < b && x[i][j + 1] == '*')
                        x[i][j]++;

                    // bottom left
                    if (i + 1 < a && j > 0 && x[i + 1][j - 1] == '*')
                        x[i][j]++;

                    // bottom
                    if (i + 1 < a && x[i + 1][j] == '*')
                        x[i][j]++;

                    // bottom right
                    if (i + 1 < a && j + 1 < b && x[i + 1][j + 1] == '*')
                        x[i][j]++;

                }
                cout << x[i][j];
            }
        }
        cout << endl;
    }

    return 0;
}
