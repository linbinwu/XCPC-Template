struct Hash {
    int b[MAX], tot;
    void init() { tot = 0; }
    void insert(int x) { b[++tot] = x; }
    void build() {
        sort(b + 1, b + 1 + tot);
        tot = unique(b + 1, b + 1 + tot) - (b + 1);
    }
    int pos(int x) { return lower_bound(b + 1, b + 1 + tot, x) - b; }
};