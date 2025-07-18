#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18
//#define MOD 998244353//1000000007

#define MOD 1000000007
vector<int> dp(1000006,0);
vector<int> aux(1000006,0);


signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //claramente dp.. vai guardando as possibilidades
    for(int i=1;i<=6;i++){
        dp[i]=1;
        aux[i]=1;
    }

    int n;
    cin>>n;

    for(int i=1;i<n;i++){
        for(int j=1;j<=6;j++){
            dp[i+j]=(dp[i+j]%MOD+dp[i]%MOD)%MOD;
        }
        
    }

    cout<<dp[n]<<"\n";

    

    return 0;
}
