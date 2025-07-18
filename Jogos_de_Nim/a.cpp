#include <bits/stdc++.h>

using namespace std;
#define int long long
#define MAX 1000006

int rsp[MAX];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
    A:
    Varios tipos de jogadas diferentes
    Podem ser tratados como "jogos diferentes"
    Acho o mex de cada posicao, queremos que o proximo tenha uma posicao perdedora
    */

    int n,k;

    cin>>n>>k;

    int p[n+5];

    for(int i=1;i<=k;i++){
        cin>>p[i];
    }

    //levar em consideracao o numero maximo q ele alcança
    /*
    Tecnicamente poderia dar infinito, n?... se p1 nao fosse 1...
    */

    rsp[0]=0;//mex

    for(int i=1;i<=n;i++){
        int tmp=0;// se acha uma posicao q seja 0, ou seja perde, é pq a atual é vencedora
        for(int j=1;j<=k;j++){
            if(p[j]<=i){
                if(rsp[i-p[j]]==0){
                    tmp=1;
                }
            }
            
        }
        if(tmp==1){
            rsp[i]=1;
        }
    }

    for(int i=1;i<=n;i++){
        if(rsp[i]==0){
            cout<<"L";
        }
        else{
            cout<<"W";
        }
    }
    cout<<"\n";
   

    return 0;
}

