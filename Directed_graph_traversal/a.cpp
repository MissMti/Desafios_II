#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18
//#define MOD 998244353//1000000007

#define MOD 1000000007
//vector<int> dp(1000006,0);
//vector<int> aux(1000006,0);

int n;
int imp=0;
vector<string> S(200);// e de tam maximo 100, é um valor bem baixo...dá para fazer algo comisso?
//codigo n² passa..


//é de grafo.. ordenar as letras? criar como se fosse "uma lista" e ver a ordem topologica...(?)
vector<int> G[30];//abcdefghijklmnopqrstuvwxyz(26) (é ingles nao tem ç e acentos e blablabla)
vector<int> N[30];//não directionado
vector<int> I[30];//invertido
//vector<bool> vis[30];

vector<int> comp(205);
vector<bool> vis1(30,false);
vector<bool> aux(30,false);


stack<int> st; 
vector<bool> vis2(30, false);
vector<char> rsp(30);




void topologica(int i){
    vis2[i] = true;

    for (int j=0;j<G[i].size();j++) {

        if (!vis2[G[i][j]]){
            topologica(G[i][j]);
        }
    }
    st.push(i);
    //cout<<"deu push"<<i<<"\n";
}

void ordem(){
    for (int i = 0; i < 26; i++) {
        if (!vis2[i]){
            topologica(i);
            //cout<<"sai\n";
        }    
    }

    for(int i=0;i<26;i++){
        char tmp=st.top()+'a';
        //cout<<tmp<<"\n";
        rsp[i]=tmp;
        st.pop();
    }
}

vector<int> grau(30, 0);
bool ciclos(){//é ciclo?
    
    queue<int> q; 
  
    //int jah_vis = 0;

    for (int i = 0; i < 26; i++) {
        for(int j=0;j<G[i].size();j++){
            int tmp=G[i][j];
            grau[tmp]++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (grau[i] == 0) {
            q.push(i);
        }
    }

    int jah_vis = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        jah_vis++;

        for (int j=0;j<G[u].size();j++) {
            int v=G[u][j];
            grau[v]--;
            if (grau[v] == 0) {
                q.push(v);
            }
        }
    }
    //cout<<"jah_vis: "<<jah_vis<<"\n";
    if(jah_vis!=26){
        return true;
    }

    return false; 
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>n;
    for(int i=0;i<n;i++){
        cin>>S[i];
    }


    for (int i = 0; i < n-1; i++){// comparar todos com todos(?)
        int flag=0;
        for(int j=0;j<min(S[i].size(),S[i+1].size());j++){
            if(S[i][j]!=S[i+1][j]){
                int a=S[i][j]-'a';
                int b=S[i+1][j]-'a';
                //cout<<a<<" "<<b<<"\n";
                G[a].push_back(b);
                //I[b].push_back(a);
                //N[a].push_back(b);
                //N[b].push_back(b);
                flag=1;
                break;
            }

           
        }
        if(S[i].size()>S[i+1].size() && flag==0){
            imp=1;
            //cout<<"entrou"<<i<<"\n";
        }
	}

    /*for(int i=0;i<26;i++){
        cout<<i;
        for(int j=0;j<G[i].size();j++){
            cout<<" "<<G[i][j];
        }
        cout<<"\n";
    }*/

    //cout<<"sai\n";

    //não pode ter ciclos senão é uma contradição.. 
    //separa componentes
    /*int c=1;
    for(int i=0;i<n;i++){
        if(comp[i]==0 && !vis1[i]){
            componentes(i,c);
            c++;
        }
    }
    cout<<"\ncomponente conexas: \n";
    for(int i=0;i<n;i++){
        cout<<comp[i]<<" ";
    }
    cout<<"\n";*/


    //vẽ se acho ciclos..
    //int c=1;
    if(ciclos()){
        imp=1;
    }



    if(imp==1){
        cout<<"Impossible\n";
        return 0;
    }
    
    //se não gera ciclos, então..deve ter uma resposta
    //ordem topológica p/ impressão
    ordem();
    
    for(int i=0;i<26;i++){
        cout<<rsp[i];
    }

	
    cout<<"\n";
    


    return 0;
}
