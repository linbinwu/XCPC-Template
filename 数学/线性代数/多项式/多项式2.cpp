namespace FFT {
#define mod 998244353
#define G 3
#define maxn 501000
    typedef long long ll;
    int bh[maxn], tmpA[maxn], tmpB[maxn], tmpC[maxn], tmp[maxn], lim = maxn, w[2][maxn];

    int qpow(int a, int b) {
        int ans = 1, tmp = a;
        for (; b; b >>= 1, tmp = 1ll * tmp * tmp % mod)
            if (b & 1)ans = 1ll * ans * tmp % mod;
        return ans;
    }

    int qpow(int a, int b, int p) {
        int ans = 1, tmp = a;
        for (; b; b >>= 1, tmp = 1ll * tmp * tmp % p)
            if (b & 1)ans = 1ll * ans * tmp % p;
        return ans;
    }

    void init(int b) {
        for (int i = 1; i < (1 << b); i <<= 1) {
            int wn = qpow(G, (mod - 1) / (i << 1));
            for (int j = 0; j < i; ++j)w[1][i + j] = (j ? 1ll * wn * w[1][i + j - 1] % mod : 1);
            wn = qpow(G, mod - 1 - (mod - 1) / (i << 1));
            for (int j = 0; j < i; ++j)w[0][i + j] = (j ? 1ll * wn * w[0][i + j - 1] % mod : 1);
        }
    }

    ll gmod(ll x) {
        return x >= mod ? x - mod : x;
    }

    void fft(int h[], int len, int flag) {
        if (flag == -1)flag = 0;
        for (int i = 0, j = 0; i < len; ++i) {
            if (i < j)swap(h[i], h[j]);
            for (int k = len >> 1; (j ^= k) < k; k >>= 1);
        }
        for (int i = 1; i < len; i <<= 1)
            for (int j = 0; j < len; j += (i << 1))
                for (int k = 0; k < i; ++k) {
                    int x = h[j + k], y = (ll) h[j + k + i] * w[flag][i + k] % mod;
                    h[j + k] = gmod((ll) x + y);
                    h[j + k + i] = gmod((ll) x - y + mod);
                }
        if (flag == 0) {
            int x = qpow(len, mod - 2);
            for (int i = 0; i < len; ++i)
                h[i] = 1ll * h[i] * x % mod;
        }
    }

    void poly_mul(const int A[], int lenA, const int B[], int lenB, int C[], int lenc) {
        int l = 1, k = 0, L = min(lenA, lenc) + min(lenB, lenc) + 1;
        if (1ll * lenA * lenB <= 400) {
            for (int i = 0; i < L; ++i)tmpA[i] = 0;
            for (int i = 0; i < lenA; ++i)
                if (A[i])
                    for (int j = 0; j < lenB; ++j)
                        if (B[j])
                            tmpA[i + j] = (tmpA[i + j] + 1ll * A[i] * B[j]) % mod;
            for (int i = 0; i < lenc && i < L; ++i)C[i] = tmpA[i];
            for (int i = L; i < lenc; ++i)C[i] = 0;
            return;
        }
        while (l < L)l <<= 1, k++;
        memset(tmpA, 0, l << 2);
        memset(tmpB, 0, l << 2);
        memcpy(tmpA, A, min(lenA, lenc) << 2);
        memcpy(tmpB, B, min(lenB, lenc) << 2);
        fft(tmpA, l, 1), fft(tmpB, l, 1);
        for (int i = 0; i < l; ++i)tmpA[i] = 1ll * tmpA[i] * tmpB[i] % mod;
        fft(tmpA, l, -1);
        for (int i = 0; i < lenc && i < L; ++i)C[i] = tmpA[i];
        for (int i = L; i < lenc; ++i)C[i] = 0;
    }

    void poly_inv(int n, const int a[], int C[]) {
        if (n == 1) {
            C[0] = qpow(a[0], mod - 2);
            return;
        }
        static int A[maxn];
        A[0] = qpow(a[0], mod - 2);
        int m = (n + 1) / 2, len = 1, k = 0;
        poly_inv(m, a, C);
        while (len < n + n)len <<= 1, k++;
        memcpy(A, a, n << 2);
        memset(A + n, 0, (len - n) << 2);
        memset(C + m, 0, (len - m) << 2);
        fft(A, len, 1), fft(C, len, 1);
        for (int i = 0; i < len; ++i)C[i] = 1ll * (2ll - 1ll * A[i] * C[i] % mod + mod) * C[i] % mod;
        fft(C, len, -1);
    }

    void poly_div(const int a[], int lena, const int b[], int lenb, int C[], int &plen) {
        static int A[maxn], B[maxn];
        while (!a[lena - 1] && lena >= 1)lena--;
        while (!b[lenb - 1] && lenb >= 1)lenb--;
        if (lena < lenb) {
            plen = 1, C[0] = 0;
            return;
        }
        plen = lena - lenb + 1;
        memcpy(A, a, lena << 2);
        memcpy(B, b, lenb << 2);
        reverse(A, A + lena);
        reverse(B, B + lenb);
        poly_inv(plen, B, tmp);
        poly_mul(tmp, plen, A, lena, C, plen);
        reverse(C, C + plen);
    }

    typedef vector<int> Poly;

    int SZ(const Poly &v) { return v.size(); }

    void upd(Poly &v) { while (v.size() > 1 && !v.back())v.pop_back(); }

    Poly operator*(const Poly &a, const Poly &b) {
        Poly ret(SZ(a) + SZ(b) - 1);
        poly_mul(a.data(), SZ(a), b.data(), SZ(b), ret.data(), SZ(ret));
        upd(ret);
        return ret;
    }

    Poly operator/(const Poly &a, const Poly &b) {
        int len;
        poly_div(a.data(), SZ(a), b.data(), SZ(b), tmp, len);
        Poly ret = Poly(tmp, tmp + len);
        upd(ret);
        return ret;
    }

    Poly operator-(const Poly &a, const Poly &b) {
        Poly
        ret(max(SZ(a), SZ(b)));
        for (int i = 0; i < SZ(ret); ++i)
            ret[i] = (1ll * (i < SZ(a) ? a[i] : 0) - (i < SZ(b) ? b[i] : 0) + mod) % mod;
        upd(ret);
        return ret;
    }

    Poly operator+(const Poly &a, const Poly &b) {
        Poly
        ret(max(SZ(a), SZ(b)));
        for (int i = 0; i < SZ(ret); ++i)
            ret[i] = (1ll * (i < SZ(a) ? a[i] : 0) + (i < SZ(b) ? b[i] : 0)) % mod;
        upd(ret);
        return ret;
    }

    Poly operator%(const Poly &a, const Poly &b) {
        int len;
        poly_div(a.data(), SZ(a), b.data(), SZ(b), tmp, len);
        poly_mul(b.data(), SZ(b), tmp, len, tmp, SZ(a));
        for (int i = 0; i < SZ(a); ++i)
            tmp[i] = (1ll * a[i] - tmp[i] + mod) % mod;
        for (len = SZ(a); len > 1 && !tmp[len - 1]; len--);
        return Poly(tmp, tmp + len);
    }

    void print(const Poly &x) {
        printf("\n[len=%d]", SZ(x));
        for (int i = 0; i < SZ(x); ++i)
            printf("%d ", x[i]);
        puts("");
    }

    Poly getinv(Poly g, int n) {
        for (int i = 0; i < n; ++i)tmpC[i] = 0;
        for (int i = 0; i < g.size() && i < n; ++i)tmpC[i] = g[i];
        poly_inv(n, tmpC, tmp);
        return Poly(tmp, tmp + n);
    }

    int getrt(int p) {
        if (p == 2)return 1;
        for (int i = 2; i < p; i++) {
            int flg = 1, s = p - 1;
            for (int j = 1; 1ll * j * j <= s && flg; j++)
                if (s % j == 0) {
                    flg &= qpow(i, j, p) != 1;
                    if (j != 1)flg &= qpow(i, s / j, p) != 1;
                }
            if (flg)return i;
        }
        exit(1);
    }

#undef maxn
#undef G
#undef mod
};