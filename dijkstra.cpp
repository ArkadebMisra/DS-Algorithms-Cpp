//Dijkstra.....................................................................................

#include <bits/stdc++.h> 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <queue>
#define endl "\n"
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

class WeightedGraph{
public:
   map <pair <int, int>, int> weight;
   vector <vector <int>> adj = vector<vector<int>>(100000000);
   
   void add_edge(int u, int v, int w){
      adj[u].push_back(v);
      weight[make_pair(u, v)] = w;
   }
};


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



int main (){
   int no_nodes, no_edges, u, v, w;
   WeightedGraph g;
   Result r;
   cin >> no_nodes >> no_edges;
   for(int i=0;i<no_edges;i++){
      cin >> u >> v >> w;
      g.add_edge(u, v, w);
   }
   dijkstra(g, r, 1);
   r.print();
   return 0;
}
/*test Input
5 10
1 2 10
1 4 5
2 4 2
4 2 3
2 3 1
4 3 9
4 5 2
5 1 7
3 5 4
5 3 6
*/