#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18

int n,q;//200005aaaa

//vector<int> t(200005);
vector<int> prox(200005);
vector<vector<int>> volta(200005);

vector<int> comp(200005);
vector<bool> vis1(200005,false);

vector<int> qual_ciclo(200005,-1);
vector<int> comp_ana(200005,false);
vector<bool> eh_ciclo(200005,false);
vector<int> tah_ciclo(200005,-1);
vector<int> tam_ciclo(200005,0);
vector<bool> vis2(200005,false);

vector<int> dist(200005,MAX);//dist de um dos membros do cicloa
vector<bool> vis3(200005,false);

vector<int> qual_arv(200005,-1);
vector<int> raiz(200005,-1);
vector<int> dist_arv(200005);//dist de um dos membros do cicloara
vector<bool> vis4(200005,false);


//jah vi antes...?
//calcular a distancia, ver se sao componentes diferentes
//como sei se eh um ciclo? negativo arv positov ciclo 0 ainda n passou?
//cilos difrente, arv p ciclo, arv..
//nao tem ciclo para arv(soh sai um de cada vertice, neh?)as

int alt[200005]; 
int pai[200005][30]; 
vector<int> faz_parte[200005];

//colocar os vetores que fazem parte de cada arvore separado
//mudar o pre de forma a soh ver os pai deles...

void dfs(int atu, int ant, int cnt) {
    faz_parte[cnt].push_back(atu);
    qual_arv[atu]=cnt;
    alt[atu] = alt[ant] + 1; 
    pai[atu][0] = ant; 
    for (int i=0; i<(int)volta[atu].size(); i++)  { 
        if (volta[atu][i] != ant && !eh_ciclo[volta[atu][i]]) {
            dfs(volta[atu][i], atu,cnt); 
        }
    } 
} 
 
void pre(int ind){ 
    for (int i=1; i<20; i++) { 
        for (int j=0; j <faz_parte[ind].size(); j++) { 
            int x=faz_parte[ind][j];
            // cout<<i<<" "<<node<<" "<<pai[node][i-1] <<"\n";
            if (pai[x][i-1] != -1) {
                //cout<<"entra";
                pai[x][i] = pai[pai[x][i-1]][i-1]; 
               // cout<<pai[node][i]<<"\n";
            }   
        } 
    } 
} 

void cal_dist(int ini){
    dist[ini]=0;
    int v=prox[ini];
    int ant=ini;
    vis3[ini]=true;
    while(v!=ini){
        dist[v]=dist[ant]+1;
        vis3[v]=true;
        ant=v;
        v=prox[ant];
    }
    tam_ciclo[qual_ciclo[ini]]=dist[ant]+1;
}

int componentes(int i, int c){
    vis1[i]=true;
    if(comp[prox[i]]==0 && !vis1[prox[i]]){//ainda não foi visitado
        c=componentes(prox[i],c);
    }
    else{//ela já foi vista por outra componente antes
        if(comp[prox[i]]!=0){
            comp[i]= comp[prox[i]];
            return comp[i];
        }
    }
    comp[i]=c;
    return c;

}

int ciclos(int i, int componente, int c, int tmp){//é ciclo? se sim, qual?aciclos(i,comp[i],ci,-1);
    vis2[i]=true;
    int x=-1;
    
    if(!vis2[prox[i]]){//ainda não foi visitado
        x=ciclos(prox[i],componente, c,-1);
    }
    else{//ela já foi vista por outra componente antes(achamos um ciclo...)
        eh_ciclo[i]=true;
        qual_ciclo[i]=c;
        comp_ana[componente]=true;
        tah_ciclo[componente]=i;
        if(prox[i]!=i){
            return prox[i];
        }
        return -1;
    }

    if(x==-1){
        eh_ciclo[i]=false;
        return -1;
    }
    else{

        eh_ciclo[i]=true;
        qual_ciclo[i]=c;
        if(i==x){
            return -1;
        }
        return x;
    }

}

