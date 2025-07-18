#include <bits/stdc++.h>

using namespace std;

#define int long long
//#define MAX 1e18
//#define MOD 998244353//1000000007

//vector<vector<int>> dp(550,vector<int>(550,MAX));


vector<int> V(100005);


signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin>>n;

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        V[i]=x;
    }

    sort(V.begin(),V.begin()+n);

    /*for(int i=0;i<n;i++){
        cout<<V[i]<<" ";
    }
    cout<<"\n";*/
    
    int q;
    cin>>q;

    int l,r;
    for(int i=0;i<q;i++){
        l=-1;
        r=n;
        //int m=(l+r)/2;
        int x;
        cin>>x;

        while(l<r-1){
            int m=(l+r)/2;
            if(V[m]<=x){
                l=m;
            }
            else{
                r=m;
            }
        }
        cout<<r<<"\n";


    }

    

    return 0;
}
