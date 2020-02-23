int pre[MAX], num[MAX], dis[MAX];//num[i]表示以i为队头时队内元素数量, dis[i]表示到达i的祖先节点的距离

void merge(int x, int y) {
    dis[x] = num[y];
    num[y] += num[x];
    num[x] = 0;
    pre[x] = y;
}

int find(int x) {//路径压缩并查集
    if (x == pre[x]) return x;
    int t = find(pre[x]);
    dis[x] += dis[pre[x]];
    return pre[x] = t;
}