struct Splay {
#define rt  ch[0][1]
#define lc  ch[u][0]
#define rc  ch[u][1]
    int tot, totElement;
    int val[MAX], fa[MAX], sum[MAX], tag[MAX];
    int ch[MAX][2];
    Splay() { tot = totElement = 0; }
    void push_up(int u) { sum[u] = sum[lc] + sum[rc] + 1; }
    void push_down(int u) {
        if (tag[u]) {
            tag[lc] ^= 1;
            tag[rc] ^= 1;
            tag[u] = 0;
            swap(lc, rc);
        }
    }
    int identify(int u) { return ch[fa[u]][1] == u; }
    void connect(int u, int par, int son) { ch[par][son] = u, fa[u] = par; }
    void rotate(int u) {
        int fc = identify(u), f = fa[u];
        int gc = identify(f), g = fa[f];
        int uc = fc ^ 1, son = ch[u][uc];
        connect(son, f, fc);
        connect(f, u, uc);
        connect(u, g, gc);
        push_up(f);
        push_up(u);
    }
    void splay(int u, int v) {
        v = fa[v];
        while (fa[u] != v) {
            int f = fa[u];
            if (fa[f] != v)
                rotate(identify(u) ^ identify(f) ? u : f);
            rotate(u);
        }
    }
    int creat(int v, int par) {
        val[++tot] = v;
        fa[tot] = par;
        sum[tot] = 1;
        return tot;
    }
    int insert(int v) {
        totElement++;
        if (totElement == 1) {
            creat(v, 0);
            return rt = tot;
        }
        int u = rt;
        while (1) {
            sum[u]++;
            if (v == val[u]) return u;
            int nxt = v > val[u];
            if (!ch[u][nxt]) {
                creat(v, u);
                splay(ch[u][nxt] = tot, rt);
                return tot;
            }
            u = ch[u][nxt];
        }
    }
    int queryKth(int k) {
        if (k > totElement) return -1;
        int u = rt;
        while (1) {
            push_down(u);
            if (k > sum[lc] && k <= sum[lc] + 1) {
                splay(u, rt);
                return val[u];
            }
            if (k <= sum[lc]) u = lc;
            else {
                k -= sum[lc] + 1;
                u = rc;
            }
        }
    }
    void reverse(int ql, int qr) {
        ql = queryKth(ql);
        qr = queryKth(qr + 2);
        splay(ql, rt);
        splay(qr, ch[ql][1]);
        tag[ch[qr][0]] ^= 1;
    }
} splay;