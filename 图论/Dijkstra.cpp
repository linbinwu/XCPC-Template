//O((N+M)logM)
struct Node {
    int now, d;
    bool operator < (const Node &rhs) const {
        return d > rhs.d;
    }
};

priority_queue<Node> q;

void dijkstra(int s) {
    for (int i = 1; i <= n; i++) dis[i] = INF, vis[i] = 0;
    dis[s] = 0;
    q.push(Node{s, dis[s]});
    while (!q.empty()) {
        Node p = q.top(); q.pop();
        int u = p.now;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u], v; i; i = e[i].nxt)
            if (dis[u] + e[i].w < dis[v = e[i].to]) {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v]) q.push(Node{v, dis[v]});
            }
    }
}