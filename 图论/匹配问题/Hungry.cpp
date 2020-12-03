//不带权重的最大匹配, 复杂度O(nm)
int used[N], match[N];
vector<int> g[N];

bool find(int u) {
    for (auto &v: g[u])
        if (!used[v]) {
            used[v] = 1;
            if (!match[v] || find(match[v])) {
                match[v] = u;
                return true;
            }
        }
    return false;
}

int hungry() {
    int res = 0;
    for (int i = 1; i <= n; i++) match[i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) used[j] = 0;
        if (find(i)) res++;
    }
    return res;
}