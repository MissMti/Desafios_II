#include <bits/stdc++.h>

using namespace std;
#define int long long
#define MAX 100010

int SQ;
//int v[MAX];

int ans, freq[MAX];

int a[MAX];

int n,m;

vector<pair<int,int>> q(MAX);

vector<int> rsp(MAX);

inline void insert(int p) {
	int o = a[p];
	

	if(freq[o]==o){
		ans--;
	}
	freq[o]++;
	if(freq[o]==o){
		ans++;
	}
}

inline void erase(int p) {
	int o = a[p];


	if(freq[o]==o){
		ans--;
	}
	freq[o]--;
	if(freq[o]==o){
		ans++;
	}
}


void MO() {
	ans = 0;
	vector<int> ord(m);
	iota(ord.begin(), ord.end(), 1);

	/*for(int i=0;i<n;i++){
		cout<<ord[i]<<" ";
	}
	cout<<"\n";*/

	sort(ord.begin(), ord.end(), [&](int l, int r) {
		if (q[l].first / SQ != q[r].first / SQ) return q[l].first < q[r].first;
		if ((q[l].first / SQ) % 2) return q[l].second > q[r].second;
		return q[l].second < q[r].second;
	});

	/*for(int i=0;i<m;i++){
		cout<<ord[i]<<" ";
	}
	cout<<"\n";*/

	
	int l = 1, r = 0;

	for (int j=0;j<m;j++) {
		int i=ord[j];
		//cout<<i<<"\n";
		int ql, qr;
		ql=q[i].first;
		qr=q[i].second;
		while (r < qr){
			++r;
			if(a[r]<=n){//pode ser 10⁹
				insert(r);
			}
		} 
		while (l > ql){
			--l;
			if(a[l]<=n){//pode ser
				insert(l);
			}
			
		} 
		while (l < ql){
			if(a[l]<=n){//pode ser 10⁹
				erase(l);
			}
			l++;
		} 
		while (r > qr){
			if(a[r]<=n){//pode ser 10⁹
				erase(r);
			}
			r--;
		} 
		rsp[i] = ans;
	}
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
    array indexado de 1 a n
    queries com o par l e r
    contar x x's no array

    ex: 
    1 2 3 4 5 6 7
    3 1 2 2 3 3 7

    eh para usar mo's

    */
    
    cin>>n>>m;
    SQ=sqrt(n);

    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    
	for(int i=1;i<=m;i++){
        int l,r;
		cin>>l>>r;
		q[i].first=l;
		q[i].second=r;
    }

	MO();

	//int tam=rsp.size();

	for(int i=1;i<=m;i++){
		cout<<rsp[i]<<"\n";
	}
   

    return 0;
}
