#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18
//#define MOD 998244353//1000000007

#define MOD 1000000007
//vector<int> dp(1000006,0);
//vector<int> aux(1000006,0);



//vector<int> qual_scc(100006);//0 se for parte, maior q zero se for, guarda o val dele
vector<int> vis(100006,-1);
vector<int> low(100006,-1);
vector<bool> tah_na_pilha(100006,false);
stack<int> st;
int qtd_scc;
int tempo;

vector<bool> vis2(100006, false);
vector<int> low2(100006,-1);
vector<int> disc2(100006,-1);

vector<pair<int,int>> rsp ;

int n,m;//10⁵ e 2.10⁵
vector<vector<int>> G(100005);

vector<bool> vis3(100006, false);

//preciso guardar se a ida e a volta nao foram visitas ainda
vector<pair<int,int>> GI[100005];
vector<int> jah_foi(200006,-1);


int flag=0;

int ponte(int u,int pai){

    vis2[u] = true;

    tempo++;

    disc2[u] = low2[u] = tempo;

    for (int i = 0; i< G[u].size(); i++){
        int v = G[u][i]; 
          
        if(v!=pai){
            if(vis2[v]){
                low2[u]  = min(low2[u], disc2[v]);
            }
            else{
                pai = u;
                ponte(v, pai);
                
        
                low2[u]  = min(low2[u], low2[v]);
                if (low2[v] > disc2[u]){//encontrou a ponte
                    cout<<"IMPOSSIBLE\n";
                    flag=1;
                    return 0;
                }      
            }
        }
            
        
    }

    return 1;
}

void acha_scc(int u){ 
    tempo++;
    vis[u] = low[u] = tempo;
    st.push(u);
    tah_na_pilha[u] = true;
 

    for(int i=0;i<G[u].size();i++){
        //cout<<"aqui"<<i<<" "<<G[u].size()<<"\n";

        int v=G[u][i];
        //cout<<"vert: "<<u<<" "<<v<<"\n";
        if (vis[v] == -1) {
            //cout<<"a"<<low[u]<<" "<<low[v]<<" "<<vis[u]<<" "<<vis[v]<<"\n";
            acha_scc(v);
            low[u] = min(low[u], low[v]);
        }
        else{
            //cout<<"c\n";
            if(tah_na_pilha[v] == true){
                //cout<<"b"<<low[u]<<" "<<low[v]<<" "<<vis[u]<<" "<<vis[v]<<"\n";
                low[u] = min(low[u], vis[v]);
            }
        } 
    }

    int w=0;
    if (low[u] == vis[u]) {
        //cout<<"entrou: "<<u<<" "<<low[u]<<"\n";
        while (st.top() != u) {
            w = st.top();
            tah_na_pilha[w] = false;
            //qual_scc[w]=qtd_scc;
            //v_especial[qtd_scc].push_back(w);
            st.pop();
        }
        w = st.top();
        tah_na_pilha[w] = false;
        //qual_scc[w]=qtd_scc;
        //v_especial[qtd_scc].push_back(w);
        st.pop();

        qtd_scc++;
    }
}

void dfs(int u,int pai){
    vis3[u]=true;
    for(int i=0;i<GI[u].size();i++){
        int v=GI[u][i].first;

        if(!vis3[v]){
            rsp.push_back(make_pair(u,v));
            jah_foi[GI[u][i].second]=1;
            dfs(v,u);
            //rsp.push_back(make_pair(u,v));
        }
        else{
            if(v!=pai && jah_foi[GI[u][i].second]==-1){
                rsp.push_back(make_pair(u,v));
                jah_foi[GI[u][i].second]=1;
            }
        }
    }
    
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //nao direcionado, é para gerar um grafo conectado, igual o da ideai feita em aula?
    //dfs percorre deve achar um 
    //precisa ter um ciclo.. dito isso precisamos achar esse ciclo para dar o sinal dessas arestas
    //para ser scc precisa que seja um soh e n tenha com grau 1 e nao tenha ponte?

    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);

        GI[a].push_back(make_pair(b,i));
        GI[b].push_back(make_pair(a,i));
    }

    //ver se ele não é impossible e depois montar o grafo? dá para fazer junto?
    for(int i=1;i<=n;i++){
        if(G[i].size()<=1){
            cout<<"IMPOSSIBLE\n";
            return 0;
        }
    }
    
    //vê se tem mais de uma componente conexa
    qtd_scc=0,tempo=0;
    for (int i = 1; i <=n; i++){
        if (vis[i]==-1){
            acha_scc(i);
        }
    }
    if(qtd_scc>1){
        cout<<"IMPOSSIBLE\n";
        return 0;
    }

    //nao pode ser grafo do tipo se retira um cria duas variáveis, vai ter q usar o tarjan
    //mostrar pontes tem que usar o tarjan modificado?
    int pai = -1,qtd_scc=0,tempo=0;
    for (int i = 0; i < n; i++){
        if (vis2[i] == false){
            if(ponte(i, pai)==0 || flag==1){
                return 0;
            }
        }
            
    }
        
    //agr sim sabemos que tem uma scc
    //para encontrar ela.. dfs, n? posso usar no tarjan com ponte?
    //arv vai para baixo, outros vai subindo e achamos o scc, n?
    dfs(1,-1);

    for(int i=0;i<m;i++){
        cout<<rsp[i].first<<" "<<rsp[i].second<<"\n";
    }

    return 0;
}
