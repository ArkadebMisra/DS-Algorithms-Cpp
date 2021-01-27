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
    long long int dist[100][100];
    int parent[101][101];    
};

class Graph{
public:
    long long int edge[101][101];
};


void floyd_warshall(Result &r, int v){
    for(int k=1;k<=v;k++){
        for(int i=1;i<=v;i++){
            for(int j=1;j<=v;j++){
                if(r.dist[i][k] + r.dist[k][j] < r.dist[i][j]){
                    r.dist[i][j] = r.dist[i][k] + r.dist[k][j];
                }
            }
        }
    }

}
int main(){
    int no_nodes, no_edges;
    int u, v, w;
    cin >> no_nodes >> no_edges;
    Result r;
    Graph g;
    int i, j;
    for(i=1;i<=no_nodes;i++){
        for(j=1;j<=no_nodes;j++){
            if(i==j){
                r.dist[i][j] = 0;
                g.edge[i][j] = 0;
            }
            else{
                r.dist[i][j] = inf;
                g.edge[i][j] = inf;
            }

        }
    }
    for(i=0;i<no_edges;i++){
        cin >> u >> v >> w;
        g.edge[u][v] = w;
        r.dist[u][v] = w;
    }
    floyd_warshall(r, no_nodes);
    for(i=1;i<=no_nodes;i++){
        for(j=1;j<=no_nodes;j++){
            cout << r.dist[i][j] << "\t";
        }
        cout << endl;
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
*/


