#include <iostream>
using namespace std;

#define MAX_V 20
#define OK 1
#define ERROR 0
typedef int ElemType, Status;
typedef int GraphKind; // 定义图的类型，无向图0， 有向图1，无向网2，有向网3
// 定义边的结点结构类型
struct ArcNode
{
    int adjvex; // 该边的终边编号
    int weight; // 该边的权值
    struct ArcNode *nextarc;
};
// 定义顶点的结构类型
struct VexNode
{
    ElemType data;     // 顶点的值
    ArcNode *firstarc; // 指向第一条与该顶点有关的指针
};

// 定义邻接表表示的图
class ALGraph
{
private:
    VexNode vexnode[MAX_V]; // 定义邻接表
    int vexnum, arcnum;
    GraphKind type; // 定义图的类型，无向图0， 有向图1，无向网2，有向网3

public:
    Status CreateGraph();           // 图的创建
    Status InsertVex();             // 插入顶点
    Status InsertArc(int v, int w); // 插入边
    Status DeleteVex(int v);        // 删除顶点
    Status DeleteArc(int v, int w); // 删除边
    Status Print();                 // 打印邻接表
};

// 基于邻接表的无向图创建
Status ALGraph::CreateGraph()
{
    printf("输入图的顶点数 边数\n");
    cin >> vexnum >> arcnum; // 输入图的顶点数和边数
    int i, v, w;
    for (i = 1; i <= vexnum; i++)
    { // 输入各顶点的信息
        vexnode[i].data = i;
        vexnode[i].firstarc = NULL;
    }
    ArcNode *p;
    for (i = 0; i < arcnum; i++)
    {
        cout << "输入边 例如1 2" << endl;
        // 创建各边
        cin >> v >> w;   // 输入一条边的两个顶点
        p = new ArcNode; // 创建一个用于存放当前边的顶点
        if (p == NULL)
            exit(0);
        p->adjvex = w;                    // 该边的起点是v终点是w
        p->nextarc = vexnode[v].firstarc; // 将该边结点链接到v号顶点
        vexnode[v].firstarc = p;

        p = new ArcNode; // 由于是无向图还要创建一条对称的边，起点w终点v
        if (p == NULL)
            exit(0);
        p->adjvex = v;
        p->nextarc = vexnode[w].firstarc; // 将该边链接到w号顶点
        vexnode[w].firstarc = p;
    }
    return OK;
}
// 打印邻接表
Status ALGraph::Print()
{
    cout << "邻接表如下" << endl;
    int i;
    ArcNode *p;
    for (i = 1; i <= vexnum; i++)
    {
        p = vexnode[i].firstarc;
        cout << vexnode[i].data << "-->";
        while (p)
        {
            cout << p->adjvex << " ";
            p = p->nextarc;
        }
        cout << endl;
    }
    return OK;
}
// 删除顶点
Status ALGraph::DeleteVex(int v)
{
    ArcNode *p, *q;
    int i;
    p = q = vexnode[v].firstarc;
    while (p)
    {
        i = p->adjvex;
        ArcNode *p1, *q1;
        p1 = q1 = vexnode[i].firstarc;
        if (p1->adjvex == v)
        {
            vexnode[i].firstarc = p1->nextarc;
            delete p1;
            p1 = q1 = NULL;
        }
        else
        {
            while (true)
            {
                p1 = p1->nextarc;
                if (p1->adjvex == v)
                {
                    q1->nextarc = p1->nextarc;
                    delete p1;
                    p1 = NULL;
                    break;
                }
                q1 = p1;
            }
        }
        p = p->nextarc;
        delete q;
        q = p;
        arcnum--;
    }
    vexnode[v].firstarc = NULL;
    for (i = v; i <= vexnum - 1; i++)
        vexnode[i] = vexnode[i + 1];
    vexnum--;
    return OK;
}

