#include <bits/stdc++.h>

using namespace std;

#define int long long

const long long mod1 = 1000015553, mod2 = 1000028537;
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count()); // Random number generator
static long long base = uniform_int_distribution<int>(356, mod1 - 1)(rng);	// In case TL, use const


struct hash_s{
	string s; 
	long long n;
	vector<long long> hsh1, pwr1, hsh2, pwr2;

	hash_s() : n(0) {}
	hash_s(string _s) : n(_s.size()), s(_s), hsh1(n), pwr1(n), hsh2(n), pwr2(n){	
		pwr1[0] = pwr2[0] = 1;
		for (int i = 1; i < n; i++){
			pwr1[i] = (base * pwr1[i - 1]) % mod1;
			pwr2[i] = (base * pwr2[i - 1]) % mod2;
		}
		hsh1[0] = hsh2[0] = s[0];
		for (int i = 1; i < n; i++){
			hsh1[i] = (hsh1[i - 1] * base + (long long)(s[i]))%mod1;
			hsh2[i] = (hsh2[i - 1] * base + (long long)(s[i]))%mod2;
		}
	}
	long long hash(int i, int j){ // hash no intervalo [i, j]
		if (i == 0) return (hsh1[j] << 30)^(hsh2[j]);;
		long long ret1 = ((hsh1[j] - (hsh1[i - 1] * pwr1[j - i + 1])) % mod1 + mod1) % mod1;
		long long ret2 = ((hsh2[j] - (hsh2[i - 1] * pwr2[j - i + 1])) % mod2 + mod2) % mod2;
		return (ret1 << 30)^(ret2);
	}
};


signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin>>s;
    int tam=s.size();
    //s+=s;
    //cout<<s<<"\n";
    hash_s h(s);

    vector<int> rsp;
    
    for(int i=0;i<tam;i++){
        int tam_tmp=1+i;
        int flag=0;
        //cout<<tam_tmp<<"\n";
        int j;
        for(j=0;j<=tam-tam_tmp;j+=tam_tmp){
            //cout<<0<<" "<<i<<" "<<j<<" "<<j+tam_tmp-1<<"\n";
            if(h.hash(0,i)!=h.hash(j,j+tam_tmp-1)){
                flag=1;
                break;
            }
            //cout<<"a:"<<j+tam_tmp<<"\n";
        }
    
        if(flag==0){
        
            //verifica rebarba
            int tam_reb=tam%tam_tmp;

            //cout<<"reb: "<<tam_reb<<" "<<j<<"\n";
            if(h.hash(0,tam_reb-1)==h.hash(j,tam-1) || j==tam){
                rsp.push_back(i+1);
            }
            
        }
    }
    //rsp.push_back(tam);
    int m=rsp.size();

    for(int i=0;i<m;i++){
        cout<<rsp[i]<<" ";
    }
    cout<<"\n";
    
    return 0;
}

