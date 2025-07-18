#include <bits/stdc++.h>

using namespace std;
#define int long long
#define ll long long



const int NEUT = 0;
const int N=1e6;

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
	// Initializes a segTree with the values of the array A of length n
	int init(int* A, int L=0, int R=n) {
		if(L + 1 == R) return newNode(A[L]);
		int M = (L + R) >> 1;
		int l = init(A, L, M), r = init(A, M, R);
		return newNode(merge(t[l], t[r]), l , r);
	}
	int updNode(int cur_value, int upd_value) {
		return cur_value + upd_value;
	}
	// updates the position pos of version k with the value v
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
	// query in the range [l, r) of version k
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

    int n;
    cin>>n;
    vector<int> A(n);

    for(int i=0;i<n;i++){
        cin>>A[i];
    }

    segTree sg;
    segTree::n=n;
    vector<int> vers;
    vers.push_back(sg.init(A.data())); 

    int q;
    cin>>q;
    

    for(int i=0;i<q;i++) {
        int op, id,a,b;
        cin>>op>>id>>a>>b;
        
        if (op== 1) {
            int tmp = sg.upd(vers[id],a- 1, b); 
            vers.push_back(tmp);
        } 
        else {
            int rsp= sg.que(vers[id], a- 1, b);
            cout<<rsp<< '\n';
        }
    }

    return 0;
}
