void getNext(string str) {
    M = str.size() - 1, nxt[0] = -1;
    int match = -1;
    for (int i = 1; i <= M; i++) {
        while (match != -1 && str[match + 1] != str[i]) match = nxt[match];
        if (str[match + 1] == str[i]) match++;
        if (str[match + 1] == str[i + 1]) nxt[i] = nxt[match + 1];
        else nxt[i] = match;
    }
}

int N = strlen(s + 1), M = strlen(t + 1);
    int j = 0;
    for (int i = 1; i <= N; i++) {
        while (j && t[j + 1] != s[i])
            j = nxt[j];
        if (t[j + 1] == s[i]) j++;
        if (j == M) {
            ans.push_back(i - M + 1);
            j = nxt[j];
        }
    }