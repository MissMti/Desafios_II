#include <bits/stdc++.h>

using namespace std;
#define int long long
#define N 5000006
int n,mod;


int best[2][N]; 
int d1[N], d2[N];
int dp[N];

void manacher(string &s){
	n = s.size();
	for(int i = 0; i < n; i++)
		best[0][i] = best[1][i] = 1;
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
		while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
			best[1][i-k] = max(best[1][i-k], k << 1 | 1);
			best[0][i+k] = max(best[0][i+k], k << 1 | 1);
			k++;
		}
		d1[i] = k--;
		if (i + k > r) {
			l = i - k;
			r = i + k;
		}
	}
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
			best[1][i-k-1] = max(best[1][i-k-1], k*2 + 2);
			best[0][i+k] = max(best[0][i+k], k*2 + 2);
			k++;
		}
		d2[i] = k--;
		if (i + k > r) {
			l = i - k - 1;
			r = i + k ;
		}
	}
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //programacao  dinamica
    //dp[i]=0 se nao for paindromo, caso contrario dp[i]=1+dp[i/2]
    //descobrir para todos os prefixos se eles sao palindromo ou nao
    //ED de palindromo, manacher(verificar se um intervalo é palindromo em O(1))
    //olhando o valor M do seu centro
    //pode fazer com hash tbm
    //pior q eu jah tinha pensado nisso, mas a exec ficou ruim eu acho..

    string s;
    cin>>s;
    manacher(s);



   /* for(int i=0;i<n;i++){
        cout<<best[0][i]<<" ";
    }
    cout<<"\n";*/

    
    dp[0]=1;
    for(int i=1;i<n;i++){
        if(best[0][i]==i+1){//eh palindromo
            //cout<<"p: "<<i<<"\n";
            dp[i]=1+dp[(i-1)/2];
        }
        else{
            dp[i]=0;
        }
    }

    int rsp=0;
    for(int i=0;i<n;i++){
        //cout<<dp[i]<<" ";
        rsp+=dp[i];

    }
    cout<<rsp<<"\n";

    return 0;
}
