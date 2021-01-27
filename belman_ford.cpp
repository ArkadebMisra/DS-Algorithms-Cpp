//Belman-ford---------------------------------------------------------------------------------------
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


bool belman_ford(WeightedGraph &g, Result &r, int n, int s){
   r.s_path[s] = 0;
   r.parent[s] = 0;
   for(int i=0; i<n-1;i++){
      for(int u=1;u<=n;u++){
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



int main (){
   int no_nodes, no_edges, u, v, w;
   WeightedGraph g;
   Result r;
   bool found;
   cin >> no_nodes >> no_edges;
   for(int i=0;i<no_edges;i++){
      cin >> u >> v >> w;
      g.add_edge(u, v, w);
   }
   found = belman_ford(g, r, no_nodes, 1);
   if(found){
      r.print();
   }
   else{
      cout << "the graph contains a negetive weight cycle\n";
   }
   
   return 0;
}
/*test Input
5 10
1 2 6
1 4 7
2 4 8
2 3 5
3 2 -2
4 5 9
5 1 2
5 3 7
2 5 -4
4 3 -3

contains negetive weight cycle
5 10
1 2 6
1 4 7
2 4 8
2 3 5
3 2 -7
4 5 9
5 1 2
5 3 7
2 5 -4
4 3 -3
*/