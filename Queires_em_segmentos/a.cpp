#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18
//#define MOD 998244353//1000000007

#define MOD 1000000007
//vector<int> dp(1000006,0);
//vector<int> aux(1000006,0);

int n,q;

int b[100005][20];

vector<int> a(100005);

int ele[25];
int aten;
 

void pre(){
    for (int i = 0; i < n; i++){
        b[i][0] = i;
    }        

    for (int j = 1; ele[j]<= n; j++) {
        for (int i = 0; (ele[j]+i-1) < n; i++) {
            if (a[b[i][j - 1]] < a[b[i+(ele[j-1])][j - 1]]){
                b[i][j] = b[i][j- 1];
            }
            else{
                b[i][j] = b[i +ele[j-1]][j - 1];
            } 
        }
    }
}
 

int query(int l,int r){
    int j = (int)log2(r-l+1);

    return min(a[b[l][j]],a[b[r - ele[j] + 1][j]]);
}


signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    
    int tmp=1;
    for(int i=0;i<=20;i++){
        ele[i]=tmp;
        tmp*=2;
    }


    pre();

    /*for(int j=0;j<10;j++){
        cout<<(1 << j)<<" "<<ele[j]<<" ";
    }
    cout<<"\n";*/

    cin>>q;

    for (int i = 0; i < q; i++) {
        int l,r;
        cin>>l>>r;
        cout << query(l,r)<<"\n";
    }


    return 0;
}
