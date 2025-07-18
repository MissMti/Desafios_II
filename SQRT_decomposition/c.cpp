#include <bits/stdc++.h>

using namespace std;
#define int long long

//TLE



int n,m;
vector<int> a(100005);
vector<int> lucky;
int k=500;
vector<bool> is_lucky(10004,false);
vector<vector<int>> freq_blocos(k+5,vector<int>(10004));
vector<int> lazy_soma(k+5);

bool eh_lucky(int a){
    while(a!=0){
        int sobra=a%10;
        
        if(sobra!=4 && sobra!=7){
            return false;
        }
        a/=10;
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    /*
    Lucky array
    Apenas digitos 4 e 7, array de n numeros
    add l r d : adc d em todos os elementos entre l e r (inclusivo)
    count l r : encontra quantos numeros de sorte tem no inervalo

    4, 7, 44, 47, 74, 77, 444, 447, 474, 477, 744, 747, 777..
    dá para verificar isso aqui..

    k+n/k(n/k)+k
    (k+n)n/k²+k

    */
    cin>>n>>m;

    for(int i=1;i<10004;i++){
        if(eh_lucky(i)){
            //cout<<i<<"\n";
            lucky.push_back(i);
            is_lucky[i]=true;
        }
    }

    for(int i=1;i<=n;i++){
        cin>>a[i];
        freq_blocos[i/k][a[i]]++;
    }

    for(int i=0;i<m;i++){
        string s;
        cin>>s;
        int l,r,d;
        if(s=="add"){//add
            cin>>l>>r>>d;
            while (l <= r && l % k != 0) {
                freq_blocos[l / k][a[l]]--;
                a[l] += d;
                freq_blocos[l / k][a[l]]++;
                l++;
            }
            while (l+k-1 <= r) {
                lazy_soma[l / k] += d;
                l += k;
            }
            while (l <= r) {
                freq_blocos[l / k][a[l]]--;
                a[l] += d;
                freq_blocos[l / k][a[l]]++;
                l++;
            }
        }
        else{//count
            cin>>l>>r;
            int rsp = 0;
            while (l <= r && l%k != 0) {
                if (is_lucky[a[l] + lazy_soma[l / k]]) {
                    rsp++;
                }
                l++;
            }
            while (l+k-1 <= r) {
                int tam=lucky.size();
                for (int j=0;j<tam;j++) {
                    if (lucky[j] >= lazy_soma[l/k]) {
                        rsp += freq_blocos[l/k][lucky[j]- lazy_soma[l/k]];
                    }
                }
                l += k;
            }
            while (l <= r) {
                if (is_lucky[a[l] + lazy_soma[l/k]]) {
                    rsp++;
                }
                l++;
            }
            cout<<rsp<<"\n";
        }
    }
    
    return 0;
}
