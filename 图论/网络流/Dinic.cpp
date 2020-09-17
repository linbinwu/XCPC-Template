//理论复杂度O(n^2m), 求解二分图匹配问题时, 时间复杂度为O(m sqrt(n))
struct Dinic {
    static const int N = ...;//size
    struct Edge { int from, to, cap, flow; };
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[N];
    int dep[N], cur[N];
    bool vis[N];

    void init(int siz) { n = siz; for (int i = 0; i < siz; i++) G[i].clear(); edges.clear(); }

    void addEdge(int from, int to, int cap) {
        edges.push_back(Edge{from, to, cap, 0});
        edges.push_back(Edge{to, from, 0, 0});
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<int> q; q.push(s); dep[s] = 0, vis[s] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto &v: G[x]) {
                Edge& e = edges[v];
                if (!vis[e.to] && e.cap > e.flow) {
                    dep[e.to] = dep[x] + (vis[e.to] = 1);
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int dfs(int u, int a) {
        if (u == t || a == 0) return a;
        int flow = 0;
        for (int& i = cur[u], f; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if (dep[u] + 1 == dep[e.to] && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[u][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int maxFlow(int S, int T) {
        s = S, t = T;
        int flow = 0;
        while (bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(S, INF);
        }
        return flow;
    }
} flow;