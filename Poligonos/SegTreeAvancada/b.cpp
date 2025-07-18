#include <bits/stdc++.h>

using namespace std;
#define int long long
#define ll long long



const int NEUT=0;
const int N=200010; 

struct segTree {
	vector<int> t = vector<int>(1, NEUT);
	vector<int> left = vector<int>(1, 0), right = vector<int>(1, 0);
	static int n;
	int newNode(int v, int l=0, int r=0) {
		t.push_back(v), left.push_back(l), right.push_back(r);
		return t.size() - 1;
	}
	int merge(int a, int b) {
		return a + b;
	}
	int init(int L=0, int R=n) {
		if(L + 1 == R) return newNode(NEUT);
		int M = (L + R) >> 1;
		int l = init(L, M), r = init(M, R);
		return newNode(merge(t[l], t[r]), l , r);
	}
	int updNode(int cur_value, int upd_value) {
		return upd_value;
	}
	int upd(int k, int pos, int v, int L=0, int R=n) {
		int nxt = newNode(t[k], left[k], right[k]);
		if(L + 1 == R) t[nxt] = updNode(t[nxt], v);
		else {
			int M = (L + R) >> 1;
			int temp;
			if(pos < M) temp = upd(left[nxt], pos, v, L, M), left[nxt] = temp;
			else temp = upd(right[nxt], pos, v, M, R), right[nxt] = temp;
			t[nxt] = merge(t[left[nxt]], t[right[nxt]]);
		}
		return nxt;
	}
	int que(int k, int l, int r, int L=0, int R=n){
		if(r <= L || R <= l) return NEUT;
		if(l <= L && R <= r) return t[k];
		int M = (L + R) >> 1;
		return merge(que(left[k], l, r, L, M), que(right[k], l, r, M, R));
	}
};
int segTree::n = N;


signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


    int n,q;
    cin>>n>>q;
    vector<int> A(n);
    for(int i=0;i<n;i++){
        cin>>A[i];
    }

    segTree seg;
    segTree::n = n;
    vector<int> vers(n+1);
    vers[0]=seg.init();
    map<int,int> tmp;
    for(int i=1;i<=n;i++){
        int atual=vers[i-1];
        if(tmp.count(A[i-1])){
            atual=seg.upd(atual,tmp[A[i-1]]-1,0);
        }
        atual=seg.upd(atual,i-1,1);
        vers[i]=atual;
        tmp[A[i-1]]=i;
    }

    for(int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        cout<<seg.que(vers[b],a-1,b)<<"\n";
    }

    return 0;
}
