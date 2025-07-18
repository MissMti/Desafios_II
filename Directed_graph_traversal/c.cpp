#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18

int n,m,s;//10^6;

vector<pair<int,int>> G[1000006];
vector<pair<int,int>> NG[1000006];

vector<int> qual_scc(1000006);//0 se for parte, maior q zero se for, guarda o val dele
vector<int> vis(1000006,-1);
vector<int> low(1000006,-1);
vector<bool> tah_na_pilha(1000006,false);
stack<int> st;

vector<int> peso(1000006);

vector<int> v_especial[1000006];

vector<int> dist(1000006,-1);
vector<bool> vis2(1000006);
stack<int> S;

int qtd_scc;
int tempo;


//o n é alto.. preciso achar um jeito de fazer a conta antes 
    //dfs provavelmente para ver até onde ele consegue chegar/passar.

//ciclo-> indica que posso ir todas as vezes(consigo tirar o máximo proveito disso)
//isso dá o valor total do ciclo...
//caso contrário, teriamos um caso de que(conseguiria passar apenas uma vez)

//dp:
// para o cálculo inicial de quantos eu consigo tirar de cada passagem?
//tem aluma lógica?

//retirando os ciclos, consigo ter uma ideia de como se fosse um aciclico, ai aplico?
//ideia promissora..

//preciso da formula matematica...
//quanto prever quantas sessoes acontecem...

void acha_scc(int u){ 
    tempo++;
    vis[u] = low[u] = tempo;
    st.push(u);
    tah_na_pilha[u] = true;
 

    for(int i=0;i<G[u].size();i++){
        //cout<<"aqui"<<i<<" "<<G[u].size()<<"\n";

        int v=G[u][i].first;
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
            qual_scc[w]=qtd_scc;
            v_especial[qtd_scc].push_back(w);
            st.pop();
        }
        w = st.top();
        tah_na_pilha[w] = false;
        qual_scc[w]=qtd_scc;
        v_especial[qtd_scc].push_back(w);
        st.pop();

        qtd_scc++;
    }
}

int cogumelos(int n){//logica matematica..
    /*
    n=i*(i+1)/2
    i² +i-2n=0 (bhaskara)
    não pode ser neg
    */
    int x=(-1+sqrt(1+8*n))/2;//quando o -1-2-3.. supera o n :P;
    return (x+1)*n-x*(x+1)*(x+2)/6;//n+(n-1)+(n-1-2)+...até acabar
}
 

void topo(int v)  {   
    vis2[v] = true;  
    
    for (int i = 0; i<NG[v].size(); i++) {  
        if (!vis2[NG[v][i].first])  {
            topo(NG[v][i].first); 
        }
    }  
    
    S.push(v);  
}

int dfs(int ini){  

    for (int i = 1; i < qtd_scc; i++)  {
        if (vis2[i] == false)  {
            topo(i);
        } 
    }
         
    dist[ini] = peso[ini];   
    while (S.empty() == false) {  
        int u = S.top();  
        S.pop();  
        if (dist[u] != -1) {  
            for (int i = 0; i<NG[u].size();i++){  
                if (dist[NG[u][i].first]<dist[u]+NG[u][i].second+peso[NG[u][i].first])  {
                    dist[NG[u][i].first]=dist[u]+NG[u][i].second+peso[NG[u][i].first]; 
                }
            } 
        }  
    }  
    
    int M=0;
    for (int i = 1; i < qtd_scc; i++) {
        if(dist[i]>M){
            M=dist[i];
        }
    }
    return M;
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n>>m;

    for(int i=0;i<m;i++){//m pode ser zero!! atenção ao possível caso err...
        int x,y,w;
        cin>>x>>y>>w;
        G[x].push_back(make_pair(y,w));//tah bom esse esquema?
        //I[y].push_back(make_pair(x,w));
    }
    cin>>s;

    

    //encontra os ciclos/scc
    qtd_scc=1,tempo=0;
    for (int i = 1; i <=n; i++){
        if (vis[i]==-1){
            acha_scc(i);
        }
    }

    /*cout<<"\nqtd: "<<qtd_scc-1<<"\n";
    cout<<"\nscc\n";
    for(int i=1;i<qtd_scc;i++){
        for(int j=0;j<v_especial[i].size();j++){
            cout<<v_especial[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";*/

    /*for(int i=1;i<10;i++){
        cout<<cogumelos(i)<<"\n";
    }
    cout<<"\n";*/

    

    //novo grafo (NG)...
    //individual copia de G, multiplo faz diferente..
    for(int i=1;i<qtd_scc;i++){
        if(v_especial[i].size()==1){//individual
            //cout<<"sing\n";
            int u=v_especial[i][0];
            for(int j=0;j<G[u].size();j++){//analisa as arestas
                if(qual_scc[G[u][j].first]==i){
                    peso[i]+=cogumelos(G[u][j].second);
                }
                else{
                    NG[i].push_back(make_pair(qual_scc[G[u][j].first],G[u][j].second));
                }
            }
        }
        else{//scc com mais
            //cout<<"mult\n";
            for(int k=0;k<v_especial[i].size();k++){
                int u=v_especial[i][k];
                for(int j=0;j<G[u].size();j++){//analisa as arestas
                    if(qual_scc[G[u][j].first]==i){
                        peso[i]+=cogumelos(G[u][j].second);
                    }
                    else{
                        NG[i].push_back(make_pair(qual_scc[G[u][j].first],G[u][j].second));
                    }
                    
                }
            }
            
        }
        
    }

    /*cout<<"NG: \n";
    for(int i=1;i<qtd_scc;i++){
        cout<<i<<": ";
        for(int j=0;j<NG[i].size();j++){
            cout<<NG[i][j].first<<" "<<NG[i][j].second;
        }
        cout<<"\n";
    }
    cout<<"\n";

    cout<<"s: "<<qual_scc[s]<<"\n";*/


    /*for(int i=1;i<qtd_scc;i++){
        for(int j=0;j<v_especial[i].size();j++){
            int v=v_especial[i][j];
            if(G[v].size()>1){//sai mais q um..
                for(int k=0;k<G[v].size();k++){
                    if(qual_scc[G[v][k].first]==qual_scc[v]){//considero na mat
                        peso[qtd_scc]+=cogumelos(G[v][k].second);
                    }
                    else{//junto aos q saem dele no vetor especial
                        NG[i].push_back(make_pair(G[v][k].first,G[v][k].second));
                    }
                }
            }
            if(I[v].size()>1){//entra mais queum..
                for(int k=0;k<I[v].size();k++){
                    if(qual_scc[I[v][k].first]!=qual_scc[v]){
                        NG[I[v][k].first].push_back(make_pair(i,I[v][k].second));
                    }
                }
            }
        }        
    }*/


    //rsp

    cout<<dfs(qual_scc[s])<<"\n";

    return 0;
}
