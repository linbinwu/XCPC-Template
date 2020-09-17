vector<pii> store;

void divide(ll x) {
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                x /= i, cnt++;
            }
            store.push_back(make_pair(i, cnt));
        }
    if (x > 1) store.push_back(make_pair(x, 1));
}