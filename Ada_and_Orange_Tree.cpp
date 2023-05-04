#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int MAX = 450025;
const int LOGMAX = 20;

int st[MAX][LOGMAX + 1];
vector<int> gr[MAX];
bool shade[MAX][251];
int level[MAX];
int nodeval[MAX];
int n, q, root;

void dfs(int node, int par)
{
    shade[node][nodeval[node]] = 1;
    st[node][0] = par;
    level[node] = level[par] + 1;
    for (int k = 1; k <= LOGMAX; ++k)
    {
        if (st[node][k - 1] != -1)
        {
            st[node][k] = st[st[node][k - 1]][k - 1];
        }
    }
    for (auto child : gr[node])
    {
        if (child != par)
        {
            dfs(child, node);
            shade[node][nodeval[child]] = 1;
            for (int i = 0; i < 251; ++i)
            {
                if (shade[child][i] == 1)
                {
                    shade[node][i] = 1;
                }
            }
        }
    }
}
int lca(int u, int v)
{
    if (level[v] > level[u])
    {
        swap(u, v);
    }

    for (int k = LOGMAX - 1; k >= 0; --k)
    {
        if (level[st[u][k]] >= level[v] && st[u][k] != -1)
        {
            u = st[u][k];
        }
    }
    if (u == v)
    {
        return u;
    }
    for (int k = LOGMAX - 1; k >= 0; --k)
    {
        if (st[u][k] != st[v][k])
        {
            u = st[u][k];
            v = st[v][k];
        }
    }
    return st[u][0];
}

void reset()
{
    //  memset(nodeval, 0, sizeof nodeval);
    memset(level, 0, sizeof level);
    memset(st, -1, sizeof st);
    for (int i = 0; i <= n; ++i)
    {
        gr[i].clear();
    }
    memset(shade, 0, sizeof shade);
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cin.tie(0);

    int t;
    scanf("%d", &t);
    // cin >> t;
    while (t--)
    {
        // cin >> n >> q >> root;
        scanf("%d %d %d", &n, &q, &root);
        ++root;
        for (int i = 1; i <= n; ++i)
        {
            //  cin >> nodeval[i];
            scanf("%d", &nodeval[i]);
        }
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            // cin >> u >> v;
            u++, v++;
            gr[u].push_back(v);
            gr[v].push_back(u);
        }
        dfs(root, -1);
        while (q--)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            // cin >> u >> v;
            u++, v++;
            int LCA = lca(u, v);
            int ans = 0;
            for (int i = 0; i < 251; ++i)
            {
                if (shade[LCA][i] == 1)
                {
                    ans++;
                }
            }
            printf("%d\n", ans);
        }
        reset();
    }
}
