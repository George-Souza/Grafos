#include<bits/stdc++.h>

using namespace std;
typedef pair<int, int> ipair;

struct Disjuntos{
    vector<int> pai, rank;
    int n;

    Disjuntos(int n){
        this->n = n;
        pai = vector<int>(n+1);
        rank = vector<int>(n+1);

        for(int i=0; i<=n; i++){
            rank[i] = 0;
            pai[i] = i;
        }
    }

    int Find(int v){
        if(pai[v] != v){
            pai[v] = Find(pai[v]);
        }
        return pai[v];
    }

    void Union(int x, int y){
        x = Find(x);
        y = Find(y);

        if(rank[x] > rank[y]){
            pai[y] = x;
        } else{
            pai[x] = y;
        }

        if(rank[x] == rank[y]){
            rank[x]++;
        }
    }
};

struct Grafo{
    int V, m;
    vector<pair<int, ipair>> arestas;

    Grafo(int n, int m){
        this->V = n;
        this->m = m;
    }

    void addAresta(int u, int v, int w){
        arestas.push_back({w, {u, v}});
    }
    int Kruskal();

};

    int Grafo::Kruskal(){
        int wt = 0;

        sort(arestas.begin(), arestas.end());

        Disjuntos ds(V);

        vector<pair<int,ipair>>::iterator i;

        for(i=arestas.begin(); i!=arestas.end(); ++i){
            int u = i->second.first;
            int v = i->second.second;

            int setU = ds.Find(u);
            int setV = ds.Find(v);

            if(setU != setV){
                cout << u << " - " << v << endl;

                wt += i->first;

                ds.Union(setU, setV);
            }
        }

        return wt;
    }
int main(){
    int n, m;
    cin >> n >> m;

    Grafo g(n, m);

    int u, v, w;

    for(int i=0; i < m; i++){
        cin >> u >> v >> w;
        g.addAresta(u, v, w);
    }
    int k = g.Kruskal();
    cout <<"..."<<k<<endl;
    return 0;
}