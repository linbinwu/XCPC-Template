set<int> st;
set<int>::iterator now;

int lower(int x) {
    now = st.find(x);
    if (now == st.begin()) return -1;
    return *(--now);
}

int upper(int x) {
    now = st.find(x); now++;
    if (now != st.end()) return *now;
    else return -1;
}