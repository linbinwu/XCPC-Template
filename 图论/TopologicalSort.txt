void topo() {
    queue<int> q;
    for (int i = 1; i <= N; i++)
        if (!degree[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        //
        for (auto &v: g[u]) {
            degree[v]--;
            if (!degree[v]) q.push(v);
        }
    }
    //
}
