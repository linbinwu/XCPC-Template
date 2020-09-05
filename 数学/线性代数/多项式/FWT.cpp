const int mod = ...;
const int inv2 = ...;

int n;
int a[MAX], b[MAX];

inline void get() {
    for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * b[i] % mod;
}

inline void OR(int *f, int x = 1) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; j++)
                f[i + j + k] = (f[i + j + k] + 1ll * f[i + j] * x % mod + mod) % mod;
}

inline void AND(int *f, int x = 1) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; j++)
                f[i + j] = (f[i + j] + 1ll * f[i + j + k] * x % mod + mod) % mod;
}

inline void XOR(int *f, int x = 1) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; j++) {
                ll a0 = f[i + j], a1 = f[i + j + k];
                f[i + j] = (a0 + a1) % mod * x % mod;
                f[i + j + k] = (a0 - a1 + mod) % mod * x % mod;
            }
}

int main() {

    FWT(a, 1); FWT(b, 1); get(); FWT(a, (OR + AND: -1, XOR: inv2));

}