ll dfs(int pos, ... , bool lead, bool isMax) {//当前位pos, ...为省略条件, lead判前导零, isMax判前几位数是否选的都是最大值
    if (!pos) return 1;//此处为越过一个数的最后一位(最小的一位), 如123, 越过3这里说明当前已经是123了，所以只有一个数
    //有时候不一定都是返回1，看条件
    if (!isMax && !lead && dp[pos][...][...] != -1) return dp[pos][...][...];//记忆化, 如果有直接返回
    int up = isMax ? a[pos] : 9; //如果一直是最大, 当前位最多也就是a[pos], 超过了就大于这个数了
    ll res = 0;
    for (int i = 0; i <= up; i++) {
        //按限制条件来
        //如, 判是否有前导0
        if (lead) res += dfs(pos - 1, ... , !i, isMax && i == a[pos]);
        else res += dfs(pos - 1, ... , 0, isMax && i == a[pos]);
    }
    return isMax || lead ? res : dp[pos][...][...] = res;//如果有前导0或者是前几位都是最大, 直接返回
    //否则dp[pos][...][...]记录值再返回
}

ll calc(ll x) {
    int pos = 0;
    while (x) a[++pos] = x % 10, x /= 10;
    memset(dp, -1, sz(dp));//约束是不确定的  跟数有关
    //约束确定才放外面, 比如不要62, 对于每一个数都是不要62
    return dfs(pos, ... , 1, 1);
}
