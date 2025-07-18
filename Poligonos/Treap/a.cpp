#include <bits/stdc++.h>
 
using namespace std;
#define int long long
#define MAX 100005
 

typedef struct item *pitem;
struct item {
	int pr,key,cnt;
	pitem l,r;
	item(int key):key(key),pr(rand()),cnt(1),l(0),r(0) {}
};
int cnt(pitem t){return t?t->cnt:0;}
void upd_cnt(pitem t){if(t)t->cnt=cnt(t->l)+cnt(t->r)+1;}
void split(pitem t, int key, pitem& l, pitem& r){ // l: < key, r: >= key
	if(!t)l=r=0;
	else if(key<t->key)split(t->l,key,l,t->l),r=t;
	else split(t->r,key,t->r,r),l=t;
	upd_cnt(t);
}
void insert(pitem& t, pitem it){
	if(!t)t=it;
	else if(it->pr>t->pr)split(t,it->key,it->l,it->r),t=it;
	else insert(it->key<t->key?t->l:t->r,it);
	upd_cnt(t);
}
void merge(pitem& t, pitem l, pitem r){
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),t=l;
	else merge(r->l,l,r->l),t=r;
	upd_cnt(t);
}
void erase(pitem& t, int key){
	if(t->key==key)merge(t,t->l,t->r);
	else erase(key<t->key?t->l:t->r,key);
	upd_cnt(t);
}
void unite(pitem &t, pitem l, pitem r){
	if(!l||!r){t=l?l:r;return;}
	if(l->pr<r->pr)swap(l,r);
	pitem p1,p2;split(r,l->key,p1,p2);
	unite(l->l,l->l,p1);unite(l->r,l->r,p2);
	t=l;upd_cnt(t);
}
pitem kth(pitem t, int k){
	if(!t)return 0;
	if(k==cnt(t->l))return t;
	return k<cnt(t->l)?kth(t->l,k):kth(t->r,k-cnt(t->l)-1);
}
pair<int,int> lb(pitem t, int key){ // position and value of lower_bound
	if(!t)return {0,1<<30}; // (special value)
	if(key>t->key){
		auto w=lb(t->r,key);w.first+=cnt(t->l)+1;return w;
	}
	auto w=lb(t->l,key);
	if(w.first==cnt(t->l))w.second=t->key;
	return w;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    pitem r=nullptr;
    int t;
    cin>>t;
    
    for(int loops=0;loops<t;loops++){
        char op;
        int tmp;
        cin>>op>>tmp;
        
        if(op=='I'){//insere
            pair<int,int> pos=lb(r,tmp);
            if(pos.second!=tmp){
                insert(r,new item(tmp));
            }
        }
        if(op=='D') {//deleta
            pair<int,int> pos=lb(r,tmp);
            if(pos.second==tmp){
                erase(r,tmp);
            }
        }
        if(op=='K'){//kth
            if(tmp>cnt(r)){
                cout<<"invalid\n";
            }
            else{
                pitem noh=kth(r,tmp-1);
                cout<<noh->key<<"\n";
            }
        }
        if(op=='C'){//conta
            pair<int,int> pos=lb(r,tmp);
            cout<<pos.first<<'\n';
        }
    }
    
    return 0;
}
