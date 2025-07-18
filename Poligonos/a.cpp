#include <bits/stdc++.h>

using namespace std;
#define int long long
#define MAX 100005



int n;

int produto_vetorial(pair<int,int> &A,pair<int,int> &B,pair<int,int> &C){
    return (B.first-A.first)*(C.second-B.second)-(B.second-A.second)*(C.first-B.first);
}

bool eh_convexo(vector<pair<int,int>> &poligono){
    if(n<3){
        return false;
    }

    int tmp;
    int ant=0;
    for(int i=0;i<n;i++){
        tmp=produto_vetorial(poligono[i],poligono[(i+1)%n],poligono[(i+2)%n]);
        if(tmp!=0){
            if(tmp*ant<0){
                return false;
            }
            ant=tmp;
        }
    }

    return true;
}


signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    
    cin>>n;
    while(n!=0){
        vector<pair<int,int>> poligono(n);
        for(int i=0;i<n;i++){
            cin>>poligono[i].first>>poligono[i].second;
        }

        if(!eh_convexo(poligono)){
            cout<<"Yes\n";
        }
        else{
            cout<<"No\n";
        }
        cin>>n;
    }

    return 0;
}
