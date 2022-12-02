#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
int n, a[17][7];
vector <int> ans[5005];

bool check(int u, int v, int len, int pre, int under)
{
    if (len + 16 - u > 25) return 0;
    if (u == 16) return (len >= 23 && len <= 25);
    int k;
    if (pre == 0 && under == 0) k = max(6 - v, v - 1);
    if (pre == 1 || under == 1) k = v - 1;
    if (pre == 2 || under == 2) k = 6 - v;
    int p = (u & 1) ? 15 : 14;
    k += ((p - u) * 7 / 2 + ((u & 1) ^ 1) + 1);
    return (k + len >= 23);
}

void backtrack(int u, int v, int len, int pre, int under)
{
    if (n >= 5000) return;
    if (u == 16) {
        n++;
        for (int i = 1; i < 17; i++) for (int j = 1; j < 7; j++) ans[n].pb(a[i][j]);
        return;
    }
    if ((pre == 1 || under == 1 || (pre == 0 && under == 0)) && v - 1 > 0 && check(u, v - 1, len + 1, pre, under)) {
        a[u][v - 1] = 1;
        backtrack(u, v - 1, len + 1, 1, 1);
        a[u][v - 1] = 0;
    }
    if ((pre == 2 || under == 2 || (pre == 0 && under == 0)) && 6 - v > 0 && check(u, v + 1, len + 1, pre, under)) {
        a[u][v + 1] = 1;
        backtrack(u, v + 1, len + 1, 2, 2);
        a[u][v + 1] = 0;
    }
    if (check(u + 1, v, len + 1, 0, pre)) {
        a[u + 1][v] = 1;
        backtrack(u + 1, v, len + 1, 0, pre);
        a[u + 1][v] = 0;
    }
}

int main()
{
    for (int i = 1; i < 7; i++) {
        a[1][i] = a[2][i] = 1;
        backtrack(2, i, 2, 0, 0);
        a[1][i] = a[2][i] = 0;
    }

    cout << n << '\n';
    for (int i = 1; i <= n; i++) for (int j = 0; j < 96; j++) cout << ans[i][j] << " \n"[j == 95];

    return 0;
}
