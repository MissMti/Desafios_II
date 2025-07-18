#include <bits/stdc++.h>

using namespace std;
#define int long long

// Link-cut Tree
//
// Link-cut tree padrao
//
// Todas as operacoes sao O(log(n)) amortizado

namespace lct {
	struct node {
		int p, ch[2];
		node() { p = ch[0] = ch[1] = -1; }
	};

	node t[200005];

	bool is_root(int x) {
		return t[x].p == -1 or (t[t[x].p].ch[0] != x and t[t[x].p].ch[1] != x);
	}
	void rotate(int x) {
		int p = t[x].p, pp = t[p].p;
		if (!is_root(p)) t[pp].ch[t[pp].ch[1] == p] = x;
		bool d = t[p].ch[0] == x;
		t[p].ch[!d] = t[x].ch[d], t[x].ch[d] = p;
		if (t[p].ch[!d]+1) t[t[p].ch[!d]].p = p;
		t[x].p = pp, t[p].p = x;
	}
	void splay(int x) {
		while (!is_root(x)) {
			int p = t[x].p, pp = t[p].p;
			if (!is_root(p)) rotate((t[pp].ch[0] == p)^(t[p].ch[0] == x) ? x : p);
			rotate(x);
		}
	}
	int access(int v) {
		int last = -1;
		for (int w = v; w+1; last = w, splay(v), w = t[v].p)
			splay(w), t[w].ch[1] = (last == -1 ? -1 : v);
		return last;
	}
	int find_root(int v) {
		access(v);
		while (t[v].ch[0]+1) v = t[v].ch[0];
		return splay(v), v;
	}
	void link(int v, int w) { // v deve ser raiz
		access(v);
		t[v].p = w;
	}
	void cut(int v) { // remove aresta de v pro pai
		access(v);
		t[v].ch[0] = t[t[v].ch[0]].p = -1;
	}
	int lca(int v, int w) {
		return access(v), access(w);
	}
}


signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int n,m;
    cin>>n>>m;


    for (int i=0;i<m;i++) {
        string op;
        int a,b;
        cin>>op;

        if(op=="link"){
            cin>>a>>b;
            lct::link(a,b);
        } 

        if(op=="cut"){
            cin>>a;
            lct::cut(a);
        } 
        
        if(op=="lca"){
            cin>>a>>b;
            int tmp=lct::lca(a,b);
            cout<<tmp<<"\n";
        }
    }
    
    return 0;
}
