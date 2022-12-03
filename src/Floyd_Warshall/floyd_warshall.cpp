#include<iostream>
#include<vector>

using namespace std;

void Floyd_Warshall(vector<vector<int>>& adj, int n){
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if((adj[i][k] * adj[k][j] != 0) && (i != j)){
                    if((adj[i][k] + adj[k][j] < adj[i][j]) ||
                    (adj[i][j] == 0)){
                        adj[i][j] = adj[i][k] + adj[k][j];
                    }
                }
            }
        }
    }

    for(int i=0; i < n; i++){
        cout << "Custo mínimo para o vértice "<<i<<endl;
        for(int j=0; j<n; j++){
            cout<<adj[i][j] <<" ";
        }
        cout << endl;
    }
}


int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>(0));

    int u;

    for(int i = 0; i < n; i++){
        for(int j=0; j < m; j++){
            cin >> u;
            adj[i].push_back(u);
        }
    }
    

    Floyd_Warshall(adj, n);

    return 0;
}