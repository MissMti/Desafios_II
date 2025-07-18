#include <bits/stdc++.h>

using namespace std;
#define int long long
#define N 100005
int n;



vector<int> p(N+5);
vector<pair<int,int>> G[N+5];
bool vis[N];
bool vis1[N];
vector<pair<int,int>> info(N+5);//peso(habitantes) e total(até ai)
vector<int> pai(N+5);
vector<int> dist_pai(N+5);

pair<int,int> dfs(int x){
    vis[x]=true;
    int tam=G[x].size();
    for(int i=0;i<tam;i++){
        int v=G[x][i].first;
        
        if(vis[v]==false){
            pai[v]=x;
            dist_pai[v]=G[x][i].second;
            pair<int,int> tmp=dfs(v);
            info[x].first+=tmp.first;
            info[x].second+=tmp.first*G[x][i].second+tmp.second;
        }
    }
    info[x].first+=p[x];
    //pair<int,int> tmp;
    return info[x];
}

vector<int> bfs(int s)  {
    vector<int> res;

    queue<int> q; 

    vis1[s] = true;
    q.push(s);

    while (!q.empty()) {
      
        int atu = q.front();
        q.pop();
        res.push_back(atu);
        //tratar aqui
        int tmp=pai[atu];
        //preciso fazer as cotnas
        if(atu!=1){
            info[atu].second=info[tmp].second-info[atu].first*dist_pai[atu]+(info[tmp].first-info[atu].first)*dist_pai[atu];
            info[atu].first=info[tmp].first;
        }
        
        int tam=G[atu].size();
        for (int i=0;i<tam;i++) {
            int x=G[atu][i].first;
            if (vis1[x]==false) {
                vis1[x] = true;
                q.push(x);
            }
        }
    }

    return res;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //eh o rerooting lah?

    freopen("house.in", "r", stdin);
    freopen("house.out", "w", stdout);

    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>p[i];//populaçao
    }
    for(int i=0;i<n-1;i++){
        int a,b,l;
        cin>>a>>b>>l;//a b e largura
        G[a].push_back(make_pair(b,l));
        G[b].push_back(make_pair(a,l));
    }

    //dfs de cima para baixo
    //pai[1]=-1;
    dfs(1);

    /*for(int i=1;i<=n;i++){
        cout<<i<<" "<<info[i].first<<" "<<info[i].second<<"\n";
    }
    for(int i=1;i<=n;i++){
        cout<<i<<" "<<pai[i]<<" "<<dist_pai[i]<<"\n";
    }*/
    //deu certin ;-;

    //procurr pelos pais...

    //baixo pra cima(ver se os calculos funcionam k) (ir de cima para baixo)
    //virar só o "sentido" do de cima
    bfs(1);
    /*for(int i=1;i<=n;i++){
        cout<<i<<" "<<info[i].first<<" "<<info[i].second<<"\n";
    }*/
    /*for(auto i:ans) {
        cout<<i<<" ";
    }*/

    int indice=1;
    int rsp=info[1].second;
    for(int i=2;i<=n;i++){
        if(rsp>info[i].second){
            indice=i;
            rsp=info[i].second;
        }
    }

    cout<<indice<<" "<<rsp<<"\n";

    return 0;
}
