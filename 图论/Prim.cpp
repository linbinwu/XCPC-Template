struct Node {
    int to, d;
    bool operator < (const Node &rhs) const {
        return d > rhs.d;
    }
};

ll prim(int n) {
    vector<int> vis(n + 1);
    priority_queue<Node> q; q.push({1, 0});
    ll ans = 0, cnt = 0;
    while (!q.empty() && cnt <= n) {
        Node now = q.top(); q.pop();
        int u = now.to, dis = now.d;
        if (vis[u]) continue;
        vis[u] = 1, cnt++, ans += dis;
        for (int i = head[u], v; i; i = e[i].nxt)
            if (!vis[v = e[i].to]) q.push({v, e[i].w});
    }
    return ans;
}