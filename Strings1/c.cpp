#include <bits/stdc++.h>

using namespace std;
#define int long long
#define N 100005
//int n;

//string s;
//int tam;

vector<int> eh_sp;

vector<int> rsp(N,0);

vector<int> z_function(string s) {
	int tam=s.size();
	vector<int> z(tam+5);
	for(int i = 1, l = 0, r = 0; i <tam; i++) {
		if(i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while(i + z[i] <tam && s[z[i]] == s[i + z[i]])
			z[i]++;
		if(i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    string s;
    cin>>s;
    int tam = s.size();

    vector<int> z=z_function(s);

    /*for(int i=0;i<tam;i++){
        cout<<z[i]<<" ";
    }
    cout<<"\n";*/

    int qtd=0;
    for(int i=0;i<tam;i++){
        
        if(z[tam-1-i]+tam-i-1==tam){
            //cout<<i+1<<"\n";
            eh_sp.push_back(i+1);
            rsp[i+1]++;
            qtd++;
        }
        else{
           if(z[tam-1-i]>0){
                rsp[z[tam-1-i]]++;
            } 
        }
    }
    rsp[tam]=1;//q eh o grandao
    qtd++;
    eh_sp.push_back(tam);


    //contar quantas vezes aparecem
    //contar quantas ocorrencias no z
    //contar as repeticoes...

    /*for(int i=0;i<tam;i++){
        if(z[i]>0){
            rsp[z[i]]++;
        }
    }*/

    /*for(int i=0;i<=tam;i++){
        cout<<rsp[i]<<" ";
    }
    cout<<"\n";*/

    //se aconteceu o prefixo maior, acontece o menor tambem 
    //multiplicaaco? soma?
    //
    for(int i=tam-1;i>=0;i--){
        rsp[i]+=rsp[i+1];
    }

    /*for(int i=0;i<=tam;i++){
        cout<<rsp[i]<<" ";
    }
    cout<<"\n";*/


    cout<<qtd<<"\n";
    for(int i=0;i<qtd;i++){
        cout<<eh_sp[i]<<" "<<rsp[eh_sp[i]]<<"\n";
    }

    return 0;
}
