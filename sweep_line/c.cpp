#include <bits/stdc++.h>

using namespace std;
#define int long long

int n;

int mdc(int a, int b) {
    if(b==0){
        return a;
    }
    return mdc(b, a%b);
}

pair<int, int> encontra_ang(pair<int,int> a, pair<int,int> b) {
    int dx=a.first-b.first;
    int dy=a.second-b.second;
    
    if(dx==0){
        return {1,0};
    } 
    if(dy==0){
        return {0,1};
    }
    
    int tmp=mdc(dx,dy);
    dx=dx/tmp;
    dy= dy/tmp;

    if(dx<0) {//"gira"
        dx=-dx;
        dy=-dy;
    }
    
    return {dx,dy};
}

int max_colinear(vector<pair<int,int>>& pts) {
    if(n<=2){
        return n;
    } 
    
    int rsp=0;
    for (int i=0; i<n;i++){
        map<pair<int, int>, int> angulos;
        int iguais=0;
        int max_atual=0;
        
        for (int j=0; j<n; j++) {
            if (i!=j){
                if (pts[i].first==pts[j].first && pts[i].second==pts[j].second) {
                    iguais++;
                }
                else {
                    pair<int, int> tmp = encontra_ang(pts[i], pts[j]);
                    angulos[tmp]++;
                    max_atual = max(max_atual, angulos[tmp]);
                }
            }
            
            
        }
        
        rsp = max(rsp, max_atual+iguais+1);
    }
    
    return rsp;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    
    cin>>n;
    while(n!=0){
        vector<pair<int,int>> pontos(n);
        for (int i=0;i<n;i++) {
            cin>>pontos[i].first>>pontos[i].second;
        }
        
        cout<<max_colinear(pontos)<<"\n";
        cin>>n;
    }
    
    return 0;
}
