#include <bits/stdc++.h>

using namespace std;

#define int long long
//#define MAX 1e18
//#define MOD 998244353//1000000007
//vector<int> dp(1000006);

int n,m;


vector<int> a(200005);
vector<int> seg(1000006);
vector<int> ind(1000006);

int upd(int u, int l, int r, int x){
    if(seg[u]<x){
        return 0;
    }
    if(l==r){
        seg[u]-=x;
        return l;
    }
    int mid;
    mid=(l+r)/2;
    int tmp;
    if(seg[2*u]>=x){
        tmp=upd(2*u,l,mid,x);
    }
    else{
        tmp=upd(2*u+1,mid+1,r,x);
    }
    seg[u]=max(seg[2*u],seg[2*u+1]);
    return tmp;
}

void init(int u, int l, int r){
    if(l==r){
        seg[u]=a[l];
        //ind[u]=l;
        return;
    }
    int mid;
    mid=(l+r)/2;
    init(2*u,l,mid);
    init(2*u+1,mid+1,r);
    seg[u]=max(seg[2*u],seg[2*u+1]);
}

signed main() {

    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //seg tree de maximos, fazer as trocas na volta (ou na ida?)
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    init(1,1,n);

    /*for(int i=1;i<=2*n;i++){
        cout<<seg[i]<<" ";
    }
    cout<<"\n";*/

    for(int i=0;i<m;i++){
        int q;
        cin>>q;
        cout<<upd(1,1,n,q)<<" ";
        //upd(1,1,n,q);
        /*for(int i=1;i<=2*n;i++){
            cout<<seg[i]<<" ";
        }
        cout<<"\n";*/
    }
    cout<<"\n";

    return 0;
}
