#include <bits/stdc++.h> 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <queue>
#define endl "\n"
#define inf 999999999999
using namespace std;

class Result{
public: 
   map <int, int> s_path;
   map <int, int> parent;

    void print(){
        cout<<endl;
        cout << "shortest path" << endl;
        for(auto ele:s_path){
            cout << ele.first << ":" <<ele.second << ", ";
        }
        cout << endl;

        cout<<endl;
        cout << "parent" << endl;
        for(auto ele:parent){
            cout << ele.first << ":" <<ele.second << ", ";
        }
        cout << endl;
    }
};

class TabulerResult{
public:
    long long int dist[100][100];
    int parent[101][101];    
};

class WeightedGraph{
public:
   map <pair <int, int>, int> weight;
   map <int , int > h;
   vector <vector <int>> adj = vector<vector<int>>(100000000);
   
   void add_edge(int u, int v, int w){
      adj[u].push_back(v);
      weight[make_pair(u, v)] = w;
   }
};

bool belman_ford(WeightedGraph &g, Result &r, int n, int s){
   r.s_path[s] = 0;
   r.parent[s] = 0;
   for(int i=0; i<n-1;i++){
      for(int u=0;u<=n;u++){
         for(auto v:g.adj[u]){
            if(((r.s_path.find(u)!=r.s_path.end()) && (r.s_path.find(v)==r.s_path.end()))||
            ((r.s_path[u]+g.weight[make_pair(u, v)])<r.s_path[v])){
               r.s_path[v] = r.s_path[u]+g.weight[make_pair(u, v)];
               r.parent[v] = u;
               }
         }
      }
   }
   for(int u=1;u<=n;u++){
      for(auto v:g.adj[u]){
         if(r.s_path[v]>r.s_path[u]+g.weight[make_pair(u, v)]){
            return 0;
         }
      }
   }
   return 1;
}

void dijkstra(WeightedGraph &g, Result &r, int s){
   set <pair <int, int>> pq;
   set <pair <int, int>>::iterator set_iter;
   r.s_path[s] = 0;
   r.parent[s] = 0;
   pq.insert(make_pair(0, s));
   while(!pq.empty()){
      int u = pq.begin()->second;
      int weight = pq.begin()->first;
      pq.erase(pq.begin());
      
      for(auto v:g.adj[u]){
         int new_weight;
         if(r.s_path.find(v) == r.s_path.end()){
            new_weight = weight + g.weight[make_pair(u, v)];
            r.s_path[v] = new_weight;
            r.parent[v] = u;
            pq.insert(make_pair(new_weight, v));
         }
         else{
            new_weight = weight + g.weight[make_pair(u, v)];
            if(new_weight<r.s_path[v]){
               pq.erase(pq.find(make_pair(r.s_path[v], v)));
               pq.insert(make_pair(new_weight, v));
               r.s_path[v] = new_weight;
               r.parent[v] = u;
            }
         }
      }
   }
}

bool johnson(WeightedGraph &g, TabulerResult &result, int no_nodes){
    Result r;
    for(int i=1;i<=no_nodes;i++){
        g.add_edge(0, i, 0);
    }
    if(belman_ford(g, r, no_nodes+1, 0)==0){
        return 0;
    }
    else{
        for(int i=1;i<=no_nodes;i++){
            g.h[i] = r.s_path[i];
        }
        for(int u=1;u<=no_nodes;u++){
            for(auto v:g.adj[u]){
                g.weight[make_pair(u, v)] = g.weight[make_pair(u, v)]+g.h[u]-g.h[v];
            }
        }
        for(int u=1;u<=no_nodes;u++){
            Result r;
            dijkstra(g, r, u);
            for(auto ele:r.s_path){
                result.dist[u][ele.first] = ele.second + g.h[ele.first] - g.h[u];
            }
            /*
            for(int v=1;v<=no_nodes;v++){
                result.dist[u][v] = r.s_path[v]+g.h[u]-g.h[v];
            }
            */
        }
        return 1;
    }

}

int main(){
    int no_nodes, no_edges;
    int u, v, w;
    bool found;
    WeightedGraph g;
    cin >> no_nodes >> no_edges;
    for(int i=0;i<no_edges;i++){
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
    TabulerResult r;
    int i, j;
    for(i=1;i<=no_nodes;i++){
        for(j=1;j<=no_nodes;j++){
            if(i==j){
                r.dist[i][j] = 0;
            }
            else{
                r.dist[i][j] = inf;
            }

        }
    }
    found = johnson(g, r, no_nodes);
    if(found){
        for(i=1;i<=no_nodes;i++){
            for(j=1;j<=no_nodes;j++){
                if(r.dist[i][j]==inf){
                    cout << "inf\t";
                }
                else{
                    cout << r.dist[i][j] << "\t";
                }
            }
            cout << endl;
        }
    }
    else{
        cout << "the graph contains a negetive weight cycle\n";
    }

    return 0;
}

/*
5 9
1 2 3
1 3 8
1 5 -4
2 5 7
2 4 1
3 2 4
4 3 -5
4 1 2
5 4 6

contains negetive weight cycle
5 10
1 2 3
1 3 8
1 5 -4
2 5 7
2 4 1
3 2 4
4 3 -5
4 1 2
5 4 6
3 4 -1
*/


