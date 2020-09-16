#define lowbit(x) x&-x
int BIT[N];
void upd(int p, int k) { for (; p < N; p += lowbit(p)) BIT[p] += k; }
int ask(int p) { int res = 0; for (; p; p -= lowbit(p)) res += BIT[p]; return res; }