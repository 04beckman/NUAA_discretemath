#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXCOST 0x7fffffff
#define MAXSIZE 21
vector<int> minstdu(MAXSIZE);                                // 最小生成树每个顶点的度 ，minstdu[1]=1表示顶点1的度为1
int mstcostnum;                                              // 最小生成树中边的条数
vector<vector<int>> minst(MAXSIZE, vector<int>(MAXSIZE));    // 最小生成树
vector<int> Connected(MAXSIZE);                              // 标记连通分量，Connected[1]=1表示顶点1处在连通分量1中
vector<vector<int>> graph(MAXSIZE, vector<int>(MAXSIZE, 0)); // 保存输入的带权无向图
vector<int> sum(MAXSIZE);                                    // 保存各回路的距离值，例如sum[1]=10表示顶点1的最小生成树生成的回路距离值为10.

void prim(int n) // prim算法求最小生成树
{
    vector<int> lowcost(n + 1);
    // lowcost存放顶点1可达点的路径长度
    vector<int> mst(n + 1);
    int a, min, minid;
    for (int i = 2; i <= n; i++)
    {
        lowcost[i] = graph[1][i];
        mst[i] = 1; // 初始化以1为起始点
    }
    mst[1] = 0;

    for (int i = 2; i <= n; i++)
    {
        min = MAXCOST;
        minid = 0;
        for (int j = 2; j <= n; j++)
        {
            if (lowcost[j] < min && lowcost[j] != 0)
            {
                min = lowcost[j]; // 找出权值最短的路径长度
                minid = j;        // 找出最小的ID
            }
        }
        printf("V%c-V%c=%d\n", 'a' + mst[minid] - 1, 'a' + minid - 1, min);
        a = mst[minid];
        minst[a][minid] = min;
        minst[minid][a] = min;
        minstdu[a]++;
        minstdu[minid]++;
        mstcostnum++;
        lowcost[minid] = 0; // 该处最短路径置为0
        for (int j = 2; j <= n; j++)
        {
            if (graph[minid][j] < lowcost[j]) // 对这一点直达的顶点进行路径更新
            {
                lowcost[j] = graph[minid][j];
                mst[j] = minid;
            }
        }
    }
}

int mstMAXdu(int v, int n) // 求最小生成树中除了点v的点的最大的度
{
    int mstmaxdu = 0;
    for (int i = 1; i <= n; i++)
        if (v != i && minstdu[i] > mstmaxdu)
            mstmaxdu = minstdu[i];
    return mstmaxdu;
}

int mstMAXdupt(int v, int u, int n) // 求最小生成树中除了点v的点的度为u的点
{
    int pt = 0;
    for (int i = 1; i <= n; i++)
        if (v != i && minstdu[i] == u)
            pt = i;
    return pt;
}

int mstMAXcost(int v, int n) // 求最小生成树中与点v相连的最大的边
{
    int maxcost = 0;
    for (int i = 1; i <= n; i++)
        if (v != i && minst[v][i] > maxcost)
            maxcost = minst[v][i];
    return maxcost;
}

int mstMAXcostpt(int v, int u, int n) // 求最小生成树中与点v相连的边为u的点
{
    int pt = 0;
    for (int i = 1; i <= n; i++)
        if (v != i && minst[v][i] == u)
            pt = i;
    return pt;
}

