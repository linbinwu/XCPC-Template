struct Dinic {
    static const int MAX_N = 1e2 + 10;
    static const int MAX_M = 1e3 + 10;
    static const int INF   = 0x3f3f3f3f;
    int n, S, T;
    struct Edge { int nxt, to, cap, flow; } e[MAX_M];
    int head[MAX_N], tot;
    int dep[MAX_N], cur[MAX_N], vis[MAX_N];

    void init(int siz, int s, int t) {
        n = siz, S = s, T = t, tot = 1; for (int i = 0; i < siz; i++) head[i] = 0;
    }

    void add(int u, int v, int cap, int flow) { e[++tot] = Edge{head[u], v, cap, flow}; head[u] = tot; }

    void addEdge(int u, int v, int cap) {
        add(u, v, cap, 0);
        add(v, u, 0, 0);
    }

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<int> q; q.push(S); dep[S] = 0, vis[S] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u], v; i; i = e[i].nxt) {
                v = e[i].to;
                if (!vis[v] && e[i].cap > e[i].flow) {
                    dep[v] = dep[u] + (vis[v] = 1);
                    q.push(v);
                }
            }
        }
        return vis[T];
    }

    int dfs(int u, int t, int flow) {
        if (u == t) return flow;
        int res = 0;
        for (int i = cur[u], v; i && res < flow; i = e[i].nxt) {
            cur[u] = i, v = e[i].to;
            if (vis[])

        }
    }

};