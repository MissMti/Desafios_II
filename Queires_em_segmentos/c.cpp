#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18
//#define MOD 998244353//1000000007

#define MOD 1000000007
//vector<int> dp(1000006,0);
//vector<int> aux(1000006,0);

int n;//100005

vector<int> a(200005);
vector<int> dp(200005,MAX);//guarda p os da frente dele (eh melhor de tras p frente entao...?
vector<int> seg(300005);
//vector<int> ind(200005);



void init(int u, int l, int r){
    if(l==r){
        seg[u]=l;
        return;
    }
    int mid;
    mid=(l+r)/2;
    init(2*u,l,mid);
    init(2*u+1,mid+1,r);
    int x=seg[2*u];
    int y=seg[2*u+1];
    if(a[x]>a[y]){
        seg[u]=x;
    }
    else{
        seg[u]=y;
    }
}


int acha_max(int l, int r,int inf, int sup, int at){
    if(l<=inf && r>=sup){
        return seg[at];
    }
    if(inf>r||l>sup){
        return 100004;
    }
    int m=(inf+sup)/2;

    //return max(acha_max(l,r,inf,m,2*at),acha_max(l,r,m+1,sup,2*at+1));

    int x=acha_max(l,r,inf,m,2*at);
    int y=acha_max(l,r,m+1,sup,2*at+1);
   /* if(x==-1){
        return y;
    }
    if(y==-1){
        return x;
    }*/
    if(a[x]>a[y]){
        return x;
    }
    else{
        return y;
    }
}


signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //n estacoes, soh pode comprar bilhete para i+1 ou a
    //soma de todos os valores pij (minimo de tickets necessario para chegra de i a j)
    //eh dp...
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>a[i];
    }
    a[n]=n;
    int soma=0;

    //segtree de maximos
    a[100004]=-1;
    init(1,1,n);

   /* for(int i=0;i<12;i++){
        cout<<seg[i]<<" ";
    }
    cout<<"\n";*/

    
    
    dp[n]=0;
    //dp[n-1]=1;
    //soma=1;
    for(int i=n-1;i>=1;i--){
        dp[i]=n-i;//pq sempre vai ter q aumentar 1...
        //encontrar o mais longe que posso ir de todos q eu consigo chegar de mim
        //rmq..
        int l=i+1,r=a[i];//jah tenho a info...
        int prox=acha_max(l,r,1,n,1);//tah devolvendo o maximo e nao o indice...
        //cout<<i<<" "<<prox<<"\n";
        //cout<<prox<<"\n";
        dp[i]+=dp[prox]-(a[i]-prox);
        soma+=dp[i];
    }

    cout<<soma<<"\n";

    return 0;
}

