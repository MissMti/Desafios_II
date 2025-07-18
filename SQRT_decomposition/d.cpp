#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAX = 100005;
const int SQ = 316;
int a[MAX];
int pref[MAX];

vector<pair<int,int>> q;

int tmp, freq[2000006];

int n,m,k;

inline void insert(int p) {
    int Xor=pref[p]^k;
    tmp+=freq[Xor];
    freq[pref[p]]++;
}

inline void erase(int p) {
    int Xor=pref[p]^k;
    freq[pref[p]]--;
	tmp-=freq[Xor];
}



signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
    XOR e numero favorito

    algoritmo de Mo
    */

    cin>>n>>m>>k;

    for(int i=1;i<=n;i++){
        cin>>a[i];
        pref[i]=pref[i-1]^a[i];
    }

    for(int i=0;i<m;i++){
        int l,r;
        cin>>l>>r;
        q.push_back(make_pair(l,r));
    }

    //Codigo do caderno do brunomaletta
    tmp = 0;
	vector<int> ord(m);
	iota(ord.begin(), ord.end(), 0);

	sort(ord.begin(), ord.end(), [&](int l, int r) {
		if (q[l].first / SQ != q[r].first / SQ) return q[l].first < q[r].first;
		if ((q[l].first / SQ) % 2) return q[l].second > q[r].second;
		return q[l].second < q[r].second;
	});

    /*for(int i=0;i<m;i++){
        cout<<ord[i]<<"\n";
    }*/

	vector<int> rsp(m);
	int l = 0, r = -1;

	for (int i : ord) {
		int ql, qr;
		tie(ql, qr) = q[i];
        ql--;
		while (r < qr) insert(++r);
		while (l > ql) insert(--l);
		while (l < ql) erase(l++);
		while (r > qr) erase(r--);
		rsp[i] = tmp;
	}

    for(int i=0;i<m;i++){
        cout<<rsp[i]<<"\n";
    }



    return 0;
}
