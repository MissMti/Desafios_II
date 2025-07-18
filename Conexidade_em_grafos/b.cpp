#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18

int t;//30
int n,m;//10000 20000
int rsp;

vector<pair<int,int>> G[20004];//vou ter q ir limpando..
vector<int> NG[20004];//vou ter q ir limpando..
vector<int> eh_ponte(20004,-1);
vector<vector<int>> entrou(35, vector<int> (20004, -1));

vector<vector<int>> vis(35, vector<int> (20004, -1));
vector<vector<int>> vis2(35, vector<int> (20004, -1));
vector<vector<int>> comp(35, vector<int> (20004, -1));
vector<vector<int>> low(35, vector<int> (20004, -1));
vector<vector<int>> disc(35, vector<int> (20004, -1));
vector<vector<bool>> tah_na_pilha(35, vector<bool> (20004, false));
vector<stack<int>> st(35);
vector<vector<int>> qual_scc(35, vector<int> (20004, -1));
int tempo,qtd_scc;

vector<int> v_especial[20004];




/*void dfsponte(int loops,int noh,int pai){
    low[loops][noh]=vis2[loops][noh]=++tempo;

    int tam=G[noh].size();

    for(int i=0;i<tam;i++){
        if(G[noh][i].first==pai){
            continue;
        }
        if(vis2[loops][G[noh][i].first]==-1){
            dfsponte(loops,G[noh][i].first,noh);
            if(vis2[loops][noh]<low[loops][G[noh][i].first]){
                eh_ponte[G[noh][i].second]=1;
            }
            low[loops][noh]=min(low[loops][noh],low[loops][G[noh][i].first]);
        }
        else{
            low[loops][noh]=min(low[loops][noh],vis2[loops][G[noh][i].first]);
        }
    }
}*/

void dfspontes(int loops,int u,int pai){

    vis2[loops][u] = 1;

    tempo++;

    disc[loops][u] = low[loops][u] = tempo;
    

    for (int i = 0; i< G[u].size(); i++){
        int v = G[u][i].first; 
        
          
        if(entrou[loops][G[u][i].second]==-1){
            entrou[loops][G[u][i].second]=1;
            if(vis2[loops][v]!=-1){
                low[loops][u]  = min(low[loops][u], disc[loops][v]);
            }
            else{
                pai = u;
                dfspontes(loops,v, pai);
                
        
                low[loops][u]  = min(low[loops][u], low[loops][v]);
                if (low[loops][v] > disc[loops][u]){//encontrou a ponte
                    eh_ponte[G[u][i].second]=1;
                }      
            }
        }
            
        
    }

}


void acha_pontes(int loops){
    tempo=0;
    for(int u=0;u<n;u++){
        if(vis2[loops][u]==-1){
           // cout<<"entra "<<u<<"\n";
            dfspontes(loops,u,u);
        }
    }
}

void acha_arv(int loops,int u){
    qual_scc[loops][u] = qtd_scc;
    v_especial[qtd_scc].push_back(u); 
    vis[loops][u] = 1;
    int tam=G[u].size();
    for(int i=0;i<tam;i++){
        if(eh_ponte[G[u][i].second]==-1){
            int prox=G[u][i].first;
            if(vis[loops][prox]==-1){
                acha_arv(loops,prox);
            }
        }
    }  
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>t;
    for(int loops=1;loops<=t;loops++){
        
        qtd_scc=1;
        tempo=0;

        cin>>n>>m;//limpar e ler
        for(int i=0;i<=20002;i++){
            G[i].clear();//ou erase begin to end(?)
            NG[i].clear();//ou erase begin to end(?)
            eh_ponte[i]=-1;
            v_especial[i].clear();
        }

        for(int i=0;i<m;i++){
            int u,v;
            cin>>u>>v;
            G[u].push_back({v,i});
            G[v].push_back({u,i});
        }

        acha_pontes(loops);

        /*cout<<"pontes:\n";
        for(int i=0;i<m;i++){
            cout<<i<<" "<<eh_ponte[i]<<"\n";
        }*/

        for(int i=0;i<n;i++){
            if(vis[loops][i]==-1){
                acha_arv(loops,i);
                qtd_scc++;
            }
        }

        /*cout<<"qtd: "<<qtd_scc-1<<"\n";
        for(int i=0;i<n;i++){
        /cout<<i<<" "<<qual_scc[loops][i]<<"\n";
        }*/

        for(int i=1;i<qtd_scc;i++){
            for(int k=0;k<v_especial[i].size();k++){
                int u=v_especial[i][k];
                for(int j=0;j<G[u].size();j++){//analisa as arestas
                    if(qual_scc[loops][G[u][j].first]!=i){
                        NG[i].push_back(qual_scc[loops][G[u][j].first]);
                    }
                }
            }   
        }

       /* cout<<"NG:\n";
        for(int i=1;i<qtd_scc;i++){
            for(int j=0;j<NG[i].size();j++){
                cout<<i<<" "<<NG[i][j]<<"\n";
            }
        }*/

        //contar quantas folhas...
        rsp=0;
        for(int i=1;i<qtd_scc;i++){
            if(NG[i].size()==1){
                rsp++;
            }
        }


        rsp=(rsp+1)/2;
        cout<<"Case "<<loops<<": "<<rsp<<"\n";
        rsp=0;

    }
    return 0;
}



