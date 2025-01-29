#include <iostream>
#include <algorithm>
#define maxn 101
using namespace std;

int n, m, g;            // n为点数，m为边数，g为图的类型（1.无向图 2.有向图）
int Matrix[maxn][maxn]; // 图的邻接矩阵(初始化为0)(从1开始)
int Path[maxn] = {0};   // 欧拉回路
int total = 0;          // 加入欧拉回路的点
void Get();             // 输入图的邻接矩阵
void Print();           // 打印图的邻接矩阵
bool Judge_Connect();   // 判断图是否连通
bool Judge_Path();      // 判断图是否有欧拉回路
void Find_Path();       // 从图中任找一条欧拉回路

void Get() // 求图的邻接矩阵
{
    if (g == 1)
    {
        cout << "请输入无向图中各点所连接的点的编号：（有重边、自环则多次输入，输入0代表结束）" << endl;
    }
    else
    {
        cout << "请输入有向图中各点所指向的点的编号：（有重边则多次输入，输入0代表结束）" << endl;
    }
    for (int i = 1; i <= n; i++)
    {
        int j;
        cout << "v" << i << ":";
        cin >> j;
        while (j != 0)
        {
            Matrix[i][j]++;
            if (i == j && g == 1)
                Matrix[i][j]++;
            cin >> j;
        }
    }
}

void Print() // 打印图的邻接矩阵
{
    cout << "\n该图的邻接矩阵为：" << endl;
    cout << "  ";
    for (int i = 1; i <= n; i++)
    {
        cout << " v" << i;
    }
    cout << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << " v" << i << " ";
        for (int j = 1; j <= n; j++)
        {
            cout << Matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

void DFS1(int x, int *p) // 用递归搜寻各点，检验是否连通
{
    p[x] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (p[i] == 1)
        { // 点已被记录过，跳过
            continue;
        }
        if (Matrix[x][i] > 0)
        {
            DFS1(i, p); // 进入与该点连通的未记录的下一个点
        }
    }
}

bool Judge_Connect() // 判断图是否连通
{
    int t = 1;
    int Point[maxn] = {0}; // 判断点是否连通
    DFS1(1, Point);        // 连通，则所有的点均会被置为1
    for (int i = 1; i <= n; i++)
    { // 检查各点是否均被记录
        if (!Point[i])
        { // 存在未记录的点，说明不连通
            t = 0;
            break;
        }
    }
    if (t)
    {
        cout << "\n连通性：该图连通" << endl;
        return true;
    }
    else
    {
        if (g == 1)
        {
            cout << "\n连通性：该无向图不连通" << endl;
        }
        else
        {
            cout << "\n连通性：该有向图不强连通" << endl;
        }
        return false;
    }
}

bool Judge_Path() // 判断图是否有欧拉回路
{
    int t = 1, sum = 0;
    if (g == 1)
    { // 无向图
        int d;
        for (int i = 1; i <= n; i++)
        {
            d = 0;
            for (int j = 1; j <= n; j++)
            {
                d += Matrix[i][j]; // 求度数
            }
            if (d % 2 != 0)
            { // 检验度数是否为偶数
                t = 0;
                break;
            }
            sum += d;
        }
        m = sum / 2; // 无向图的边数
    }
    else
    { // 有向图
        int d1, d2;
        for (int i = 1; i <= n; i++)
        {
            d1 = 0;
            d2 = 0;
            for (int j = 1; j <= n; j++)
            {
                d1 += Matrix[i][j]; // 求出度
            }
            for (int j = 1; j <= n; j++)
            {
                d2 += Matrix[j][i]; // 求入读
            }
            if (d1 != d2)
            { // 检验出度和入读是否相等
                t = 0;
                break;
            }
            sum += d1;
        }
        m = sum; // 有向图的边数
    }
    if (t)
    {
        cout << "\n该图存在欧拉回路" << endl;
        return true;
    }
    else
    {
        cout << "\n该图不存在欧拉回路" << endl;
        return false;
    }
}

void DFS2(int x) // 用递归通过各边(插入回路法)
{
    for (int i = 1; i <= n; i++)
    {
        if (Matrix[x][i] > 0)
        {                   // 点x存在到点i的通路
            Matrix[x][i]--; // 消去走过的路
            if (g == 1)
            {
                Matrix[i][x]--;
            }
            DFS2(i); // 继续向下遍历
        }
    }
    total++;
    Path[total] = x; // 回溯到无法继续走的点，则加入回路
}

void Find_Path() // 从图中任找一条欧拉回路
{
    DFS2(1);
    cout << "其中一条欧拉回路为：";
    int i;
    for (i = m + 1; i > 1; i--)
    { // 倒序输出
        cout << "v" << Path[i] << "->";
    }
    cout << "v" << Path[1];
    cout << endl;
}

int main(void)
{
    bool temp;
    cout << "图的类型：1.无向图 2.有向图" << endl;
    cout << "请输入:";
    cin >> g;
    cout << "请输入结点的数目：";
    cin >> n;
    Get();                  // 求图的邻接矩阵
    Print();                // 打印图的邻接矩阵
    temp = Judge_Connect(); // 判断图是否连通
    if (temp)
    {
        temp = Judge_Path(); // 判断图是否有欧拉回路
        if (temp)
        {
            cout << "\n该图中共有" << m << "条边" << endl;
            Find_Path(); // 从图中任找一条欧拉回路
        }
    }
    system("pause");
    return 0;
}
// G1如下
/*
1
16
16 2 0
3 1 6 5 0
2 7 0
7 16 0
2 9 0
2 7 0
3 6 4 8 0
7 11 0
10 5 12 13 0
9 11 0
10 12 8 15 0
9 11 0
9 14 0
13 15 0
11 14 0
1 4 0
*/

// G2如下
/*
2
4
4 0
1 4 0
2 0
2 3 4 0
*/