int lca(int u, int v) { 
    //cout<<u<<" "<<v<<"\n";;
    if (alt[v] < alt[u]) {
        //cout<<"troca\n";
        swap(u, v); 
    }
 
    int diff = alt[v] - alt[u]; 
    //cout<<diff<<"\n";
 
    for (int i=0; i<20; i++) {
        if ((diff>>i)&1) {
            //cout<<"entra "<<i<<" ";45961
            v = pai[v][i]; 
            //cout<<v<<"\n";
        }           
    }
        
 
    if (u == v) {
        //cout<<"retorna\n";
        return u; 
    }
 
    for (int i=19; i>=0; i--) {
        if (pai[u][i] != pai[v][i]) { 
            //cout<<"comp "<<pai[u][i]<<" "<< pai[v][i]<<": ";43053
            u = pai[u][i]; 
            v = pai[v][i]; 
            //cout<<u<<" "<<v<<"\n";a
        } 
    }
        
    //cout<<"caiu"<<pai[u][0]<<"\n";
    return pai[u][0];
} 

void calc_arv(int ini, int narv){
    //dist dos vertices da arv em relacao a raiz, bfs..(?)
    queue<pair<int,int>> q;
    q.push({ini,0});
    dist_arv[ini] = 0;
    //vis4[ini]=true;
 
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        vis4[p.first] = true;
        qual_arv[p.first]=narv;

        for (int i=0;i<(int)volta[p.first].size();i++) {
            if (!vis4[i]&&!eh_ciclo[i]) {
                dist_arv[i] = dist_arv[p.first] + 1;
                q.push({i,p.first});
            }
        }
    }
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>n>>q;
    for(int i=1;i<=n;i++){
        //cin>>t[i];
        int tmp;
        cin>>tmp;
        prox[i]=tmp;
        volta[tmp].push_back(i);
    }

    //encontro os ciclos, e os marco como ciclos..val positivos do ini dele
    //faco ordem topologica? 
    
    //encontra diferentes componentes conexas
    int c=1,teste=1;
    for(int i=1;i<=n;i++){
        if(comp[i]==0){
            componentes(i,c);
            c++;
            teste++;
        }
    }

    /*cout<<"\ncomponente conexas: \n";
    for(int i=1;i<=n;i++){
        cout<<comp[i]<<" ";
    }
    cout<<"\n";*/

    //separar os ciclos, faz parte de um ciclo?
    //se sim, qual?
    int ci=1;
    for(int i=1;i<=n;i++){
        if(comp_ana[comp[i]]==false){//ainda n foi visitado
            ciclos(i,comp[i],ci,-1);
            ci++;
        }
    }

    /*cout<<"\nciclos: \n";
    for(int i=1;i<=n;i++){
        cout<<i<<" "<<eh_ciclo[i]<<" "<<qual_ciclo[i]<<"\n";
    }
    cout<<"\n";*/

    //dist dentro dos ciclos preciso mudar a
    //outro vis?
    //eh cilo e nao foi vis ainda?
    for(int i=1;i<=n;i++){
        if(eh_ciclo[i]&&vis3[i]==false){
            cal_dist(tah_ciclo[comp[i]]);
        }
        
        //cout<<"tam: "<<i<<" "<<tam_ciclo[i]<<"\n";
    }

    //cout<<"c"<<c<<" "<<ci<<" "<<teste<<"\n";

    //confere se passou em todas mesmo
    //imprime dist
   /* cout<<"\ndist: \n";
    for(int i=1;i<=n;i++){
        cout<<i<<" "<<dist[i]<<"\n";
    }
    cout<<"\n";*/


    //pre calcular os lca.. de cada arvores
   /* pot[0] = 1;
    for (int i=1; i<20; i++){
        pot[i] = pot[i-1]*2;
    }
    int val = 1,p=0;
    for (int i=1; i<n; i++){
        logn[i] = p-1;
        if (val==i){
            val*=2;
            logn[i] = p;
            p++;
        }
    }*/

   //cout<<"ehaqui embaixo\n a";
    //ptr=0;
    //memset(pai,-1,sizeof(pai));
    memset(pai,-1,sizeof(pai));
    int cnt=1;
    for(int i=1;i<=n;i++){
        if(eh_ciclo[i]&&volta[i].size()>1){//raizes da arvores

            qual_arv[i]=cnt;
            raiz[cnt]=i;
            alt[i]=0;
            
            dfs(i,0,cnt);
            pre(cnt);
            cnt++;
        }
    }

   // cout<<"encima msm \n\n\n asa";
    
   /*cout<<"\narv: \n";
    for(int i=1;i<=n;i++){
        cout<<i<<" "<<!eh_ciclo[i]<<" "<<qual_arv[i]<<" "<<alt[i]<<"\n";
    }
    cout<<"\n";

    cout<<"lca: \n";
    for(int i=1;i<=n;i++){
        for(int j=0;j<=20;j++){
            cout<<i<<" " <<j<<" "<<pai[i][j]<<"\n";
        }
        
    }
    cout<<"\n";

    cout<<lca(4,2)<<"\n";*/
   


    //respostas para as queries..
    //cout<<"\nqueries: \n";
    for(int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        //cout<<a<<" "<<b<<" ";
        if(a==b){
            cout<<"0\n";
        }
        else{
            if(comp[a]==comp[b]){//sao da msm componente
                if(eh_ciclo[a]&&eh_ciclo[b]){
                    if(qual_ciclo[a]!=qual_ciclo[b]){//dif ciclos
                        cout<<-1<<"\n";
                    }
                    else{//msm ciclo
                        //cout<<"aba: "<<tah_ciclo[comp[a]]<<"\n";
                        int x=qual_ciclo[a];
                        if(tah_ciclo[comp[a]]==a){
                            cout<<dist[b]<<"\n";
                        }
                        else{
                            if(tah_ciclo[comp[a]]==b){
                                cout<<tam_ciclo[x]-dist[a]<<"\n";
                            }
                            else{
                                if(dist[a]>dist[b]){
                                    cout<<tam_ciclo[x]-dist[a]+dist[b]<<"\n";
                                }
                                else{
                                    cout<<dist[b]-dist[a]<<"\n";
                                }
                            }
                        }
                    }
                }
                else{
                    if(eh_ciclo[a]&&!eh_ciclo[b]){//ciclo p arva
                        cout<<-1<<"\n";
                    }
                    else{
                        if(!eh_ciclo[a]&&eh_ciclo[b]){//arv p/ ciclo
                            //pensar nisso aqui?
                            int dist_arv_ciclo=alt[a]-1;
                            int raiz_da_arv=raiz[qual_arv[a]];
                            //cout<<raiz_da_arv<<" "<<dist[b]<<" "<<dist[raiz_da_arv]<<" "<<tah_ciclo[comp[b]]<<"\n";
                            if(raiz_da_arv==b){
                                //cout<<"a";
                                cout<<dist_arv_ciclo<<"\n";
                            }
                            else{
                                if(tah_ciclo[comp[a]]==b){
                                    //cout<<"b";
                                    cout<<tam_ciclo[qual_ciclo[b]]-dist[raiz_da_arv]+dist_arv_ciclo<<"\n";
                                }
                                else{
                                    if(dist[b]>dist[raiz_da_arv]){
                                        //cout<<"c";
                                        cout<<-1+alt[a]+dist[b]-dist[raiz_da_arv]<<"\n";
                                    }
                                    else{
                                        //cout<<"d"<<alt[a]<<" "<<dist[b]<<" "<<tam_ciclo[qual_ciclo[b]]<<" "<<dist[raiz_da_arv]<<" ";
                                       // cout<<comp[b]<<" "<<tah_ciclo[comp[b]];
                                        //cout<<"\n";
                                        cout<<alt[a]+dist[b]+tam_ciclo[qual_ciclo[b]]-dist[raiz_da_arv]-1<<"\n";
                                    }
                                }
                            }
    
                        }
                        else{//ambos em arv(tem q ser da mesma linha..)
                            if(raiz[qual_arv[a]]!=raiz[qual_arv[b]]){//dif arv
                                cout<<"-1\n";
                            }
                            else{
                                if(lca(a,b)!=b){
                                    cout<<"-1\n";
                                }
                                else{
                                    //cout<<"e";
                                    cout<<alt[a]-alt[b]<<"\n";
                                }
                            }
                        }
                    }
                }
            }
            else{//componentes diferentes..
                cout<<-1<<"\n";
            }
        }
    }

    return 0;
}


