#include <bits/stdc++.h>

using namespace std;

#define int long long
//#define MAX 1e18
//#define MOD 998244353//1000000007

//vector<vector<int>> dp(550,vector<int>(550,MAX));


vector<int> V(100005);
vector<vector<int>> E(100005);
vector<bool> vis(100005,false);
//vector<vector<int>> E(100005,vector<int>(100005));

int rsp,m;


//considerando as vezes seguidas se chegar numa folha temos +1 p/rsp :D
void dfs(int at,int soma){
    vis[at]=true;
    if(E[at].size()==1 && at!=1){
        rsp++;
    }
    else{
        for(int j=0;j<E[at].size();j++){
            int i=E[at][j];
            if(vis[i]==false){
                if(V[i]==0){
                    dfs(i,0);
                }
                else{
                    if(soma<m){
                        dfs(i,soma+V[i]);
                    }
                }
            }
        }
    }
    
}



signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;//vertices
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        cin>>V[i];//1 tem gato
    }

    //é uma arvore garantida,soh adc normal
    //cria estrutura
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        E[a].push_back(b);
        E[b].push_back(a);
    }

    //dfs, ideia discutida em aula
    rsp=0;
    dfs(1,V[1]);


    //imprime
    cout<<rsp<<"\n";
    

    return 0;
}

//oq a torna uma folha? apenas conecta 1 e nao é a casa

