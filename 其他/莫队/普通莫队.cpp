
int n, m;
int belong[N], size;
int ans[N], res;

struct node {
    int l, r, id;
    bool operator < (const node &rhs) const {//ÆæÅ¼ÓÅ»¯
        return belong[l] ^ belong[rhs.l] ? belong[l] < belong[rhs.l] :
               ((belong[l] & 1) ? r < rhs.r : r > rhs.r);
    }
} q[N];

void add(int x) {

}

void del(int x) {

}

int main() {

    size = sqrt(n); int num = ceil((long double)n / size);
    for (int i = 1, j = 1; i <= num; i++)
        while (j <= i * size && j <= n)
            belong[j++] = i;


    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        int ql = q[i].l, qr = q[i].r;
        while (l < ql) del(l++);
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (r > qr) del(r--);
        ans[q[i].id] = res;
    }



}