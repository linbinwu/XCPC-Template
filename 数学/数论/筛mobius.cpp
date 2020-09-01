int vis[N], prime[N], num, mu[N];
void makeMobius(int siz) {
    mu[1] = 1, num = 0;
    for (int i = 2; i <= siz; i++) {
        if (!vis[i]) prime[++num] = i, mu[i] = -1;
        for (int j = 1; j <= num && i * prime[j] <= siz; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            else mu[i * prime[j]] = mu[i] * mu[prime[j]];
        }
    }
}