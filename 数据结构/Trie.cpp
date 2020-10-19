struct Trie {
    static const int MAX_N = 1e6 + 10, rt = 0;
    int ch[MAX_N][26], sum[MAX_N], tot;
    void init() { tot = 0; memset(ch[tot], 0, sizeof(ch[tot])); sum[tot] = 0; }
    void insert(char *s, int val) {
        int len = strlen(s), u = rt;
        for (int i = 0; i < len; i++) {
            int nxt = s[i] - 'a';
            if (!ch[u][nxt]) {
                ch[u][nxt] = ++tot;
                memset(ch[tot], 0, sizeof(ch[tot]));
                sum[tot] = 0;
            }
            u = ch[u][nxt];
        }
        sum[u] += val;
    }
    int query(char *s) {
        int len = strlen(s), u = rt;
        for (int i = 0; i < len; i++) {
            int nxt = s[i] - 'a';
            if (!ch[u][nxt]) return -1;
            u = ch[u][nxt];
        }
        if (!sum[u]) return -1;
        return sum[u];
    }
};