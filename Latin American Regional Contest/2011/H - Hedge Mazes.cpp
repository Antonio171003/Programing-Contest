#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <int> vi;

vector <vi> AdjList, NGra; 
set <ii> Bridge;
int V, E; 

int dfsNumberCounter = 0, dfsRoot = 0, rootChildren = 0;

vi dfs_num, dfs_low, dfs_parent, articulation_vertex;

void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++;      // dfs_low[u] <= dfs_num[u]
  for (int j = 0; j < (int)AdjList[u].size(); j++) {
    int v = AdjList[u][j];
    if (dfs_num[v] == -1) {                          // a tree edge
      dfs_parent[v] = u;
      if (u == dfsRoot) rootChildren++;  // special case, count children of root

      articulationPointAndBridge(v);

      if (dfs_low[v] >= dfs_num[u])              // for articulation point
        articulation_vertex[u] = true;           // store this information first
      if (dfs_low[v] > dfs_num[u]){                          // for bridge
            NGra[v].push_back(u); //Sa añade las aristas al nuevo grafo
            NGra[u].push_back(v);
      }
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);       // update dfs_low[u]
    }
    else if (v != dfs_parent[u])       // a back edge and not direct cycle
      dfs_low[u] = min(dfs_low[u], dfs_num[v]);       // update dfs_low[u]
} }

void conexos(int u, int color){

  if(dfs_parent[u]) return;

  dfs_parent[u] = color;

  for(int i = 0; i < (int) NGra[u].size(); i++){
    conexos(NGra[u][i], color);
  }

}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, q;

    while (cin >> n >> m >> q, n != 0){

      AdjList.assign(n + 1, vi());
      NGra.assign(n + 1, vi());

      dfsNumberCounter = 0;
      dfs_num.assign(n+1, -1); dfs_low.assign(n+1, 0);
      dfs_parent.assign(n+1, 0); articulation_vertex.assign(n+1, 0);

      for(int i = 0; i < m; i++){

        int a, b;

        cin >> a >> b;
        AdjList[a].push_back(b);
        AdjList[b].push_back(a);

      }

      for(int i = 1; i <= n; i++){

        if(dfs_num[i] == -1){
            dfsRoot = i;
            rootChildren = 0;
            articulationPointAndBridge(i);
            articulation_vertex[dfsRoot] = (rootChildren > 1); //Caso especial
        }

      }

      dfs_parent.assign(n+1, 0);

      for(int i = 1; i < n; i++){

          if(articulation_vertex[i] && dfs_parent[i] == 0){
            conexos(i, i);
          }

      }

      for(int i = 0; i < q; i++){
        int a, b;

        cin >> a >> b;

        if(dfs_parent[a] && dfs_parent[b] && dfs_parent[a] == dfs_parent[b]){
          cout << "Y\n";
        }
        else{
          cout << "N\n";
        }

      }

      cout << "-\n";

    }

    return 0;
}