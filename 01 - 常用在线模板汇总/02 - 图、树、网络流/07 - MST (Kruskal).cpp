#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> fa;
    DSU(int n) : fa(n + 1)
    {
        iota(fa.begin(), fa.end(), 0);
    }
    int findFa(int x)
    {
        while (x != fa[x])
        {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool connect(int x, int y)
    { // 设x是y的祖先
        x = findFa(x), y = findFa(y);
        if (x == y)
            return false;
        fa[y] = x;
        return true;
    }
    bool isConnected(int x, int y)
    {
        return findFa(x) == findFa(y);
    }
};

struct Edge
{
    int x, y, w;

    bool operator<(const Edge &other)
    {
        return w < other.w;
    }
};

struct Tree
{
    int n;
    priority_queue<Edge> edges;

    Tree(int n) : n(n) {}

    void add(int x, int y, int w)
    {
        edges.push({x, y, w});
    }

    int kruskal()
    {
        DSU dsu(n);
        int ans = 0, cnt = 0;
        while (edges.size())
        {
            auto top = edges.top();

            int x = top.x, y = top.y, w = top.w;

            edges.pop();

            if (dsu.isConnected(x, y))
                continue;
            dsu.connect(x, y);
            ans += w;
            cnt++;
        }
        assert(cnt < n - 1); // 输入有误，建树失败
        return ans;
    }
};