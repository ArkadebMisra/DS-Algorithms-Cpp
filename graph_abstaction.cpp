#include <bits/stdc++.h> 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <queue>
#define NO_NODES 100;
#define endl "\n"
using namespace std; 


class Graph{
public:
    vector <int> vertices;
    vector <vector <int>> adj = vector<vector<int>>(50000);

    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void print(){
        for(int i=0;i<6;i++){
            for(auto ele:adj[i]){
                cout << ele << " ";
            }
            cout << endl;
        }
    }
};

class BFSResult{
public:
    map <int, int> parent;
    map <int, int> level;

    void print(){
        cout << "parent" << endl;
        for(auto ele:parent){
            cout << ele.first << ":" <<ele.second << ", ";
        }
        cout << endl;
        cout << "level" << endl;
        for(auto ele:parent){
            cout << ele.first << ":" <<ele.second << ", ";
        }
        cout << endl;
    }
};




void bfs(Graph &gr, BFSResult &r, int s){
    int u, v;
    r.parent[s] = '\0';
    r.level[s] = 0;
    queue <int> q;
    q.push(s);
    while(!q.empty()){
        u = q.front();
        q.pop();
        for(auto v:gr.adj[u]){
            if(r.parent.find(v)==r.parent.end()){
                r.parent[v] = u;
                r.level[v] = r.level[u] + 1;
                q.push(v);
            }
        }
    }
}


class DFSResult{
public:
    map <int, int> parent;
    map <pair <int, int> , string> edges;
    map <int, int> start_time;
    map <int, int> finish_time;
    vector <int> order;
    int t = 0;

    void print(){
        cout<<endl;
        cout << "parent" << endl;
        for(auto ele:parent){
            cout << ele.first << ":" <<ele.second << ", ";
        }
        cout << endl;

        cout<<endl;
        cout << "start time" << endl;
        for(auto ele:start_time){
            cout << ele.first << ":" <<ele.second << ", ";
        }
        cout << endl;

        cout<<endl;
        cout << "finish time" << endl;
        for(auto ele:finish_time){
            cout << ele.first << ":" <<ele.second << ", ";
        }
        cout << endl;

        cout<<endl;
        cout << "edges" << endl;
        for(auto ele:edges){
            cout << "("<<ele.first.first << ", " << ele.first.second << "):" << ele.second << ", ";
        }
        cout << endl;

        cout<<endl;
        cout << "eorder" << endl;
        for(auto ele:order){
            cout << ele << ", ";
        }
        cout << endl;
    }
};


void dfs(Graph &g, DFSResult &r, int u, int parent= 0){
    int v;
    r.parent[u] = parent;
    r.t += 1;
    if(parent != 0){
        r.edges[make_pair(parent, u)] = "Tree";
    }
    r.start_time[u] = r.t;
    for(auto v:g.adj[u]){
        if(r.parent.find(v)==r.parent.end()){
            dfs(g, r, v, u);
        }
        else if(r.finish_time.find(v)==r.finish_time.end()){
            r.edges[make_pair(u, v)] = "back";
        }
        else if(r.start_time[u]<r.finish_time[v]){
            r.edges[make_pair(u, v)] = "forward";
        }
        else{
            r.edges[make_pair(u, v)] = "cros";
        }
    }
    r.t += 1;
    r.finish_time[u] = r.t;
    r.order.push_back(u);
}



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


//Belman-ford---------------------------------------------------------------------------------------
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


void belman_ford(WeightedGraph &g, Result &r, int n, int s){
   r.s_path[s] = 0;
   r.parent[s] = 0;
   for(int i=0; i<n;i++){
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
   belman_ford(g, r, no_nodes, 1);
   r.print();
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
*/



