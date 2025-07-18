#include <bits/stdc++.h>

using namespace std;
#define int long long

#define N 100005
#define Mod 1000000007 
int n;


vector<int> cores(N);
vector<int> G[N];

int dp[N][5];

void dfs(int noh){//ir até as ponta, dp[u][1] qtd de formas q dá para separar do jeito q o enunciado pede a partir de u
    dp[noh][0]=1;
    dp[noh][1]=0;

    int tam=G[noh].size();
    for(int i=0;i<tam;i++){
        int u=G[noh][i];
        dfs(u);
        dp[noh][1]= (dp[noh][1]*dp[u][0])%Mod +(dp[noh][1]*dp[u][1])%Mod+ (dp[noh][0]*dp[u][1])%Mod;
        dp[noh][1]=dp[noh][1]%Mod;
        dp[noh][0]= (dp[noh][0]*dp[u][1])%Mod +(dp[noh][0]*dp[u][0])%Mod;
        dp[noh][0]=dp[noh][0]%Mod;
    }
    if(cores[noh]==1){
        dp[noh][1]=dp[noh][0];
        dp[noh][0]=0;
    }
    /*else{
        dp[noh][0]+=dp[noh][1];
    }*/

}


signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>n;

    for(int i=0;i<n-1;i++){//pensar como construir o grafo certinho...
        int tmp;
        cin>>tmp;
        G[tmp].push_back(i+1);
    }

    int p=0;
    for(int i=0;i<n;i++){
        cin>>cores[i];
        if(cores[i]==1){
            p++;
        }
    }

    //quer remover arestas..
    //por ser arv-> gera o k+1(?)
    //cada componente tem q ter um preto, dá para ver as subtree de cada vertice preto..
    //temos q separar os p noh preto, se tiver uma aresta q conecta dois, ela tem q serquebrada
    //n pode deixar um branco sozinho.., maximo p-1 para k
    //resolver do menor pro maior...multiplicar possibilidades
    //se um filho soh tem branco ele tem q ficar junto com o preto..
    //quantas formas eu consigo quebrar a sub em compoentnes com 1 preto
    //a forma da raiz eh a rsp(dp)
    //a componente da raiz eh branca e os outros componentes com 1 preto..

    dfs(0);

    cout<<dp[0][1]<<"\n";

    return 0;
}
