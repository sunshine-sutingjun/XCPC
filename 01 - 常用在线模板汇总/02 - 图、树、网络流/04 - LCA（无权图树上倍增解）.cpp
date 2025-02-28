struct Tree
{
    int n;
    vector<vector<int>> adj;       // adjacency list
    vector<vector<int>> ancestors; // ancestors at different levels
    vector<int> lg;                // precomputed log values
    vector<int> depth;             // u depths
    Tree(int n) : n(n)
    {
        adj.resize(n + 1);
        ancestors.resize(n + 1, vector<int>(30));
        lg.resize(n + 1);
        depth.resize(n + 1);
        for (int i = 1; i <= n; i++)
        { // 预处理 log
            lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
        }
    }
    void add(int u, int v)
    { // 建立双向边
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void buildAncestors(int u, int parent)
    {
        ancestors[u][0] = parent; // 储存 x 的父节点
        depth[u] = depth[parent] + 1;
        for (int i = 1; i <= lg[depth[u]]; i++)
        {
            ancestors[u][i] = ancestors[ancestors[u][i - 1]][i - 1];
        }
        for (auto v : adj[u])
        {
            if (v == parent)
                continue;
            buildAncestor(v, u);
        }
    }
    int findLCA(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);
        while (depth[u] > depth[v])
        {
            u = ancestors[u][lg[depth[u] - depth[v]] - 1];
        }
        if (u == v)
            return u;
        for (int level = lg[depth[u]] - 1; level >= 0; level--)
        {
            if (ancestors[u][level] == ancestors[v][level])
                continue;
            u = ancestors[u][level];
            v = ancestors[v][level];
        }
        return ancestors[u][0];
    }
    int getDistance(int u, int v)
    { // 倍增查询两点间距离
        return depth[u] + depth[v] - 2 * depth[findLCA(u, v)];
    }
    void initialize(int root = 1)
    { // 在此初始化
        buildAncestor(root, 0);
    }
};