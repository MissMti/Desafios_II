#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18

int n;
//vector<int> f(250);
vector<int> G(250);

vector<vector<int>> volta(200005);

vector<int> comp(205);
vector<bool> vis1(205,false);

vector<int> qual_ciclo(205,-1);
vector<int> comp_ana(205,false);
vector<bool> eh_ciclo(205,false);
vector<int> tah_ciclo(205,-1);
vector<int> tam_ciclo(205,0);
vector<bool> vis2(205,false);

vector<int> dist(205,MAX);//dist de um dos membros do cicloa
vector<bool> vis3(205,false);

vector<int> qual_arv(205,-1);
vector<int> raiz(205,-1);
vector<int> dist_arv(205);//dist de um dos membros do cicloara
vector<bool> vis4(205,false);

int alt[200005]; 
int alt_max;

vector<int> tams_de_ciclo;
//int pai[200005][30]; 
//vector<int> faz_parte[200005];


void dfs(int atu, int ant, int cnt) {
    //faz_parte[cnt].push_back(atu);
    qual_arv[atu]=cnt;
    alt[atu] = alt[ant] + 1; 
    if(alt[atu]>alt_max){
        alt_max=alt[atu];
    }
    //pai[atu][0] = ant; 
    for (int i=0; i<(int)volta[atu].size(); i++)  { 
        if (volta[atu][i] != ant && !eh_ciclo[volta[atu][i]]) {
            dfs(volta[atu][i], atu,cnt); 
        }
    } 
} 

void cal_dist(int ini){
    dist[ini]=0;
    int v=G[ini];
    int ant=ini;
    vis3[ini]=true;
    while(v!=ini){
        dist[v]=dist[ant]+1;
        vis3[v]=true;
        ant=v;
        v=G[ant];
    }
    tam_ciclo[qual_ciclo[ini]]=dist[ant]+1;
}

int componentes(int i, int c){
    vis1[i]=true;
    if(comp[G[i]]==0 && !vis1[G[i]]){//ainda não foi visitado
        c=componentes(G[i],c);
    }
    else{//ela já foi vista por outra componente antes
        if(comp[G[i]]!=0){
            comp[i]= comp[G[i]];
            return comp[i];
        }
    }
    comp[i]=c;
    return c;

}

int ciclos(int i, int componente, int c, int tmp){//é ciclo? se sim, qual?aciclos(i,comp[i],ci,-1);
    vis2[i]=true;
    int x=-1;
    
    if(!vis2[G[i]]){//ainda não foi visitado
        x=ciclos(G[i],componente, c,-1);
    }
    else{//ela já foi vista por outra componente antes(achamos um ciclo...)
        eh_ciclo[i]=true;
        qual_ciclo[i]=c;
        comp_ana[componente]=true;
        tah_ciclo[componente]=i;
        if(G[i]!=i){
            return G[i];
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

int mult( ){
    int tam=tams_de_ciclo.size();
    sort(tams_de_ciclo.begin(),tams_de_ciclo.begin()+tam);

    /*cout<<"tam ciclos: ";
    for(int i=0;i<tam;i++){
        cout<<tams_de_ciclo[i]<<" ";
    }
    cout<<"\n";*/
 
    int rsp = 1;

    int fat=2;
 
    while (fat <= tams_de_ciclo[tam-1]){
        vector<int> ind;
        for (int j=0; j<tam; j++){
            if (tams_de_ciclo[j]%fat == 0){
                ind.push_back(j);
            }
                
        }

            
        if (ind.size() >= 2) {
            for (int j=0; j<ind.size(); j++){
                tams_de_ciclo[ind[j]] = tams_de_ciclo[ind[j]]/fat;
            }
            rsp = rsp * fat;
        }
        else{
            fat++;
        }
            
    }
 
    for (int i=0; i<tam; i++){
        rsp = rsp*tams_de_ciclo[i];
    }

    //cout<<rsp<<" "<<alt_max<<"\n";

    int tmp=1;
    while(rsp*tmp<alt_max){
        tmp++;
    }
    rsp=rsp*tmp;
 
    return rsp;
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //idempotent é tipo identidade?-> é ir até ser ? n exatamente...
    //grafo? função é a aresta?

    //teste3: eles voltam para sim mesmos, se tornam ind.. isso parece simples..
    //depois fica certo p/ sempre? NAO PENSAMENTO ERRADO DÀ ERRO!!! vai ter ser mult msm...

    //mas e os outros o que estão fora dos ciclos? tem q ser levados até um ciclo
    //mas como vejo isso? teste 2 não ajuda muito...
    //eh soh contar o tam até o local? a->b->c->c, b e c ind, a n, a->c b->c c->c, agr é..

    //isso é fácil até demais...? to desconsiderando algum caso?


    cin>>n;//val pequeno!! dá pra er n²
    //msm pequeno dá ruim se for fznd caso a caso, até rsp, tem q ter um jeito mais fácil de fazer, n?


    for(int i=1;i<=n;i++){
        //cin>>f[i];
        //int a;
        cin>>G[i];
        volta[G[i]].push_back(i);
    }

    //similar a b da L2, tipo só sai um de cada, logo cada componente, termina num ciclo

    //identifica componente?
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


    //faz parte de ciclo, ver tam do ciclo
    for(int i=1;i<=n;i++){
        if(eh_ciclo[i]&&vis3[i]==false){
            //cout<<i<<"\n";
            cal_dist(tah_ciclo[comp[i]]);
            tams_de_ciclo.push_back(tam_ciclo[qual_ciclo[i]]);
        }
        
        //cout<<"tam: "<<i<<" "<<tam_ciclo[qual_ciclo[i]]<<"\n";
    }    

    alt_max=0;
    
    //ver dist até o ciclo
    int cnt=1;
    for(int i=1;i<=n;i++){
        if(eh_ciclo[i]&&volta[i].size()>1){
            //cout<<"entra"<<i<<"\n";
            alt[0]=-1;
            dfs(i,0,cnt);
            cnt++;
        }
    }

    /*cout<<"alt: ";
    for(int i=1;i<=n;i++){
        cout<<alt[i]<<" ";
    }
    cout<<"\n";
    cout<<"alt max: "<<alt_max<<"\n";*/


    //pode n³?8.10⁶..
    //achar o multiplo comum..
    //considerar o alt_max tbm..

    cout<<mult()<<"\n";

    return 0;
}

