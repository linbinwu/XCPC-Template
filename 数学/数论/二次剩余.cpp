struct Complex {
    ll x, y;
};
ll w;

Complex mul(Complex a, Complex b, ll mod) {//复数乘法
    Complex ans = {0, 0};
    ans.x = ((a.x * b.x % mod + a.y * b.y % mod * w % mod) % mod + mod) % mod;
    ans.y = ((a.x * b.y % mod + a.y * b.x % mod) % mod + mod) % mod;
    return ans;
}

ll binpow_real(ll a, ll b, ll mod) {//实部快速幂
    ll ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}

ll binpow_imag(Complex a, ll b, ll mod) {//虚部快速幂
    Complex ans = {1, 0};
    while (b) {
        if (b & 1) ans = mul(ans, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return ans.x % mod;
}

ll cipolla(ll n, ll mod) {//n = 0外面特判
    n %= mod;
    if (mod == 2) return n;
    if (binpow_real(n, (mod - 1) / 2, mod) == mod - 1) return -1;
    ll a;
    while (1) {//生成随机数再检验找到满足非二次剩余的a
        a = rand() % mod;
        w = ((a * a % mod - n) % mod + mod) % mod;
        if (binpow_real(w, (mod - 1) / 2, mod) == mod - 1) break;
    }
    Complex x = {a, 1};
    return binpow_imag(x, (mod + 1) / 2, mod);
}

int main() {

    ll n, mod; scanf("%lld%lld", &n, &mod);
    if (n == 0) {
        printf("0\n");
        continue;
    }
    ll ans1 = cipolla(n, mod);
    if (ans1 == -1) printf("-1\n");
    else {
        ll ans2 = mod - ans1;
        if (ans1 == ans2) printf("%lld\n", ans1);
        else {
            if (ans1 > ans2) swap(ans1, ans2);
            printf("%lld %lld\n", ans1, ans2);
        }
    }

    return 0;
}