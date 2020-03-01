ll mu(ll x) {
    int cnt = 0;
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0) {
            int now = 0;
            while (x % i == 0) x /= i, now++;
            if (now > 1) return 0;//质数幂次大于1, 返回0
            cnt++;//质数个数
        }
    if (x > 1) cnt++;
    return (cnt & 1) ? -1 : 1;//偶数1, 奇数-1
}