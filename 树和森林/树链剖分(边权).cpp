//维护边权的树剖
//化边权为点权用线段树维护
//此处3种操作:
//1. 单边修改(修改第k条加入的边)
//2. 将(u, v)间的边反转符号
//3. 查询(u, v)间边的sum, max, min

#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define lc  u<<1
#define rc  u<<1|1
#define mid (t[u].l+t[u].r)/2
using namespace std;
typedef long long ll;
const int MAX = 2e5 + 10;

int N, M;

struct edge {
    int nxt, to, w, from;//需要额外记录from
} e[MAX << 1];
int head[MAX], tot;//tot为边数*2
void add(int u, int v, int w) { e[++tot] = edge{ head[u], v, w, u }; head[u] = tot; }

//重链剖分
int siz[MAX], son[MAX], dep[MAX], fa[MAX], top[MAX];
int id[MAX], cnt;//cnt为点对应在线段树上的位置
void dfs(int u, int par) {
    dep[u] = dep[fa[u] = par] + (siz[u] = 1);
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != par) {
            dfs(v, u);
            siz[u] += siz[v];
            if (!son[u] || siz[v] > siz[son[u]])
                son[u] = v;
        }
}
void dfs2(int u, int topf) {
    id[u] = ++cnt, top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != fa[u] && v != son[u]) dfs2(v, v);
}
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

struct node {//维护最大/小值, 和
    int mx, mn, sum;
    node(int mx = -INF, int mn = INF, int sum = 0): mx(mx), mn(mn), sum(sum) {}
    node merge(const node &rhs) { return node(max(mx, rhs.mx), min(mn, rhs.mn), sum + rhs.sum); }
    void upd() {//符号反转
        sum = -sum;
        mx = -mx, mn = -mn;
        swap(mx, mn);
    }
};
struct SegmentTree {
    int l, r, tag;
    node v;
} t[MAX << 2];
void build(int u, int l, int r) {
    t[u] = SegmentTree{ l, r, 0, node() };
    if (l == r) return;
    build(lc, l, mid); build(rc, mid + 1, r);
}
void push_up(int u) { t[u].v = t[rc].v.merge(t[lc].v); }
void push_down(int u) {
    if (t[u].tag) {
        t[lc].v.upd(), t[lc].tag ^= 1;
        t[rc].v.upd(), t[rc].tag ^= 1;
        t[u].tag = 0;
    }
}
void modify1(int u, int p, int k) {//单点修改值
    if (t[u].l == t[u].r) {
        t[u].v = node{ k, k, k };
        return;
    }
    push_down(u);
    if (p <= mid) modify1(lc, p, k);
    else modify1(rc, p, k);
    push_up(u);
}
void modify2(int u, int ql, int qr) {//反转区间符号
    if (ql <= t[u].l && t[u].r <= qr) {
        t[u].v.upd(), t[u].tag ^= 1;
        return;
    }
    push_down(u);
    if (ql <= mid) modify2(lc, ql, qr);
    if (qr > mid) modify2(rc, ql, qr);
    push_up(u);

}
node query(int u, int ql, int qr) {//区间查询
    if (ql <= t[u].l && t[u].r <= qr) return t[u].v;
    push_down(u);
    if (ql <= mid && qr > mid) return query(lc, ql, qr).merge(query(rc, ql, qr));
    else if (ql <= mid) return query(lc, ql, qr);
    else return query(rc, ql, qr);
}


void update(int x, int y) {//反转(x, y)间所有边的符号
    while (top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        modify2(1, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (x != y) {
        if (dep[x] > dep[y]) swap(x, y);
        modify2(1, id[son[x]], id[y]);
    }
}

node ask(int x, int y) {//查询(x, y)间的信息
    node res;
    while (top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res = res.merge(query(1, id[top[x]], id[x]));
        x = fa[top[x]];
    }
    if (x != y) {
        if (dep[x] > dep[y]) swap(x, y);
        res = res.merge(query(1, id[son[x]], id[y]));
    }
    return res;
}

void init() {//多组样例初始化
    tot = cnt = 0;//tot为边数, cnt为树上的点对应线段树的位置
    memset(head, 0, sizeof(head));
    memset(son, 0, sizeof(son));
}

int main() {

    scanf("%d", &N);
    for (int i = 1; i < N; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }

    //预处理
    int rt = 1; dfs(rt, 0); dfs2(rt, rt);//重链剖分
    build(1, 1, cnt);
    for (int i = 1; i <= tot; i += 2) {
        int u = e[i].from, v = e[i].to;
        if (dep[u] < dep[v]) swap(u, v);//边对应的点为以rt为根时(u, v)中的儿子节点
        modify1(1, id[u], e[i].w);//化边权为点权
    }

    scanf("%d", &M);
    while (M--) {
        char op[10]; int x, y; scanf("%s%d%d", op, &x, &y);
        if (op[0] == 'C') {//单点修改值
            int u = e[(x << 1) - 1].from, v = e[(x << 1) - 1].to;
            if (dep[u] < dep[v]) swap(u, v);//边对应的点为以rt为根时(u, v)中的儿子节点
            modify1(1, id[u], y);//再找到线段树上对应的点id[u]
        }
        else if (op[0] == 'N') update(x, y);//反转(x, y)间所有边的符号
        else {//查询(x, y)间的信息
            node tmp = ask(x, y);
            int ans = 0;
            if (op[0] == 'S') ans = tmp.sum;
            else if (op[1] == 'A') ans = tmp.mx;
            else ans = tmp.mn;
            printf("%d\n", ans);
        }
    }

    return 0;
}