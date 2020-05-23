int exgcd(int a, int b, int &x, int &y) {
    //算gcd的同时, 得到ax + by = gcd(a, b)的解(x, y)
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int res = exgcd(b, a % b, x, y);
    int t = y;
    y = x - a / b * y;
    x = t;
    return res;
}

bool solve(int a, int b, int c, int &x, int &y) {
    //求 ax + by = c 的解(x, y)
    //等价于求 ax = b (mod c) 的整数解x
    int d = exgcd(a, b, x, y);
    if (c % d != 0) return false;
    int k = c / d;
    x *= k, y *= k;
    /*求ax = b (mod c)的最小正整数解
    int t = b / __gcd(a, b);
    x = (x % t + t) % t;*/
    return true;
}