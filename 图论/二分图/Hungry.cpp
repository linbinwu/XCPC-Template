//不带权重的最大匹配, 复杂度O(nm)
int used[MAX], match[MAX];
vector<int> g[MAX];

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
    for (int i = 1; i <= N; i++) match[i] = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) used[j] = 0;
        if (find(i)) res++;
    }
    return res;
}