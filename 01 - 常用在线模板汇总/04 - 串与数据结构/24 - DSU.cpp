struct DSU
{
    vector<int> fa, connectedSize;

    DSU(int n)
    {
        fa.resize(n + 1);
        iota(fa.begin(), fa.end(), 0);
        connectedSize.resize(n + 1, 1);
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
    {
        x = findFa(x), y = findFa(y);
        if (x == y)
            return false;
        if (x < y)
            swap(x, y);
        fa[y] = x;
        connectedSize[x] += connectedSize[y];
        return true;
    }
    bool isConnected(int x, int y)
    {
        return findFa(x) == findFa(y);
    }
    int getSize(int x)
    {
        return connectedSize[findFa(x)];
    }
};