#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18
//#define MOD 998244353//1000000007//63018038201//63018038201

#define MOD 998244353

int n,m,s,t;

//ruas
vector<pair<int,int>> R(200000);
vector<int> P(200000);

//grafo
vector<pair<int,int>> E[200000];
vector<int> visE[200000];
vector<bool> visV(200000,false);

//grafo invetido
vector<pair<int,int>> EI[200000];
vector<int> visEI[200000];
vector<bool> visVi(200000,false);

//min do s para outro
vector<int> mins(200000,MAX);

//min de chagar pro t vindo dos outros
vector<int> mint(200000,MAX);



//qts caminhos chegam vindo de s
vector<int> qtds(200000);

//qts caminhos chegam em t vindo dele
vector<int> qtdt(200000);

//grafo de menores caminhos
vector<pair<int,int>> Ra(200000);
vector<int> Pa(200000);

vector<pair<int,int>> Dag[200000];
//vector<bool> visd(200000,false);
vector<int> visd[200000];
vector<int> minds(200000,MAX);


vector<pair<int,int>> Dagi[200000];
//vector<bool> visdi(200000,false);
vector<int> visdi[200000];
vector<int> mindt(200000,MAX);




void menor_de_s(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
    pq.push(make_pair(0, s));

    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();

        for(int i=0; i<E[u].size();i++){
            int v=E[u][i].first;
            int peso=E[u][i].second;
            
            /*if(mins[v]==mins[u]+peso && visE[u][i]==0){
                qtds[v]=(qtds[v]%MOD+qtds[u]%MOD)%MOD;
            }*/
            if (mins[v]> mins[u]+peso && visE[u][i]==0) {
                //qtds[v]=(qtds[v]%MOD+qtds[u]%MOD)%MOD;
                //qtds[v]=qtds[u];
                mins[v]= mins[u]+peso;
                pq.push(make_pair(mins[v], v));
            }

            visE[u][i]=1;
        }
    }

}

void menor_p_t(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
    pq.push(make_pair(0, t));

    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();

        for(int i=0; i<EI[u].size();i++){
            int v=EI[u][i].first;
            int peto=EI[u][i].second;
            
            /*if(mint[v]==mint[u]+peto && visEI[u][i]==0){
                qtdt[v]=(qtdt[v]%MOD+qtdt[u]%MOD)%MOD;
            }*/
            if (mint[v]> mint[u]+peto && visEI[u][i]==0) {
                //qtdt[v]=qtdt[u];
                mint[v]= mint[u]+peto;
                pq.push(make_pair(mint[v], v));
            }

            visEI[u][i]=1;
        }
    }

}



void conta_de_s(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
    pq.push(make_pair(0, s));
    qtds[s]=1;
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();

        for(int i=0; i<Dag[u].size();i++){
            int v=Dag[u][i].first;
            int peso=Dag[u][i].second;
            qtds[v]=(qtds[v]%MOD+qtds[u]%MOD)%MOD;
            if (minds[v]> minds[u]+peso && visd[u][i]==0) {
                minds[v]= minds[u]+peso;
                pq.push(make_pair(minds[v], v));
            }

            visd[u][i]=1;
        }
    }

}

void conta_p_t(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
    qtdt[t]=1;
    pq.push(make_pair(0, t));

    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();

        for(int i=0; i<Dagi[u].size();i++){
            int v=Dagi[u][i].first;
            int peseo=Dagi[u][i].second;
            qtdt[v]=(qtdt[v]%MOD+qtdt[u]%MOD)%MOD;
            if (mindt[v]> mindt[u]+peseo && visdi[u][i]==0) {
                mindt[v]= mindt[u]+peseo;
                pq.push(make_pair(mindt[v], v));
            }

            visdi[u][i]=1;
        }
    }

}


signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

 
    cin>>n>>m>>s>>t;

    for(int i=1;i<=m;i++){
        int a,b,w;
        cin>>a>>b>>w;
        R[i]=make_pair(a,b);
        P[i]=w;
        E[a].push_back(make_pair(b,w));
        EI[b].push_back(make_pair(a,w));
        visE[a].push_back(0);
        visEI[b].push_back(0);
    }

    //dijk ida e volta, testar mod diferentes..
    //ida
    mins[s]=0;
    menor_de_s();

    //volta
    mint[t]=0;
    menor_p_t();

    minds[s]=0;
    mindt[t]=0;


    int contador=1;
    //montar as só com o cam min
    for(int i=1;i<=m;i++){
        int u=R[i].first;
        int v=R[i].second;
        int p=P[i];

        //cout<<u<<" "<<v<<" "<<p<<"\n";

        int x;
        if(mins[u]+mint[v]+p == mins[t]){
            Ra[contador]=make_pair(u,v);
            Pa[contador]=p;
            Dag[u].push_back(make_pair(v,p));
            Dagi[v].push_back(make_pair(u,p));
            contador++;
            visd[u].push_back(0);
            visdi[v].push_back(0);
        }
    }
    //contador--;


    //contar a qtd de caminhos...
    
    conta_de_s();
    conta_p_t();



    //analisar com as respostas
    for(int i=1;i<=m;i++){
        int u=R[i].first;
        int v=R[i].second;
        int p=P[i];

        int x;
        if(mins[u]+mint[v]+p > mins[t]){
            x=mins[u]+mint[v]+p-mins[t]+1;
            if(p-x>=1){
                cout<<"CAN "<<x<<"\n";
            }
            else{
                cout<<"NO\n";
            }
        }
        else{//=, pois nao pode ser <...
            //verificar se esta em tds os caminho min ou n
            //qtds[v]=(qtds[v]%MOD+qtds[u]%MOD)%MOD; //...está certo?
            if(((qtds[u]%MOD)*(qtdt[v]%MOD))%MOD==qtds[t]){
                cout<<"YES\n";
            }
            else{
                if(p>1){
                    cout<<"CAN 1\n";
                }
                else{
                    cout<<"NO\n";
                }
            }
        }
    }

    return 0;
}
