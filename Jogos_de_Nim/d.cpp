#include <bits/stdc++.h>

using namespace std;
#define int long long
#define MAX 200005
vector<int> mex(MAX);

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
    C:
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

    mas preciso, mudar
    */
    

    int t;
    cin>>t;
    int M[100];

    for(int loops=1;loops<=t;loops++){
        int n,m;
        cin>>n>>m;
        int rsp=0;


        for(int l=1;l<=n;l++){
            for(int j=1;j<=m;j++){
                cin>>M[j];
            }

            int tmp=0;
            for(int c=m;c>=1;c--){
                if(M[c]<=tmp){
                    tmp=M[c]-1;
                }
                else{
                    tmp=M[c];
                }
            }

            if(tmp!=0){
                rsp=rsp^tmp;
            }
            
        }
        if(rsp==0){
            cout<<"SECOND\n";
        }
        else{
            cout<<"FIRST\n";
        }

    }
   

    return 0;
}
