int vis[N], prime[N], num, phi[N];
void makePhi(int siz) {
    phi[1] = 1;
    for (int i = 2; i <= siz; i++) {
        if (!vis[i]) prime[++num] = i, phi[i] = i - 1;
        for (int j = 1; j <= num && i * prime[j] <= siz; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}