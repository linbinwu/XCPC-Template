//spfa·ÑÓÃÁ÷
struct MCMF {
    static const int N = ...;
    static const int M = ...;
    struct Edge { int nxt, to, cap, cost; } e[M << 1];
    int head[N], tot;
    int n, m;
    int cur[N], dis[N], minCost;
    bool vis[N];

    void init(int siz) { n = siz, tot = 1; for (int i = 0; i < siz; i++) head[i] = 0; }

    void add(int u, int v, int w, int c) { e[++tot] = Edge{head[u], v, w, c}; head[u] = tot; }

    void addEdge(int u, int v, int w, int c) { add(u, v, w, c), add(v, u, 0, -c); }

    bool spfa(int s, int t) {
        for (int i = 0; i < n; i++) dis[i] = INF, cur[i] = head[i];
        queue<int> q; q.push(s), dis[s] = 0, vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop(), vis[u] = 0;
            for (int i = head[u], v; i; i = e[i].nxt) {
                if (e[i].cap && dis[v = e[i].to] > dis[u] + e[i].cost) {
                    dis[v] = dis[u] + e[i].cost;
                    if (!vis[v]) q.push(v), vis[v] = 1;
                }
            }
        }
        return dis[t] != INF;
    }

    int dfs(int u, int t, int flow) {
        if (u == t) return flow;
        vis[u] = 1;
        int ans = 0;
        for (int &i = cur[u], v; i && ans < flow; i = e[i].nxt) {
            if (!vis[v = e[i].to] && e[i].cap && dis[v] == dis[u] + e[i].cost) {
                int x = dfs(v, t, min(e[i].cap, flow - ans));
                if (x) minCost += x * e[i].cost, e[i].cap -= x, e[i ^ 1].cap += x, ans += x;
            }
        }
        vis[u] = 0;
        return ans;
    }

    pair<int, int> mcmf(int s, int t) {
        int ans = 0; minCost = 0;
        while (spfa(s, t)) {
            int x;
            while ((x = dfs(s, t, INF))) ans += x;
        }
        return make_pair(ans, minCost);
    }
} flow;