#include<iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;
vector<int> pre;
vector<int> dist;
#define INF 0x3f3f3f3f
typedef pair<int, int> ii;
typedef vector<ii> vii;

class Heap{
    private:
        vector<ii> heap;
        int get_left_child(int index){return 2 * index+1;}
        int get_rigth_child(int index){return 2 * index+2;}
        int get_parent(int index){return (index-1)/2;}

        void swap(int i, int j){
            ii temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
        }

        bool has_left(int index){return get_left_child(index) < heap.size();}
        bool has_right(int index){return get_rigth_child(index) < heap.size();} 

    public:
        Heap(){
            heap = vector<ii>();
        }

        int get_first(int index){return heap[index].first;}
        int get_second(int index){return heap[index].second;}

        void push(int v1, int v2){
            ii p = {v1, v2};
            heap.push_back(p);
            heapfy_up(heap.size()-1);
        }

        void heapfy_up(int index){
            if(index != 0){
                int parent = get_parent(index);
                if(heap[parent].second > heap[index].second){
                    swap(parent, index);
                    heapfy_up(parent);
                }
            }
        }

        void pop(){
            if(!heap.empty()){
                heap[0] = heap.back();
                heap.pop_back();
                if(heap.size() > 1){
                    heapfy_down(0);
                }
            }
        }

        void heapfy_down(int index){
            int lc = get_left_child(index);
            int rc = get_rigth_child(index);

            int min = index;

            if(has_left(index) && heap[lc].second < heap[min].second){
                min = lc;
            }
            if(has_right(index) && heap[rc].second < heap[min].second){
                min = rc;
            }
            if(min != index){
                swap(index, min);
                heapfy_down(min);
            }
        }

        bool empty(){return heap.empty();}

        void print_heap(){
            for(int i=0; i < heap.size(); i++){
                cout << "index " << i << ": {"<<heap[i].first <<", " << heap[i].second <<"}\n";
            }
            
        }

};

void Dijkstra(vector<vector<pair<int, int>>>& adj, int origem){
    dist = vector<int>(adj.size(), INF);
    dist[origem] = 0;
    Heap h;
    h.push(0, origem);
    while(!h.empty()){
        int u = h.get_second(0);
        h.pop();
        //int u = H.top().second;
        //H.pop();
        vector<pair<int, int>>::iterator it;
        for(it = adj[u].begin(); it != adj[u].end(); ++it){
            int v = (*it).first;
            int peso = (*it).second;

            if(dist[v] > dist[u] + peso){
                dist[v] = dist[u] + peso;
                pre[v] = u;
                //H.push(make_pair(dist[u], v));
                h.push(dist[u], v);
            }
        }
    }

    for(int i =0; i < adj.size(); i++){
        cout << "Vértice: " << i << " Distância da origem: " << dist[i] << endl;
    }
}

int main(){

    int n, m;
    cin >> n >> m;

    pre = vector<int>(n, -1);

    int u, v, w;
    vector<vii> adj(n, vii(0));
    
    for(int i = 0; i < m; i++){
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    Dijkstra(adj, adj[1][0].first);
    return 0;
}