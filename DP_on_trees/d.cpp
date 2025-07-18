#include <bits/stdc++.h>

using namespace std;
#define int long long
#define N 100005
int n,mod;


//pair<int,int> c[N];
vector<int> G[N];
vector<int> f(N,1);
vector<int> pai(N);
bool vis[N];
bool vis1[N];

//dpeois pensar no mod soh no final..

void reroot(int s){

    queue<pair<int,int>> q; 

    vis1[s] = true;
    q.push(make_pair(s,0));

    while (!q.empty()) {
      
        int atu = q.front().first;
        int sub_pai =q.front().second;
        q.pop();

        f[atu]*=(sub_pai+1);
        f[atu]=f[atu]%mod;
        int tam=G[atu].size();
        vector<int> esq(tam+5,1);
        vector<int> dir(tam+5,1);
        
        int p=pai[atu];


        //ida
        for(int i=0;i<tam;i++){//o esq do ind i esta no i+1
            if(G[atu][i]!=p){
                esq[i+1]=esq[i]*(f[G[atu][i]]+1);
            }
            else{
                esq[i+1]=esq[i]*(sub_pai+1);
            }
            esq[i+1]=esq[i+1]%mod;
        }

        //volta
        for(int i=tam-1;i>=0;i--){//ind do dir eh nomrla
            if(G[atu][i]!=p){
                dir[i]=dir[i+1]*(f[G[atu][i]]+1);
            }
            else{
                dir[i]=dir[i+1]*(sub_pai+1);
            }
            dir[i]=dir[i]%mod;
        }


        /*for(int i=0;i<=tam;i++){
            cout<<esq[i]<<" ";
        }
        cout<<"\n";

        for(int i=0;i<tam;i++){
            cout<<dir[i]<<" ";
        }
        cout<<"\n";*/

        for (int i=0;i<tam;i++) {
            int x=G[atu][i];
            if (vis1[x]==false) {
                vis1[x] = true;
                int prox_sub=(esq[i]*dir[i+1])%mod;
                
                q.push(make_pair(x,prox_sub));
            }
        }
    }
}

void dfs(int v){
    vis[v]=true;
    int tam=G[v].size();
    for(int i=0;i<tam;i++){
        int u=G[v][i];
        if(!vis[u]){
            pai[u]=v;
            dfs(u);
            f[v]*=(f[u]+1);
            f[v]=f[v]%mod;
        }

    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>n>>mod;//m eh o mod...
    //po mas ae me parece facil?
    //tem uma arv com n vertices numrados de 1 a N
    //pintam cada vertice com branco ou preto
    //todos os vertices pretos podem chegar em todos os outros vertices pretos 
    //usando apenas vertices pretos(conexos)
    //Para cada vertice responder:
    //assumindo que o vertice v seja preto, encontre o numero de maneiras que
    //o vertices podem ser pintados, modulo m
    //parece mais um problema de matematica..

    //queremos contar p cada v o numero de subgrafos conexos que contem v
    //é facil se pensar cada vertice como raiz, usar rerooting
    //f(v) subarvores distintas enraizadas em v
    //f(v)=multiplicatorio de todo filho(1+f(u)) (dfs)

    //fazer mesma tecnica q eu fiz em C, n?

    //pendure (v,Tw) adc 1 ao valor da subarvore Tw
    //combine (v1,v2) soma g(v1) e g(v2)


    /*for(int i=0;i<n-1;i++){
        cin>>c[i].first>>c[i].second;
    }*/

    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(1);
    /*for(int i=1;i<=n;i++){
        cout<<f[i]<<"\n";
    }*/

    //prec(1);

    reroot(1);

    for(int i=1;i<=n;i++){
        cout<<f[i]<<"\n";
    }


    return 0;
}
