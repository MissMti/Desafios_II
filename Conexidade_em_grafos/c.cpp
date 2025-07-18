#include <bits/stdc++.h>

using namespace std;

int n,m,q;

#define N 200005
vector<vector<int>> tree;

struct block_cut_tree {
	vector<vector<int>> g, blocks;
	vector<vector<pair<int, int>>> edgblocks;
	stack<int> s;
	stack<pair<int, int>> s2;
	vector<int> id, art, pos;
	
	block_cut_tree(vector<vector<int>> g_) : g(g_) {
		int n = g.size();
		id.resize(n, -1), art.resize(n), pos.resize(n);
		build();
	}

	int dfs(int i, int& t, int p = -1) {
		int lo = id[i] = t++;
		s.push(i);	
		
		if (p != -1) s2.emplace(i, p);
		for (int j : g[i]) if (j != p and id[j] != -1) s2.emplace(i, j);
		
		for (int j : g[i]) if (j != p) {
			if (id[j] == -1) {
				int val = dfs(j, t, i);
				lo = min(lo, val);

				if (val >= id[i]) {
					art[i]++;
					blocks.emplace_back(1, i);
					while (blocks.back().back() != j) 
						blocks.back().push_back(s.top()), s.pop();

					edgblocks.emplace_back(1, s2.top()), s2.pop();
					while (edgblocks.back().back() != make_pair(j, i))
						edgblocks.back().push_back(s2.top()), s2.pop();
				}
				// if (val > id[i]) aresta i-j eh ponte
			}
			else lo = min(lo, id[j]);
		}
		
		if (p == -1 and art[i]) art[i]--;
		return lo;
	}

	void build() {
		int t = 0;
		for (int i = 0; i < g.size(); i++) if (id[i] == -1) dfs(i, t, -1);
		
		tree.resize(blocks.size());
		for (int i = 0; i < g.size(); i++) if (art[i]) 
			pos[i] = tree.size(), tree.emplace_back();

		for (int i = 0; i < blocks.size(); i++) for (int j : blocks[i]) {
			if (!art[j]) pos[j] = i;
			else tree[i].push_back(pos[j]), tree[pos[j]].push_back(i);
		}
	}
};

int alt[200005]; 
int pai[200005][30]; 

void dfs2(int atu, int ant) {
    alt[atu] = alt[ant] + 1; 
    pai[atu][0] = ant; 
    for (int i=0; i<tree[atu].size(); i++)  { 
        if (tree[atu][i] != ant) {
            dfs2(tree[atu][i], atu); 
        }
    } 
} 

void pre(int n){ 
    for (int i=1; i<20; i++) { 
        for (int node = 0; node < n; node++) { 
            if (pai[node][i-1] != -1) {
                pai[node][i] = pai[pai[node][i-1]][i-1]; 
            }   
        } 
    } 
} 
 
int lca(int u, int v) { 
    if (alt[v] < alt[u]) {
        swap(u, v); 
    }
 
    int diff = alt[v] - alt[u]; 
 
    for (int i=0; i<20; i++) {
        if ((diff>>i)&1) {
            v = pai[v][i]; 
        }           
    }
        
 
    if (u == v) {
        return u; 
    }
 
    for (int i=19; i>=0; i--) {
        if (pai[u][i] != pai[v][i]) { 
            u = pai[u][i]; 
            v = pai[v][i]; 
        } 
    }
        
 
    return pai[u][0]; 
} 

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    
    cin>>n>>m>>q;
    vector<vector<int>> G(n+5);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    struct block_cut_tree A(G);

    memset(pai,-1,sizeof(pai));
    alt[0]=0;
    dfs2(0,0);
    pre(2*n);

    /*cout<<"arv: \n";
        for(int i=0;i<tree.size();i++){
            for(int j=0;j<tree[i].size();j++){
                cout<<tree[i][j]<<" ";
            }
            cout<<"\n";
        }

    cout<<"pos: \n";
        for(int i=0;i<=n;i++){
            cout<<A.pos[i]<<"\n";
        }*/

    for(int i=0;i<q;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(a==c||b==c){
            cout<<"NO\n";
            continue;
        }
        if(!A.art[c]){
            cout<<"YES\n";
            continue;
        }
        a=A.pos[a];
        b=A.pos[b];
        c=A.pos[c];
        //cout<<a<<" "<<b<<" "<<c<<"\n";
        int tmp=lca(a,b);
        //cout<<tmp<<" "<<lca(c,tmp)<<" "<<lca(a,c)<<" "<<lca(b,c)<<"\n";
        if((lca(a,c)==c && lca(c,tmp)==tmp)||(lca(b,c)==c && lca(c,tmp)==tmp)){
            cout<<"NO\n";
        }
        else{
            cout<<"YES\n";
        }
    }

    return 0;
}