// 删除边
Status ALGraph::DeleteArc(int v, int w)
{
    ArcNode *p, *q;
    p = q = vexnode[v].firstarc;
    if (p->adjvex == w)
    {
        vexnode[v].firstarc = p->nextarc;
        delete p;
        p = q = NULL;
    }
    else
    {
        while (true)
        {
            if (!p)
                break;
            p = p->nextarc;
            if (p && p->adjvex == w)
            {
                q->nextarc = p->nextarc;
                delete p;
                p = q = NULL;
                break;
            }
        }
    }

    p = q = vexnode[w].firstarc;
    if (p->adjvex == v)
    {
        vexnode[w].firstarc = p->nextarc;
        delete p;
        p = q = NULL;
    }
    else
    {
        while (true)
        {
            if (!p)
                break;
            p = p->nextarc;
            if (p && p->adjvex == v)
            {
                q->nextarc = p->nextarc;
                delete p;
                p = q = NULL;
                break;
            }
        }
    }
    arcnum--;
    return OK;
}
// 插入顶点
Status ALGraph::InsertVex()
{
    int v, w;
    ArcNode *p;
    vexnum++;
    vexnode[vexnum].data = vexnum;
    vexnode[vexnum].firstarc = NULL;
    while (true)
    {
        cout << "输入新增加的顶点与其相连的顶点 -1则退出" << endl;
        cin >> v;
        if (v == -1)
            break;
        p = new ArcNode;
        if (p == NULL)
            exit(0);
        p->adjvex = vexnum;               // 该边的起点是v终点是w
        p->nextarc = vexnode[v].firstarc; // 将该边结点链接到v号顶点
        vexnode[v].firstarc = p;

        p = new ArcNode; // 由于是无向图还要创建一条对称的边，起点w终点v
        if (p == NULL)
            exit(0);
        p->adjvex = v;
        p->nextarc = vexnode[vexnum].firstarc; // 将该边链接到w号顶点
        vexnode[vexnum].firstarc = p;
        arcnum++;
    }
    return OK;
}

// 插入边
Status ALGraph::InsertArc(int v, int w)
{
    ArcNode *p;
    p = new ArcNode;
    if (p == NULL)
        exit(0);
    p->adjvex = w;                    // 该边的起点是v终点是w
    p->nextarc = vexnode[v].firstarc; // 将该边结点链接到v号顶点
    vexnode[v].firstarc = p;

    p = new ArcNode; // 由于是无向图还要创建一条对称的边，起点w终点v
    if (p == NULL)
        exit(0);
    p->adjvex = v;
    p->nextarc = vexnode[w].firstarc; // 将该边链接到w号顶点
    vexnode[w].firstarc = p;

    arcnum++;
    return OK;
}
int main(void)
{
    ALGraph graph;
    graph.CreateGraph();
    graph.Print();
    cout << endl;
    graph.InsertVex();
    cout << "加入新顶点v6之后";
    graph.Print();
    cout << endl;
    graph.InsertArc(2, 5);
    cout << "加入新边v2->v5";
    graph.Print();
    cout << endl;
    graph.DeleteVex(2);
    cout << "删除顶点2之后";
    graph.Print();
    cout << endl;
    graph.DeleteArc(2, 3);
    cout << "删除边v2->v3之后";
    graph.Print();
    cout << endl;
    system("pause");
    return 0;
}
/*
5 6
1 4
1 5
1 2
5 4
4 3
2 3
3
-1

*/
/*
T2.
邻接矩阵浪费空间——存稀疏图（点很多而边很少）有大量无效元素，因此邻接表更高效
对稠密图（特别是完全图）还是合算的。
T3.
邻接矩阵的优点：
（1）可以通过M[u][v]直接引用边(u, v)， 因此只需常数时间(O(1))即可确定顶点u 和顶点v 的关系
（2）只要更改M[u][v] 就能完成边的添加和删除， 简单且高效O(1)
缺点：
（1）消耗的内存空间等于顶点的平方数。如果图的边数较少（稀疏图），则会浪费大量的内存空间
（2）一个邻接矩阵中，只能记录顶点u 到顶点v 的一个关系（一个基本型的二维数组中，无法在同一对顶点之间画出俩条边）
 (3)邻接矩阵不便于增加和删除顶点（增加一个顶点需要增加一行一列，删除一个顶点需要删除一行一列）
邻接表的优点是
(1)节省空间，只存储实际存在的边。
(2)增加顶点方便。
缺点：
（1）缺点是关注顶点的度时，就可能需要遍历一个链表。
（2）对于无向图，如果需要删除一条边，就需要在两个链表上查找并删除。

*/