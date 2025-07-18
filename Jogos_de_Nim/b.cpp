#include <bits/stdc++.h>

using namespace std;
#define int long long
#define MAX 200005
vector<int> mex(MAX);

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
    Vemos qual é o xor.., pq se forem iguais já temos a resposta
    o que tem que é fora disso? vemos 
    101+101+111+010=101 
    8 0
    7 3
    6 2
    5 1
    4 0
    3 3
    2 2
    1 1
    0 0
    ...

    quais sao os momentos q nao dá pra escolher? quantos sao eles

    pares g -> perco
    p -> sempre perco(0)
    p/g -> 

    5 7 2 5 (1 3 2 1) 

    4 1 (0 1) 

    4 4 4 (0 0 0) 

    100+001=101 

    011+001=010

    1321->ganha
    01->ganha
    000->perde

    q nem no video?
    */

    int t;
    cin>>t;
    

    for(int loops=1;loops<=t;loops++){
        int n;
        cin>>n;
        
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            mex[i]=x%4;
        }

        

        int Xor=0;
        for(int i=1;i<=n;i++){
            //cout<<mex[i];
            Xor=Xor^mex[i];
        }
        //cout<<"\n";

        //cout<<Xor<<"\n";

        if(Xor==0){
            cout<<"second\n";
        }
        else{
            cout<<"first\n";
        }

    }
    
   

    return 0;
}
