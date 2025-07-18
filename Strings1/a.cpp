#include <bits/stdc++.h>

using namespace std;
#define int long long
#define N 1000006
int n,m,t;


int best[2][N]; 
int d1[N], d2[N];

void manacher(string s){
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

    //encontrar qual é o maior palindromo de uma string(?)
    string s;
    cin>>s;
    manacher(s);

    int tam=s.size();
    int maior=best[1][0];
    int ind=0;

    for(int i=1;i<tam;i++){
        if(best[1][i]>maior){
            maior=best[1][i];
            ind=i;
        }
    }

    for(int i=0;i<maior;i++){
        cout<<s[ind+i];
    }
    cout<<"\n";

    
    return 0;
}
