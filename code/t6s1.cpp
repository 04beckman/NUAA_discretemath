// 最邻近法
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> g; // 采用邻接矩阵存储图
vector<int> ans;       // 存储该算法下最优答案路径

int bestx = INT_MAX;
int N;
void TSP(int x)
{
    vector<int> flag(N, 0);
    vector<int> temp;
    temp.push_back(x);
    int sum = 0;
    int u, v, min;
    u = x; // u是当前城市的位置 ，现在是设置的x城市
    flag[u] = 1;
    for (int i = 0; i < N - 1; i++) // 走N步回到起点
    {
        min = INT_MAX;
        for (int j = 0; j < N; j++) // 比较当前城市距离其他每个城市的距离
        {
            if (flag[j] != 1 && g[u][j] < min && g[u][j] != 0) // flag查看城市是否已经走过，利用min依次比较
            {
                min = g[u][j];
                v = j;
            }
        }
        sum += min;
        flag[v] = 1;
        temp.push_back(v);
        u = v;
    }
    sum += g[v][x];
    temp.push_back(x);
    if (sum < bestx)
    {
        bestx = sum;
        ans = temp;
    }
}
int main(void)
{
    cout << "输入城市个数:" << endl;
    cin >> N;
    g = vector<vector<int>>(N, vector<int>(N));
    cout << "输入城市之间的距离(0表示城市间不通):" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> g[i][j];
    for (int i = 0; i < N; ++i)
        TSP(i);
    cout << "最小费用为" << bestx << endl;
    char k = 'a';
    for (int i = 0; i < ans.size() - 1; ++i)
        cout << char(k + ans[i]) << "->";
    cout << char(k + ans[0]);
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