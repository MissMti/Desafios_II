#include <bits/stdc++.h>

using namespace std;
#define int long long
#define MAX 100005

int n,m;



vector<int> g[MAX];

vector<int> rsp(MAX,MAX);

int verm[MAX];

vector<int> vermelhos;




int d[MAX], p[MAX], pp[MAX];

void set_root(int i) { p[i] = pp[i] = i, d[i] = 0; }

void add_leaf(int i, int u) {
	p[i] = u, d[i] = d[u]+1;
	pp[i] = 2*d[pp[u]] == d[pp[pp[u]]]+d[u] ? pp[pp[u]] : u;
}

/*int kth(int i, int k) {
	int dd = max((long long)0, d[i]-k);
	while (d[i] > dd) i = d[pp[i]] >= dd ? pp[i] : p[i];
	return i;
}*/

int lca(int a, int b) {
	if (d[a] < d[b]) swap(a, b);
	while (d[a] > d[b]) a = d[pp[a]] >= d[b] ? pp[a] : p[a];
	while (a != b) {
		if (pp[a] != pp[b]) a = pp[a], b = pp[b];
		else a = p[a], b = p[b];
	}
	return a;
}

int dist(int a, int b) { return d[a]+d[b]-2*d[lca(a,b)]; }

void build(int i, int pai=-1) {
	if (pai == -1) set_root(i);
	for (int j : g[i]) if (j != pai) {
		add_leaf(j, i);
		build(j, i);
	}
}




void bfs() {//com todos que estão em vermelhos
    queue<int> q;
    int tam=vermelhos.size();
    for (int i=0;i<tam;i++) {
        int s=vermelhos[i];
        rsp[s] = 0;
        q.push(s);
    }
    //cout<<"okay\n";
    
    
    while (!q.empty()) {
        //cout<<"entrou\n";
        int u = q.front();
        //cout<<u<<"\n";
        q.pop();
        
        for (int v : g[u]) {
            if (rsp[v] > rsp[u] + 1) {
                rsp[v] = rsp[u] + 1;
                q.push(v);
            }
        }
    }





/*

    vector<bool> visited(n,0);
    visited[s]=true;
    

    queue<pair<int,int>> q; 

    q.push(make_pair(s,0));
    if(verm[s]==1){
        rsp[s]=0;
        return;
    }

    while (!q.empty()) {

        //cout<<q.first<<
        int atu = q.front().first; 
        int dist=q.front().second+1; 
        q.pop();
        //cout<<g[atu].size()<<"tam\n";
        
        


        for (int x : g[atu]) {
            //cout<<dist<<" "<<rsp[x]<<"\n";
            if(verm[x]==1){
                rsp[s]=dist;
                return;
            }

            if (!visited[x]) {
                //rsp[x]=dist;
                visited[x] = true;
                q.push(make_pair(x,dist));
            }
        }

    }*/

}


signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
    mistura com lca e bfs

    x novos nohs vermelhos recalculamos a distancia

    n/x=xlogn

    100000/14≃7142
    x=84,4


    */

    

    cin>>n>>m;


    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    build(1);
    vermelhos.push_back(1);
    verm[1]=1;


    
    bfs();
    vermelhos.clear();
    /*for(int i=1;i<=n;i++){
        cout<<i<<" "<<rsp[i]<<"\n";
    }*/
    
    for(int loops=0;loops<m;loops++){
        int query, x;
        cin >> query >> x;
        
        if(query == 1) {
            if (verm[x]==0) {
                verm[x] = 1;
                vermelhos.push_back(x);
            }
        }
        else {
            int tmp = rsp[x];
            int tam=vermelhos.size();
            for (int j=0;j<tam;j++) {
                tmp = min(tmp, dist(x, vermelhos[j]));
            }
            cout << tmp << "\n";
        }
        
        // Processa em blocos
        if (vermelhos.size() >= 84) {
            bfs();
            vermelhos.clear();

            /*for(int i=1;i<=n;i++){
                cout<<i<<" "<<rsp[i]<<"\n";
            }*/
        }

    }
    

    return 0;
}
