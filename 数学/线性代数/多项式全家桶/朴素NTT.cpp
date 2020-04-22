//mod比最终答案要大
//如果中间乘法计算会爆ll, 换成按位乘
//精度高, 比3次FFT要快(复数运算=>整数运算)

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int tr[MAX], n;
const ll mod = 998244353;
const ll G = 3;
const ll invG = qpow(G, mod - 2, mod);

void NTT(ll *A, int type) {
    for (int i = 0; i < n; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int len = 2; len <= n; len <<= 1) {
        int mid = len / 2;
        ll Wn = qpow(type == 1 ? G : invG, (mod - 1) / len, mod);
        for (int k = 0; k < n; k += len) {
            ll w = 1;
            for (int l = k; l < k + mid; l++) {
                ll t = w * A[l + mid] % mod;
                A[l + mid] = (A[l] - t + mod) % mod;
                A[l] = (A[l] + t) % mod;
                w = w * Wn % mod;
            }
        }
    }

}

int N, M;
ll a[MAX], b[MAX];

int main() {

    scanf("%d%d", &N, &M);
    for (int i = 0; i <= N; i++) scanf("%lld", &a[i]);
    for (int i = 0; i <= M; i++) scanf("%lld", &b[i]);

    n = 1; while (n <= N + M) n <<= 1;
    for (int i = 0; i < n; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);

    NTT(a, 1), NTT(b, 1);

    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;

    NTT(a, -1);

    ll invn = qpow(n, mod - 2, mod);
    for (int i = 0; i <= N + M; i++)
        printf("%lld ", a[i] * invn % mod);

    return 0;
}