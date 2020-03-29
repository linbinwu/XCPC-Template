
//get pos of first num >= x
int pos(int x) { return lower_bound(b + 1, b + 1 + N, x) - b; }

//get pos of first num > x
int pos(int x) { return upper_bound(b + 1, b + 1 + N, x) - b; }
