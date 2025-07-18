#include <bits/stdc++.h>

using namespace std;
#define int long long
#define MAX 200005
//vector<int> mex(MAX);




signed main() {
   ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
    E: 
Tem uma pilha com n moedas, vai dividindo, vai sobrar 2.

Construcao do mex dos estados

estado final sao varis pilhas de 1

similar ao c?




    for (int i = 0; i < 1000006; i++) {
        if (s.count(i) == 0) return i;
    }
}

    */
    


    int t; cin>>t;
    vector<int> dp = {0, 0, 0};



    for (int i = 3; i < 1225; i++) {
        set<int> s;
        for (int j = 1; j < (i+1)/2; j++) {
            //cout<<j<<" "<<i-j<<"\n";
            s.insert(dp[j]^dp[i-j]);

        }

        int mex=0;
        for (int j = 0; j<1000006; j++) {
            if(s.count(j)==0){
                mex=j;
                break;
            }
        }


        dp.push_back(mex);
    }
    /*cout<<"passou\n";

    for(int i=0;i<25;i++){
        cout<<i<<" "<<dp[i]<<"\n";
    }*/

    for(int i=0;i<t;i++){
        int tmp;
        cin>>tmp;
        if(tmp<1224){
            if(dp[tmp]==0){
                cout<<"second\n";
            }
            else{
                cout<<"first\n";
            }
        }
        else{
            cout<<"first\n";
        }
    }

    
   

    return 0;
}