int main(void)
{
    int m, n;
    int x, y, cost, v;
    int maxdu, maxp, maxmc, maxmstcostpoint;
    cout << "请输入城市的个数: " << endl;
    cin >> m;
    cout << "输入城市之间的距离(0表示城市间不通):" << endl;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
        {
            int a;
            cin >> a;
            if (a != 0)
                graph[i][j] = a;
            else
                graph[i][j] = MAXCOST;
        }
    cout << endl;
    mstcostnum = 0;
    for (v = 1; v <= m;)
    {
        printf("以顶点%c构造最小生成树\n", v + 'a' - 1);
        prim(m);                     // 用prim算法从顶点1生成最小生成树
        for (int k = 1; k <= m; k++) // 第一步,降低最小生成树中度大于2的节点的度 ,保证每个节点的度都不大2。
        {
            if (minstdu[k] > 2)
            {
                maxdu = mstMAXdu(k, m);
                maxp = mstMAXdupt(k, maxdu, m);
                if (maxdu > 2)
                {
                    minst[k][maxp] = 0;
                    minst[maxp][k] = 0;
                    minstdu[k]--;
                    minstdu[maxp]--;
                    mstcostnum--;
                }
                else
                {
                    maxmc = mstMAXcost(k, m);
                    maxmstcostpoint = mstMAXcostpt(k, maxmc, m);
                    minst[k][maxmstcostpoint] = 0;
                    minst[maxmstcostpoint][k] = 0;
                    minstdu[k]--;
                    minstdu[maxmstcostpoint]--;
                    mstcostnum--;
                }
            }
        }
        for (; mstcostnum < m;) // 第二步是通过连接的方法 , 连接最小生成树中度小于2 的节点
        {
            for (int i = 1; i <= m; i++) // 标记连通分量
            {
                if (minstdu[i] == 0)
                {
                    Connected[i] = i;
                }
                else
                {
                    for (int j = 1; j <= m; j++)
                    {
                        if (i != j && minst[i][j] != 0)
                        {
                            if (Connected[i] == 0)
                            {
                                Connected[i] = i;
                            }
                            Connected[j] = Connected[i];
                        }
                    }
                }
            }
            for (int i = 1; i <= m; i++) // 连接最小生成树中度小于2 的节点
            {
                if (minstdu[i] < 2)
                {
                    for (int j = 1; j <= m; j++)
                    {
                        if (i != j && Connected[j] != Connected[i] && minstdu[j] < 2)
                        {
                            minst[i][j] = graph[i][j];
                            minst[j][i] = graph[i][j];
                            minstdu[i]++;
                            minstdu[j]++;
                            mstcostnum++;
                            x = Connected[i];
                            y = Connected[j];
                            for (int k = 1; k <= m; k++)
                            {
                                if (Connected[k] == y)
                                {
                                    Connected[k] = x;
                                }
                            }
                        }
                    }
                    if (minstdu[i] < 2)
                    {
                        for (int j = 1; j <= m; j++)
                        {
                            if (i != j && Connected[j] == Connected[i] && minstdu[j] < 2)
                            {
                                minst[i][j] = graph[i][j];
                                minst[j][i] = graph[i][j];
                                minstdu[i]++;
                                minstdu[j]++;
                                mstcostnum++;
                            }
                        }
                    }
                }
            }
        }
        printf("输出此路径及其距离为：\n");
        for (int i = 1, j = 1, x = 0; i <= m; i++) // 输出路径
        {
            for (int k = 1; k <= m; k++)
            {
                if (j != k && k != x && minst[j][k] != 0)
                {
                    printf("%c -> %c : %d\n", 'a' + j - 1, 'a' + k - 1, minst[j][k]);
                    sum[v] = sum[v] + minst[j][k];
                    x = j;
                    j = k;
                    break;
                }
            }
        }
        printf("此路径距离值为：%d\n\n", sum[v]);

        if (v > 1) // 若已经替换过初始点，则恢复成原图
        {
            for (int i = 2; i <= m; i++)
            {
                if (i != v)
                {
                    cost = graph[1][i];
                    graph[1][i] = graph[v][i];
                    graph[i][1] = graph[v][i];
                    graph[v][i] = cost;
                    graph[i][v] = cost;
                }
            }
        }
        // 重设顶点
        v++;
        for (int i = 2; i <= m; i++)
        {
            if (i != v)
            {
                cost = graph[1][i];
                graph[1][i] = graph[v][i];
                graph[i][1] = graph[v][i];
                graph[v][i] = cost;
                graph[i][v] = cost;
            }
        }
        // 重设顶点后需要初始化
        for (int i = 0; i <= m; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                minst[i][j] = 0;
                minst[j][i] = 0;
                minstdu[i] = 0;
                minstdu[j] = 0;
                Connected[i] = 0;
                Connected[j] = 0;
            }
        }
        mstcostnum = 0;
    }

    int minnum = sum[1];
    for (int i = 2; i <= m; i++)
        if (minnum > sum[i])
            minnum = sum[i];

    for (int i = 1; i <= m; i++)
    {
        if (minnum == sum[i])
        {
            cout << "\n由上述可得" << endl;
            printf("由顶点%c生成的最小生成树求得的路径距离值最小，为%d\n", 'a' + i - 1, sum[i]);
        }
    }
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