//卡特兰数有以下几种形式:
//
//
//

int catalan[N];
void getCatalan(int siz) {
    catalan[0] = catalan[1] = 1;
    for (int i = 2; i <= siz; i++) {
        //catalan[i] = catalan[i - 1] * (4 * i - 2) % mod * qpow(i + 1, mod - 2) % mod;
        catalan[i] = (C(2 * i, i) - C(2 * i, i - 1) + mod) % mod;
    }
}