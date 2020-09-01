#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

const ll mod = 998244353;
const ll G = 3;
const ll invG = qpow(G, mod - 2, mod);
const ll inv2 = qpow(2ll, mod - 2, mod);
int tr[N];

int getLen(int n) {
    int len = 1;
    while (len < (n << 1)) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    return len;
}

void NTT(ll *A, int len, int type) {
    for (int i = 0; i < len; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2; i <= len; i <<= 1) {
        int mid = i / 2;
        ll Wn = qpow(type == 1 ? G : invG, (mod - 1) / i, mod);
        for (int k = 0; k < len; k += i) {
            ll w = 1;
            for (int l = k; l < k + mid; l++) {
                ll t = w * A[l + mid] % mod;
                A[l + mid] = (A[l] - t + mod) % mod;
                A[l] = (A[l] + t) % mod;
                w = w * Wn % mod;
            }
        }
    }
    if (type == -1) {
        ll invn = qpow(len, mod - 2, mod);
        for (int i = 0; i < len; i++)
            A[i] = A[i] * invn % mod;
    }
}

void getDer(ll *f, ll *g, int len) { for (int i = 1; i < len; i++) g[i - 1] = f[i] * i % mod; g[len - 1] = 0; }

void getInt(ll *f, ll *g, int len) { for (int i = 1; i < len; i++) g[i] = f[i - 1] * qpow(i, mod - 2, mod) % mod; g[0] = 0; }

void getInv(ll *f, ll *g, int n) {
    if (n == 1) return (void) (g[0] = qpow(f[0], mod - 2, mod));
    getInv(f, g, (n + 1) >> 1);
    int len = getLen(n);
    static ll a[N];
    for (int i = 0; i < len; ++i) a[i] = i < n ? f[i] : 0;
    NTT(a, len, 1), NTT(g, len, 1);
    for (int i = 0; i < len; i++)
        g[i] = 1LL * (2 - 1LL * a[i] * g[i] % mod + mod) % mod * g[i] % mod;
    NTT(g, len, -1);
    for (int i = n; i < len; i++) g[i] = 0;
}

void getLn(ll *f, ll *g, int n) {
    static ll a[N], b[N];
    getDer(f, a, n);
    getInv(f, b, n);
    int len = getLen(n);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
    NTT(a, len, -1);
    getInt(a, g, len);
    for (int i = n; i < len; i++) g[i] = 0;
    for (int i = 0; i < len; i++) a[i] = b[i] = 0;
}

void getExp(ll *f, ll *g, int n) {
    if (n == 1) return (void) (g[0] = 1);
    getExp(f, g, (n + 1) >> 1);
    static ll a[N];
    getLn(g, a, n);
    a[0] = (f[0] + 1 - a[0] + mod) % mod;
    for (int i = 1; i < n; i++) a[i] = (f[i] - a[i] + mod) % mod;
    int len = getLen(n);
    NTT(a, len, 1), NTT(g, len, 1);
    for (int i = 0; i < len; i++) g[i] = g[i] * a[i] % mod;
    NTT(g, len, -1);
    for (int i = n; i < len; i++) g[i] = 0;
    for (int i = 0; i < len; i++) a[i] = 0;
}

void getPow(ll *f, ll *g, int n, ll k) {
    static ll a[N];
    getLn(f, a, n);
    for (int i = 0; i < n; i++) a[i] = a[i] * k % mod;
    getExp(a, g, n);
    for (int i = 0, len = getLen(n); i < len; i++) a[i] = 0;
}


struct Complex { ll x, y; }; ll w;
Complex mul(Complex a, Complex b, ll mod) {
    Complex ans = {0, 0};
    ans.x = ((a.x * b.x % mod + a.y * b.y % mod * w % mod) % mod + mod) % mod;
    ans.y = ((a.x * b.y % mod + a.y * b.x % mod) % mod + mod) % mod;
    return ans;
}
ll binpow_imag(Complex a, ll b, ll mod) {
    Complex ans = {1, 0};
    while (b) {
        if (b & 1) ans = mul(ans, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return ans.x % mod;
}
ll cipolla(ll n, ll mod) {
    srand(time(0));
    n %= mod;
    if (mod == 2) return n;
    if (qpow(n, (mod - 1) / 2, mod) == mod - 1) return -1;
    ll a;
    while (1) {
        a = rand() % mod;
        w = ((a * a % mod - n) % mod + mod) % mod;
        if (qpow(w, (mod - 1) / 2, mod) == mod - 1) break;
    }
    Complex x = {a, 1};
    return binpow_imag(x, (mod + 1) / 2, mod);
}
void getSqrt(ll *f, ll *g, int n) {
    if (n == 1) {
        if (f[0] == 0) g[0] = f[0];
        else {
            ll t = cipolla(f[0], mod);
            g[0] = min(t, mod - t);
        }
        return;
    }
    getSqrt(f, g, (n + 1) >> 1);
    int len = getLen(n);
    static ll a[N], b[N];
    for (int i = 0; i < len; ++i) a[i] = i < n ? f[i] : 0;
    getInv(g, b, n);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = 1ll * a[i] * b[i] % mod;
    NTT(a, len, -1);
    for (int i = 0; i < n; i++) g[i] = (g[i] + a[i]) % mod * inv2 % mod;
    for (int i = n; i < len; i++) g[i] = 0;
    for (int i = 0; i < len; i++) a[i] = b[i] = 0;
}

ll f[N], g[N];

int main() {
#ifdef ACM_LOCAL
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &f[i]);

    getSqrt(f, g, n);
    for (int i = 0; i < n; i++)
        printf("%lld ", g[i]);

    return 0;
}