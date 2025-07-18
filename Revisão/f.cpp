#include <bits/stdc++.h>

using namespace std;

#define int long long
//#define MAX 1e18
//#define MOD 998244353//1000000007

vector<int> dp(1000006);

//lCA

int n,k;

vector<int> G[100005];
vector<int> E[100005];
//vector<pair<int,int>> E(100005);
vector<int> rsp(100005,0);
vector<int> qtd(100005,0);
 
int alt[100005]; 
int pai[100005][20]; 

void dfs(int atu, int ant) {
    alt[atu] = alt[ant] + 1; 
    pai[atu][0] = ant; 
    for (int i=0; i<G[atu].size(); i++)  { 
        if (G[atu][i] != ant) {
            dfs(G[atu][i], atu); 
        }
    } 
} 
 
void pre(int n){ 
    for (int i=1; i<20; i++) { 
        for (int node = 1; node <= n; node++) { 
            if (pai[node][i-1] != -1) {
                pai[node][i] = pai[pai[node][i-1]][i-1]; 
            }   
        } 
    } 
} 
 
int lca(int u, int v) { 
    if (alt[v] < alt[u]) {
        swap(u, v); 
    }
 
    int diff = alt[v] - alt[u]; 
 
    for (int i=0; i<20; i++) {
        if ((diff>>i)&1) {
            v = pai[v][i]; 
        }           
    }
        
 
    if (u == v) {
        return u; 
    }
 
    for (int i=19; i>=0; i--) {
        if (pai[u][i] != pai[v][i]) { 
            u = pai[u][i]; 
            v = pai[v][i]; 
        } 
    }
        
 
    return pai[u][0]; 
} 

void conta(int u,int ant){
    for(int i=0;i<G[u].size();i++) {
        int tmp=G[u][i];
        //cout<<u<<" "<<ant<<" "<<i<<" "<<tmp<<"\n";
        if(tmp != ant){
            //cout<<"dif";
            conta(tmp, u);
            //cout<<"voltou";
            qtd[u] += qtd[tmp];
            rsp[E[u][i]]=qtd[tmp];
            //cout<<qtd[u]<<" "<<qtd[tmp]<<" "<<E[u][i];
        }
        //cout<<"\n";
    }
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


    cin>>n;
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
        E[u].push_back(i);
        E[v].push_back(i);
    }

    memset(pai,-1,sizeof(pai));

    //definir arvore
    alt[0]=0;
    dfs(1,0);
    pre(n); 

    //fazer o LCA...
    cin>>k;
    for(int i=0;i<k;i++){
        int u,v;
        cin>>u>>v;
        //P[i]=make_pair(u,v);

        int tmp=lca(u,v);
        //cout<<lca(u,v)<<"\n";
        qtd[u]++;
        qtd[v]++;
        qtd[tmp]-=2;
    }

    /*for(int i=1;i<=n;i++){
        cout<<qtd[i]<<" ";
    }
    cout<<"\n";*/

    //ver as rsps
    conta(1,0);

    /*for(int i=1;i<=n;i++){
        cout<<qtd[i]<<" ";
    }
    cout<<"\n";*/

    

    cout<<rsp[1];
    for(int i=2;i<=n-1;i++){
        cout<<" "<<rsp[i];
    }
    cout<<"\n";
    

    return 0;
}
