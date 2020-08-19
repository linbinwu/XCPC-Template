//树的直径性质：
//1、直径两端点一定是两个叶子节点
//2、距离任意点最远的点一定是直径的一个端点，这个基于贪心求直径方法的正确性可以得出
//3、对于两棵树，如果第一棵树直径两端点为(u,v)(u,v)，第二棵树直径两端点为(x,y)(x,y)，用一条边将两棵树连接，那么新树的直径一定是u,v,x,y,u,v,x,y,中的两个点
//4、对于一棵树，如果在一个点的上接一个叶子节点，那么最多会改变直径的一个端点
//5、若一棵树存在多条直径，那么这些直径交于一点且交点是这些直径的中点

//P3761 [TJOI2017]城市
//求去掉一条高速公路，并且重新修建一条一样的高速公路(即交通费用一样），使得这个地区的两个城市之间的最大交通费用最小
//只需每次去掉一条路，查询两边连通块树的直径，树的半径
//最后答案为 两个连通块的树的直径 和 树的半径之和 的最小值

const int MAX = 5e3;
int N;
int dis[MAX], tag[MAX], ans, half;
//tag标记两个点是否要分开


struct edge {
    int nxt, to, w;
} e[MAX << 1];

int head[MAX], tot;

void add(int u, int v, int w) {
    e[++tot].to = v;
    e[tot].w = w;
    e[tot].nxt = head[u];
    head[u] = tot;
}

void init() {
    tot = 0;
    memset(head, 0, sz(head));
    memset(tag, 0, sz(tag));
}

pii dfs(int u, int fa) {//查找树的直径
    pii mx = make_pair(dis[u], u);
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != fa && !tag[v]) {
            dis[v] = dis[u] + e[i].w;
            mx = max(mx, dfs(v, u));
        }
    return mx;
}

pii getD(int start) {//从任意出发点开始, 查找树的直径的两个端点, 长度为dis[second]
    dis[start] = 0;
    start = dfs(start, 0).second;
    dis[start] = 0;
    return make_pair(start, dfs(start, 0).second);
}

bool findHalf(int u, int fa, int d, int totLen, int end) {//查找树的半径
    if (u == end) {
        half = min(half, max(totLen - d, d));
        return true;
    }
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != fa && !tag[v]) {
            if (findHalf(v, u, d + e[i].w, totLen, end)) {
                half = min(half, max(totLen - d, d));
                return true;
            }
        }
    return false;
}

pii getHalf(int s) {//得到直径和半径
    pii t = getStartEnd(s); int totLen = dis[t.second];
    half = INF; findHalf(t.first, 0, 0, totLen, t.second);
    return make_pair(totLen, half);
}

bool solve(int u, int fa, int end) {
    if (u == end) return true;
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != fa) {
            if (solve(v, u, end)) {
                //查找v块中树的直径的一半，查找u块中树的直径的一半
                //答案是所有..中最小的
                tag[v] = 1; pii h1 = getHalf(u); tag[v] = 0;
                tag[u] = 1; pii h2 = getHalf(v); tag[u] = 0;
                int n1 = h1.first, n2 = h2.first, n3 = h1.second + h2.second + e[i].w;
                ans = min(ans, max(max(n1, n2), n3));
                tag[v] = tag[u] = 0;
                return true;
            }
        }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    init();
    for (int i = 1; i < N; i++) {
        int u, v, w; cin >> u >> v >> w;
        add(u, v, w); add(v, u, w);
    }
    ans = INF;
    pii t = getStartEnd(1);
    int start = t.first, end = t.second;
    solve(start, 0, end);
    cout << ans << endl;

    return 0;
}