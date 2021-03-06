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