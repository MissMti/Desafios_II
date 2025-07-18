#include <bits/stdc++.h>

using namespace std;
#define int long long
#define Mx 1e5+5
#define Mod 998244353

int freq[300005];

/*int comb(int x,int k){

}*/

int modexp(int b, int e, int m = Mod) {
	int res = 1;
	b %= m;
	while (e > 0) {
		if (e & 1) res = (res * b) % m;
		b = (b * b) % m;
		e /= 2;
	}
	return res;
}

int inv(int a, int m = Mod) {
	return modexp(a, m-2, m);
}

signed main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
    Dá para fazer, soh ver quantas estão ligadas no momento
    Contando as quantidades, dá para fazer combincao e somar tudo
    */

    /*
    1 2 3 4 5 6 7 8 9 10
    - - - - - - -
        - - - - - -
        - -
            - -
    - - -
            - - - - - -
                - -
    2 2 3 3 4 4 4 3 2 1
    0 0 1 1 3 3 0 1 0 0=9
    */

    int n,k;
    cin>>n>>k;
    vector<pair<int,bool>> v;
    //vector<int> l;
    //vector<int> r;
    for(int i=0;i<n;i++){
        int lt,rt;
        cin>>lt>>rt;
        v.push_back(make_pair(lt,0));
        v.push_back(make_pair(rt,1));
    }

    sort(v.begin(),v.end());

    /*cout<<"ord:\n";
    for(int i=0;i<2*n;i++){
        cout<<v[i].first<<" "<<v[i].second<<"\n";
    }
    cout<<"\n";*/

    int tmp=0;
    
    for(int i=0;i<2*n;i++){
        if(v[i].second==0){
            freq[tmp]++;
            tmp++;
        }
        else{
            tmp--;
        }
        
    }

    /*
    cout<<"freq:\n";
    for(int i=0;i<=n;i++){
        cout<<freq[i]<<" ";
    }
    cout<<"\n\n";
    */
    

    int rsp=0;
    /*
    i=k-1
    (k-1)!/(k-1)!(0)!=1
    (n+1)/(n-k+1)
    i/1 * atual *qtd

    fixo um
    */

    int inv_mod[n];

    for(int i=0;i<n;i++){
        inv_mod[i]=inv(i);
    }

    tmp=1;
    for(int i=k-1;i<=n;i++){
        rsp=((rsp%Mod)+((tmp%Mod)*(freq[i]%Mod))%Mod)%Mod;

        int mult=((i+1)*(inv_mod[i+1-(k-1)]%Mod))%Mod;
        //cout<<mult<<"\n";
        tmp=((tmp%Mod)*(mult%Mod))%Mod;
        //cout<<tmp<<"\n";
    }

    cout<<rsp<<"\n";



    return 0;
}
