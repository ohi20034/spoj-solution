#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX = 1e5 + 9;
const int LOGMAX = 20;
int n;
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
            Table[node][k] = Table[node][k - 1] + Table[st[node][k - 1]][k - 1];
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
    int ans = 0;
    if (level[v] > level[u])
    {
        swap(u, v);
    }

    for (int k = LOGMAX - 1; k >= 0; --k)
    {
        if (level[st[u][k]] >= level[v] && st[u][k] != -1)
        {
            ans += Table[u][k];
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
            ans += Table[u][k];
            ans += Table[v][k];
            u = st[u][k];
            v = st[v][k];
        }
    }
    ans += Table[u][0];
    ans += Table[v][0];
    return {ans, st[u][0]};
}

int kth(int k, int u, int Lca)
{
    int cnt = 1;
    int ans = u;
    for (int j = LOGMAX; j >= 0; --j)
    {
        if (cnt + (1 << j) <= k)
        {
            u = st[u][j];
            ans = u;
            cnt += j + 1;
        }
    }

    return ans;
}
int getkth(int node, int k)
{
    for (int j = 0; j < LOGMAX; ++j)
    {
        if (k & (1 << j))
        {
            node = st[node][j];
        }
    }
    return node;
}
int32_t main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        cin >> n;

        for (int i = 0; i <= MAX; ++i)
        {
            gr[i].clear();
        }
        memset(level, 0, sizeof level);
        memset(st, -1, sizeof st);

        for (int i = 1; i < n; ++i)
        {
            int u, v, d;
            cin >> u >> v >> d;
            gr[u].push_back({v, d});
            gr[v].push_back({u, d});
        }
        dfs(1, -1, 0);
        string s;
        while (true)
        {
            cin >> s;
            if (s == "DONE")
            {
                break;
            }
            if (s == "DIST")
            {
                int u, v;
                cin >> u >> v;
                int Lca = lca(u, v).second;
                cout << lca(u, v).first << "\n";
            }
            else
            {
                int u, v, k;
                cin >> u >> v >> k;
                int Lca = lca(u, v).second;
                int dis1 = 1 + level[u] + level[Lca] - 2 * level[Lca];
                int dis2 = 1 + level[v] + level[Lca] - 2 * level[Lca];

                if (dis1 == k)
                {
                    cout << Lca << "\n";
                }
                else if (dis1 > k)
                {
                    cout << getkth(u, k - 1) << "\n";
                }
                else
                {
                    k -= dis1;
                    cout << getkth(v, dis2 - k - 1) << endl;
                }
            }
        }
    }
}
