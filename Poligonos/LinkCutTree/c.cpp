#include <bits/stdc++.h>

using namespace std;
#define int long long



// Link-cut Tree - vertice
//
// Valores nos vertices
// make_tree(v, w) cria uma nova arvore com um
// vertice soh com valor 'w'
// rootify(v) torna v a raiz de sua arvore
// query(v, w) retorna a soma do caminho v--w
// update(v, w, x) soma x nos vertices do caminho v--w
//
// Todas as operacoes sao O(log(n)) amortizado

namespace lct {
	struct node {
		int p, ch[2];
		int val, sub;
		bool rev;
		int sz;
		int lazy;
		node() {}
		node(int v) : p(-1), val(v), sub(v), rev(0), sz(1), lazy(0) {
			ch[0] = ch[1] = -1;
		}
	};

	node t[200005];

	void prop(int x) {
		if (t[x].lazy) {
			t[x].val += t[x].lazy, t[x].sub += t[x].lazy*t[x].sz;
			if (t[x].ch[0]+1) t[t[x].ch[0]].lazy += t[x].lazy;
			if (t[x].ch[1]+1) t[t[x].ch[1]].lazy += t[x].lazy;
		}
		if (t[x].rev) {
			swap(t[x].ch[0], t[x].ch[1]);
			if (t[x].ch[0]+1) t[t[x].ch[0]].rev ^= 1;
			if (t[x].ch[1]+1) t[t[x].ch[1]].rev ^= 1;
		}
		t[x].lazy = 0, t[x].rev = 0;
	}
	void update(int x) {
		t[x].sz = 1, t[x].sub = t[x].val;
		for (int i = 0; i < 2; i++) if (t[x].ch[i]+1) {
			prop(t[x].ch[i]);
			t[x].sz += t[t[x].ch[i]].sz;
			t[x].sub += t[t[x].ch[i]].sub;
		}
	}
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
		update(p), update(x);
	}
	int splay(int x) {
		while (!is_root(x)) {
			int p = t[x].p, pp = t[p].p;
			if (!is_root(p)) prop(pp);
			prop(p), prop(x);
			if (!is_root(p)) rotate((t[pp].ch[0] == p)^(t[p].ch[0] == x) ? x : p);
			rotate(x);
		}
		return prop(x), x;
	}
	int access(int v) {
		int last = -1;
		for (int w = v; w+1; update(last = w), splay(v), w = t[v].p)
			splay(w), t[w].ch[1] = (last == -1 ? -1 : v);
		return last;
	}
	void make_tree(int v, int w) { t[v] = node(w); }
	int find_root(int v) {
		access(v), prop(v);
		while (t[v].ch[0]+1) v = t[v].ch[0], prop(v);
		return splay(v);
	}
	bool connected(int v, int w) {
		access(v), access(w);
		return v == w ? true : t[v].p != -1;
	}
	void rootify(int v) {
		access(v);
		t[v].rev ^= 1;
	}
	int query(int v, int w) {
		rootify(w), access(v);
		return t[v].sub;
	}
	/*void update(int v, int w, int x) {
		rootify(w), access(v);
		t[v].lazy += x;
	}*/
	void link(int v, int w) {
		rootify(w);
		t[w].p = v;
	}
	void cut(int v, int w) {
		rootify(w), access(v);
		t[v].ch[0] = t[t[v].ch[0]].p = -1;
	}
	int lca(int v, int w) {
		access(v);
		return access(w);
	}
    void upd(int v,int x) {
		access(v);
		t[v].val=t[v].val+x;
	}
}



signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int n,q;
    cin>>n>>q;

    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        lct::make_tree(i,a);
    }

    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        lct::link(u,v);
    }

    for(int i=0;i<q;i++){
        int op;
        cin>>op;

        if(op==0){
            int u,v,w,x;
            cin>>u>>v>>w>>x;
            lct::cut(u,v);
            lct::link(w,x);
        }
        
        if(op==1){
            int p,x;
            cin>>p>>x;
            lct::upd(p,x);
        }
        
        if(op==2){
            int u,v;
            cin>>u>>v;
            int tmp=lct::query(u,v);
            cout<<tmp<<"\n";
        }
    }
    
    return 0;
}
