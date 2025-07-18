#include <bits/stdc++.h>

using namespace std;
#define int long long
#define MAX 1e6 + 6

priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap_dois;


signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n,k;
    cin>>n>>k;
    vector<pair<int,pair<int,int>>> A(n);//inicio , fim e id
    for(int i=0;i<n;i++){
        int tmpa,tmpb;
        cin>>tmpa>>tmpb;
        A[i].first=tmpa;
        A[i].second.first=tmpb;
        A[i].second.second=i;
    }

    sort(A.begin(),A.end());

    /*cout<<"\n";
    for(int i=0;i<n;i++){
        cout<<A[i].first<<" "<<A[i].second.first<<" "<<A[i].second.second<<"\n";
    }
    cout<<"\n";*/

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;

    int rsp=0;

    for(int i=0;i<n;i++){
        heap.push(A[i].second);
        if(heap.size()>k){
            heap.pop();
        }

        if(heap.size()==k){
            int tmp_fim=heap.top().first;
            int tmp_rsp=tmp_fim-A[i].first;
            rsp=max(rsp,tmp_rsp);
            
        }
    }

    vector<int> indices;

    for(int i=0;i<n;i++){
        heap_dois.push(A[i].second);
        if(heap_dois.size()>k){
            heap_dois.pop();
        }
        if(heap_dois.size()==k){
            int tmp_fim=heap_dois.top().first;
            int tmp_rsp=tmp_fim-A[i].first;
            if(tmp_rsp==rsp){
                while(!heap_dois.empty()){
                    indices.push_back(heap_dois.top().second);
                    heap_dois.pop();
                }
                break;
                
            }
        }
    }

    sort(indices.begin(),indices.end());

    cout<<rsp<<"\n";
    for(int i=0;i<k;i++){
        cout<<indices[i]+1<<" ";
    }
    cout<<"\n";


    return 0;
	
}
