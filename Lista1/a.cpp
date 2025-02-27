#include <bits/stdc++.h>

using namespace std;

#define int long long
//#define MAX 1e18
//#define MOD 998244353//1000000007

//vector<vector<int>> dp(550,vector<int>(550,MAX));



signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin>>n;

    set<int> S;

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        S.insert(x);
    }

    cout<<S.size()<<"\n";
    

    return 0;
}

