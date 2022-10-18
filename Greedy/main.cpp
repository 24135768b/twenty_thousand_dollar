/* C++ template design by CTHua */
#include <bits/stdc++.h>
using namespace std;
// type
typedef pair<int, int> PII;
typedef long long Lint;
// macro
#define F first
#define S second
#define pb push_back
#define mkp make_pair
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define _fio                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);
#define DEBUG cout << "debug" << endl;
#define PRINT(x)          \
    for (auto a : x)      \
        cout << a << " "; \
    cout << endl;

// #define SIZE 6
// #define N 4
#define SIZE 5050
#define N 101

double wij[N + 1][N + 1] = {0};
int used[N + 1] = {0};
int result[N + 1] = {0};
vector<int> A, B;

double calcMaxW(int n, double max, vector<int> &X)
{
    int s;
    double sum = 0;

    s = SZ(X);
    for (int i = 0; i < s; i++)
    {
        sum += wij[n][X[i]];
    }
    return sum;
}

void greedy()
{
    int t = N;
    while (t--)
    {
        double max = -1e9, sumA, sumB;
        int maxi = -1;
        int pushWhat = 0; // 0 is push A, 1 is push B
        for (int i = 1; i <= N; i++)
        {
            if (used[i] != 0)
                continue;

            sumA = calcMaxW(i, max, A);
            sumB = calcMaxW(i, max, B);

            int pushA = sumA - sumB;
            int pushB = sumB - sumA;

            if (pushA > pushB)
            {
                if (pushA > max)
                {
                    max = pushA;
                    maxi = i;
                    pushWhat = 0;
                }
            }
            else
            {
                if (pushB > max)
                {
                    max = pushB;
                    maxi = i;
                    pushWhat = 1;
                }
            }
        }
        if (pushWhat == 0)
        {
            A.pb(maxi);
            result[maxi] = 1;
        }
        else
        {
            B.pb(maxi);
            result[maxi] = -1;
        }
        used[maxi] = 1;
    }
}

double calcE()
{
    double sum = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            sum += wij[i][j] * result[i] * result[j];
        }
    }
    return sum;
}

int main(int argc, char **argv)
{
    _fio;
    for (int i = 0; i < SIZE; i++)
    {
        int n, m;
        double w;
        cin >> n >> m >> w;
        wij[n][m] = w;
        wij[m][n] = w;
    }

    greedy();

    for (int i = 1; i <= N; i++)
    {
        cout << (result[i] == 1 ? "A" : "B")
             << " ";
    }
    cout << endl;

    PRINT(A);
    PRINT(B);

    cout << calcE() << endl;
    return 0;
}