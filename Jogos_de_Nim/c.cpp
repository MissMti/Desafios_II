#include <bits/stdc++.h>

using namespace std;
#define int long long
#define MAX 200005
vector<int> mex(MAX);

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
    Para ganhar tem q comecar o ultimo, ou seja, perder o anterior
    Para perder o ultimo, tem q comecar o penultimo(pq ai tira tudo menos 1)
    Precisa perder o anterior...(?)

    Da ruim quando soh tem 1 na pila, 
    1 para 1, 2 ou + consigo trocar ou permanecer na ordem
    
    consigo juntar todos os casos 1 sao 2+

    juntar os de 1 e encontrar se eh 0 ou 1

    qm ganha (1 ou 0)
    
    o ultimo é 1

    consigo controlar minha posicao depois, 

    2 5 1 4

    */

    int t;
    cin>>t;

    for(int loops=1;loops<=t;loops++){
        int n;
        cin>>n;
        int tmp=0;
        for(int i=1;i<=n;i++){
            int x;
            cin>>mex[i];
            if(mex[i]!=1 && tmp==0){
                tmp=i;
            }
        }

        //cout<<tmp<<"\n";
        if(tmp==0){
            if(n%2==0){
                cout<<"Second\n";
            }
            else{
                cout<<"First\n";
            }
        }
        else{
            if(tmp%2==0){
                cout<<"Second\n";
            }
            else{
                cout<<"First\n";
            }
        }
    }
    
    
   

    return 0;
}
