/*
洛谷P3403: 给定x[0], x[1], x[2], ..., x[n - 1], 对于k <= h, 求有多少个k满足a[0]x[0] + a[1]x[1] + ... + a[n - 1]x[n - 1] = k
洛谷P2662: 最大的不能被x[0], x[1], ..., x[n - 1]表示的数(从小到大), 显然如果gcd(x[i]) = x[0], 无解, 否则跑同余最短路求出max(dis) - x[0]即为答案
解决形如上述类型的题目
 */

struct Node {
    ll now, d;
    bool operator < (const Node &rhs) const {
        return d > rhs.d;
    }
};

priority_queue<Node> q;

ll dis[N];

void dijkstra(int s, int n) {
    vector<int> vis(n);
    for (int i = 0; i < n; i++) dis[i] = INF;
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

ll solve(ll *x, int n, ll h) {
    sort(x, x + n);
    if (x[0] == 1) return h;
    for (int i = 0; i < x[0]; i++)
        for (int j = 1; j < n; j++)
            add(i, (i + x[j]) % x[0], x[j]);
    dijkstra(1, x[0]);
    ll res = 0;
    for (int i = 0; i < x[0]; i++)
        if (dis[i] <= h) res += (h - dis[i] + x[0] - 1) / x[0];
    return res;
}

ll x[N];

int main() {
#ifdef ACM_LOCAL
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    ll h, n; scanf("%lld", &h);
    for (int i = 0; i < n; i++) scanf("%lld", &x[i]);
    printf("%lld\n", solve(x, n, h));


    return 0;
}
