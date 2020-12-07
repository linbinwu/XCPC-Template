int vis[N], prime[N], num;
void makePrime(int siz) {
    num = 0;
    for (int i = 2; i <= siz; i++) {
        if (!vis[i]) prime[++num] = i;
        for (int j = 1; j <= num && i * prime[j] <= siz; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

void divide(ll x) {
    for (int i = 1; i <= num && 1ll * prime[i] * prime[i] <= x; i++)
        if (x % prime[i] == 0) {
            int cnt = 0;
            while (x % prime[i] == 0) x /= prime[i], cnt++;
            store.push_back({prime[i], cnt});
        }
    if (x > 1) store.push_back({x, 1});
}