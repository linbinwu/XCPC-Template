vector<int> manacher(char *s) {
    int len = strlen(s);
    static char t[N];
    int now = 0;
    t[now] = '$', t[++now] = '#';
    for (int i = 0; i < len; i++) t[++now] = s[i], t[++now] = '#';

    vector<int> p(len + 1);
    len = now;
    for (int i = 1, r = 0, mid = 0; i <= len; i++) {
        if (i <= r) p[i] = min(p[2 * mid - i], r - i + 1);
        while (t[i - p[i]] == t[i + p[i]]) ++p[i];
        if (p[i] + i > r) r = p[i] + i - 1, mid = i;
    }
    return p;
}