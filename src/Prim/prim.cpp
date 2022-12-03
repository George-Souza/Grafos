#include<iostream>
#include<vector>

using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<int> pre;
vector<int> custo;
#define INF 0x3f3f3f3f

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


void Prim(vector<vii>& adj, int src){
    custo[src] = 0;
    Heap h;
    h.push(src, 0);
    vector<bool> inMST(adj.size(), false);
  

    while(!h.empty()){
        int v = h.get_second(0);
        h.pop();
        vector<pair<int, int>>::iterator it;
        if(inMST[v] == true){
            continue;
        }
        inMST[v] = true;
        for(it = adj[v].begin(); it != adj[v].end(); ++it){
            int u = (*it).first;
            int peso = (*it).second;
            if(inMST[u] == false && custo[u] > peso){
                custo[u] = peso;
                h.push(custo[u], u);
                pre[u] = v;
            }
        }
    }

    for(int i = 1; i < pre.size(); ++i){
        cout << pre[i] << "-" << i << endl;
    }
}

int main(){

    int n, m;
    cin >> n >> m;

    pre = vector<int>(n, -1);
    custo = vector<int>(n, INF);
    int u, v, w;
    vector<vii> adj(n);
    for(int i = 0; i < m; i++){
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    
    Prim(adj, adj[1][0].first);

    return 0;
}