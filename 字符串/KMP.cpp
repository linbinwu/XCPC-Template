vector<int> getNext(string s) {
    int n = s.length();
    vector<int> nxt(n);
    for (int i = 1; i < n; i++) {
        int j = nxt[i - 1];
        while (j > 0 && s[i] != s[j]) j = nxt[j - 1];
        if (s[i] == s[j]) j++;
        nxt[i] = j;
    }
    return nxt;
}

int N = strlen(s + 1), M = strlen(t + 1);
    int j = 0;
    for (int i = 1; i <= N; i++) {
        while (j && t[j + 1] != s[i]) j = nxt[j];
        if (t[j + 1] == s[i]) j++;
        if (j == M) {
            ans.push_back(i - M + 1);
            j = nxt[j];
        }
    }