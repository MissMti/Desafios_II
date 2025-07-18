#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1e18
//#define MOD 998244353//1000000007

#define MOD 1000000007
//vector<int> dp(1000006,0);
//vector<int> aux(1000006,0);

int n,maximo,qtd=0;//1000006
stack<int> p;

//vector<char> a(1000006);
//pilha p ir tirando conforme botando...

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int i=0;
    string s;
    cin>>s;
    n=s.size();

    p.push(-1);

    for(int i=0;i<n;i++){
        if(s[i]=='(') {
            p.push(i);
        }
        else{
            //cout<<i<<" ";
            p.pop();
            if(p.empty()){
                p.push(i);
            }
            else{
                //cout<<p.top()<<"\n";
                if(i-p.top()>maximo){
                    qtd=1;
                }
                if(i-p.top()==maximo){
                    qtd++;
                }
                maximo=max(maximo, i-p.top());

            }
        }

    }
    
    if(maximo==0){
        cout<<"0 1\n";
    }
    else{
        cout<<maximo<<" "<<qtd<<"\n";
    }


    return 0;
}

