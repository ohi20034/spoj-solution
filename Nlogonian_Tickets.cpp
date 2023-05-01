#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX = 2e5 + 10;
const int LOGMAX = 20;
int st[MAX][LOGMAX + 1];
vector<pair<int, int>> gr[MAX];
int level[MAX];
int Table[MAX][LOGMAX + 1];

void dfs(int node, int par, int edge)
{
    st[node][0] = par;
    level[node] = level[par] + 1;
    if (par != -1)
    {
        Table[node][0] = edge;
    }

    for (int k = 1; k <= LOGMAX; ++k)
    {
        if (st[node][k - 1] != -1)
        {
            st[node][k] = st[st[node][k - 1]][k - 1];
            Table[node][k] = max(Table[node][k - 1], Table[st[node][k - 1]][k - 1]);
        }
    }
    for (auto child : gr[node])
    {
        if (child.first != par)
        {
            dfs(child.first, node, child.second);
        }
    }
}
pair<int, int> lca(int u, int v)
{
    int ans = INT_MIN;
    if (level[v] > level[u])
    {
        swap(u, v);
    }

    for (int k = LOGMAX - 1; k >= 0; --k)
    {
        if (level[st[u][k]] >= level[v] && st[u][k] != -1)
        {
            ans = max(ans, Table[u][k]);
            u = st[u][k];
        }
    }
    if (u == v)
    {
        return {ans, u};
    }
    for (int k = LOGMAX - 1; k >= 0; --k)
    {
        if (st[u][k] != st[v][k])
        {
            ans = max(ans, Table[u][k]);
            ans = max(ans, Table[v][k]);
            u = st[u][k];
            v = st[v][k];
        }
    }
    ans = max(ans, Table[u][0]);
    ans = max(ans, Table[v][0]);
    return {ans, st[u][0]};
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cin.tie(0);
    int n;
   // cin >> n;
    while (cin >> n && n)
    {
        memset(st, -1, sizeof st);
        memset(level,0,sizeof level);
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= LOGMAX; ++j)
            {
                Table[i][j] = INT_MIN;
            }
        }
        for (int i = 0; i <= n; ++i)
        {
            gr[i].clear();
        }
        for (int i = 1; i < n; ++i)
        {
            int u, v, d;
            cin >> u >> v >> d;
            gr[u].push_back({v, d});
            gr[v].push_back({u, d});
        }
        dfs(1, -1, 0);
        int q;
        cin >> q;
        while (q--)
        {
            int u, v;
            cin >> u;
            cin >> v;
            cout << lca(u, v).first << "\n";
        }
       // cin >> n;
    }
}