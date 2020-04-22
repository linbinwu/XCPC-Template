#include<cstdio>
#include<cstring>
#include<iostream>
#define int long long
using namespace std;

int fac[25]={1};

int n,k,x;
int val[25];
bool vis[25];

void reverse_contor(int x){
    memset(vis,0,sizeof vis);
    x--;
    int j;
    for(int i=1;i<=n;i++){
        int t=x/fac[n-i];
        for(j=1;j<=n;j++){
            if(!vis[j]){
                if(!t) break;
                t--;
            }
        }
        printf("%d ",j);
        vis[j]=1;
        x%=fac[n-i];
    }
    puts("");
}

int contor(int x[]){
    int p=0;
    for(int i=1;i<=n;i++){
        int t=0;
        for(int j=i+1;j<=n;j++){
            if(x[i]>x[j]) t++;
        }
        p+=t*fac[n-i];
    }
    return p+1;
}

signed main(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i;
    while(k--){
        char ch;cin>>ch;
        if(ch=='P') scanf("%lld",&x),reverse_contor(x);
        else{
            for(int i=1;i<=n;i++) scanf("%lld",&val[i]);
            printf("%lld\n",contor(val));
        }
    }
    return 0;
}
