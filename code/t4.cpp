#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;
unordered_map<int, vector<int>> g;
vector<bool> vis(100, false);
void dfs(int i)
{
    if (vis[i])
        return;
    vis[i] = true;
    printf("%d ", i);
    for (auto &x : g[i])
        dfs(x);
}
int main(void)
{
    cout << "输入边数 顶点数" << endl;
    int n, m, cnt = 0;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        cout << "输入边的两端 例如:1 2" << endl;
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for (int i = 1; i <= m; ++i)
    {
        if (!vis[i])
        {
            dfs(i);
            cnt++;
            cout << endl;
        }
    }
    cout << "连通分支数为:" << cnt << endl;
    system("pause");
    return 0;
}
/*
9 9
1 4
1 5
1 2
2 3
3 4
4 5
6 7
7 9
7 8
*/