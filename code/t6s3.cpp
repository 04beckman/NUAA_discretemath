#include <iostream>
#include <vector>
#include <algorithm>
#define MAXNUM 1e6
using namespace std;
int n;                 // 图顶点数
vector<vector<int>> G; // 图的邻接矩阵
vector<vector<int>> D; // 表示顶点到s顶点集合的距离
vector<vector<int>> R; // 表示i到集合s路径的第一个顶点是R[i][s]
unsigned int s;        // 用于表示顶点集合，第i位为1，表示第(i+1)个顶点在集合s中(i>0)

int Exp(int k) // 计算2的k次方:二进制数左移一位实现*2
{
    k = 1 << k;
    return k;
}

void solve() // 采用自底向上填表
{
    int i, k;
    unsigned int max, s2;
    max = Exp(n - 1) - 1;
    for (s = 1; s <= max; s++)
    {
        for (i = 1; i <= n; i++)
            if ((s & 1 << (i - 2)) == 0) // 如果第i个顶点不属于集合s
            {
                D[i][s] = MAXNUM;
                for (k = 2; k <= n; k++)
                {
                    if ((s & 1 << (k - 2)) != 0)
                    {
                        s2 = s & ~(1 << (k - 2));
                        if (G[i][k] + D[k][s2] < D[i][s])
                        {
                            D[i][s] = G[i][k] + D[k][s2];
                            R[i][s] = k;
                        }
                    }
                }
            }
    }
}

void Tsp() // 动态规划求解
{
    int i;
    s = s & 0;
    for (i = 2; i <= n; i++)
    {
        D[i][s] = G[i][1];
        R[i][s] = 1;
    }
    solve();
}

unsigned int Deletes(int k) // 从s中将第k个顶点删除
{
    unsigned int ts;
    ts = 1;
    ts = ts << (k - 2);
    ts = ~ts;
    return s & ts;
}

void construct() // 构造最优解，输出最短路程和最短路径
{
    int i, k;
    s = Exp(n - 1) - 1;
    printf("最短路程是:%d\n", D[1][s]);
    printf("最短路径为:\n");
    printf("a->");
    for (i = 1, k = R[1][s]; i <= n; i++, k = R[k][s])
    {
        if (i < n)
            printf("%c->", 'a' + k - 1);
        else
            cout << char('a' + k - 1);
        s = Deletes(k);
    }
    cout << endl;
}
int main(void)
{
    int space;
    cout << "输入城市的个数" << endl;
    cin >> n;
    space = Exp(n - 1);
    G = vector<vector<int>>(n + 1, vector<int>(n + 1));
    D = vector<vector<int>>(n + 1, vector<int>(space + 1));
    R = vector<vector<int>>(n + 1, vector<int>(space + 1));
    cout << "输入城市之间的距离(0表示城市间不通):" << endl;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> G[i][j];
    Tsp();       // 调用Tsp()动态规划求最优解
    construct(); // 调用Reconstruct()构造最优解,并输出最短路程和最短路径
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