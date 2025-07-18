#include <bits/stdc++.h>

using namespace std;
#define int long long
#define N 1005
int n;//1000(baixo, dá n²)


pair<double,double> c[N];
vector<double> r(N);
vector<vector<int>> G (N);
vector<int> raizes;

double pi=3.1415926535;
double rsp=0.0;

double area(int i){
    return pi*(double)r[i]*(double)r[i];
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>n;

    for(int i=0;i<n;i++){
        cin>>c[i].first>>c[i].second>>r[i];
    }

    //obviamente cada circulo fica dentro do outro, da para pensar como arv
    //o pai de cada circulo é aquele que o contem
    //como faço para montar essa arv? o maior raio obviamente eh a raiz..
    //como verifico se um tah dentro do outro?
    //preciso achar os pais de cada um..
    //vai do maior raio pro menor raio?
    //vejo todos os raios menores do que ele
    //como n² dá para comparar todos coom todos... ver qual dos grafos tem raio maior
    //e o outro grafo está contido.., mas pode entrar no pai do pai...
    //o raio do pai tem q ser o menor entre os q o outro tah contido..
    //d=squart((x-x)²+(y-y)²), ver se essa dist eh menor q o raio
    //nao tem como ser um igual ao outro..(?) n oq eh um ponto soh
    //int raiz;
    for(int i=0;i<n;i++){
        int tmp=-1;
        int raio=10000007;//maior q o maximo
        for (int j = 0; j < n;j++){
            double dist=sqrt((c[i].first-c[j].first)*(c[i].first-c[j].first)+(c[i].second-c[j].second)*(c[i].second-c[j].second));
            //cout<<i<<" "<<j<<" "<<dist<<" "<<r[j]<<"\n";
            if(dist<=r[j] && i!=j && r[j]>r[i]){//o i está contido em j...
                //cout<<"entra: "<<r[j]<<" "<<raio<<"\n";
                if(r[j]<raio){
                    //cout<<"atualiza\n";
                    tmp=j;
                    raio=r[j];

                }
            }
        }     
        if(tmp==-1){//raiz da arv, pode ter mais de uma raiz, n eh uma raiz mas sim uma floresta
            //raiz=i;
            raizes.push_back(i);
            //cout<<i<<"\n";
        }
        else{
            G[tmp].push_back(i);
            //G[i].push_back(tmp);
            //G[i].push_back(tmp)
        }
    }

    /*cout<<"Arv:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<G[i].size();j++){
            cout<<G[i][j]<<" ";
        }
        cout<<"\n";
    }*/

    //preciso ver agr, como q vai entrar dp nesse problema...
    //tem sempre as ideias de subarv...(dfs das pontas pro topo)
    //antes da meia noite e depois(duas partes da festa)
    //tem q achar o max
    //preciso ir de floresta em floresta
    //primeiro andar e segundo andar eu só somo, depois é um que tira e um q coloca?

    //dfs(raiz);?
    
    for(int i=0;i<raizes.size();i++){
        queue<int> q;
        q.push(raizes[i]);
        int nivel =1;

        while (!q.empty())  {
            int tam = q.size(); 
            for (int k = 0; k < tam; k++)   {
                int u= q.front();
                q.pop();
                if(nivel==1 || nivel==2 || nivel%2==0){
                    rsp+=area(u);
                }
                else {
                    if(nivel%2==1){
                        rsp-=area(u);
                    }
                }
                for(int j=0;j<G[u].size();j++){
                    q.push(G[u][j]);
                }
            }
            nivel++;
        }

    }

    cout<<fixed<<setprecision(12);
    cout<<rsp<<"\n";

    return 0;
}
