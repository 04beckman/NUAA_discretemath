// 全排列暴力法
#include <iostream>
#include <vector>
using namespace std;

vector<int> ans;     // 最优路线
vector<int> x;       // 城市编号数组,初值赋为0
vector<int> path;    // 路线,初值赋为0
int bestw = INT_MAX; // 最优的费用

void Tsp(vector<vector<int>> &g, int n, int s)
{
    if (s == n)
    {
        int w = 0;
        for (int i = 0; i < n; i++)
        {
            path[i] = x[i];
            if (i < n - 1)
                w += g[x[i]][x[i + 1]];
            else
                w += g[x[i]][x[0]]; // 回到起点的费用
        }
        if (bestw > w)
        {
            ans = path;
            bestw = w;
        }
    }
    else
    {
        for (int i = s; i < n; i++)
        {
            // dfs模板
            int t = x[i];
            x[i] = x[s];
            x[s] = t;
            Tsp(g, n, s + 1);
            t = x[i];
            x[i] = x[s];
            x[s] = t;
        }
    }
}
int main(void)
{
    cout << "请输入城市的个数: " << endl;
    int n; // 城市个数
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    x = vector<int>(n);
    path = vector<int>(n);
    for (int i = 0; i < n; i++)
        x[i] = i;
    cout << "输入城市之间的距离(0表示城市间不通):" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];
    Tsp(g, n, 0);
    cout << "最小费用为：" << bestw << endl
         << "路线为：" << endl;
    for (int i = 0; i < n; ++i)
        cout << ans[i] + 1 << "->";
    cout << ans[0] + 1;
    system("pause");
    return 0;
}

// G1
/*
5
0 5 12 5 5
5 0 9 7 8
12 9 0 9 16
5 7 9 0 8
5 8 16 8 0
*/

// G2:K4
/*
4
0 10 8 5
10 0 8 11
8 8 0 8
5 11 8 0
*/