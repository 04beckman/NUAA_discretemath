#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <stack>
using namespace std;
int n, m;
// g建图 这样方便dfs 不这样搞就换一下矩阵遍历
unordered_map<int, vector<int>> g;
// 矩阵相乘
vector<vector<int>> x(vector<vector<int>> &A, vector<vector<int>> &B)
{
    vector<vector<int>> res(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int ans = 0;
            for (int k = 1; k <= n; ++k)
            {
                ans += A[i][k] * B[k][j];
            }
            res[i][j] = ans;
        }
    }
    return res;
}
// 矩阵相加
void sum(vector<vector<int>> &A, vector<vector<int>> &B)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            A[i][j] += B[i][j];
        }
    }
}
// postion指当前位置 cnt指已经走的步长 end指目标位置
void dfs(int position, stack<int> s, int cnt, int end)
{
    if (cnt >= 5)
        return;
    if (position == end)
    {
        vector<int> ans;
        // 这里就是把答案打印出来 用不用栈其实都无所谓
        while (!s.empty())
        {
            ans.push_back(s.top());
            s.pop();
        }
        for (int i = 0; i < ans.size(); ++i)
        {
            cout << ans[ans.size() - 1 - i] << " ";
            s.push(ans[ans.size() - 1 - i]);
        }
        cout << endl;
    }
    for (auto &x : g[position])
    {
        s.push(x);
        dfs(x, s, cnt + 1, end);
        s.pop();
    }
}
int main(void)
{
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector<int>(n + 1, 0));
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        grid[x][y] = 1;
        grid[y][x] = 1;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<vector<int>> result = grid;
    vector<vector<int>> temp = grid;
    cout << "图的邻接矩阵如下" << endl;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            cout << grid[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    // result是最终A1+A2+A3+A4
    // temp是A2 A3 A4
    for (int i = 2; i < n; ++i)
    {
        temp = x(temp, grid);
        sum(result, temp);
    }
    for (int i = 1; i <= 5; ++i)
    {
        for (int j = i; j <= 5; ++j)
        {
            cout << "v" << i << "->v" << j << "总共的路线有" << result[i][j] << "条路线" << endl;
            cout << "分别是以下路线:" << endl;
            stack<int> s;
            s.push(i);
            dfs(i, s, 0, j);
        }
    }
    system("pause");
    return 0;
}

/*
5 6
1 4
1 5
1 2
4 5
4 3
2 3

*/