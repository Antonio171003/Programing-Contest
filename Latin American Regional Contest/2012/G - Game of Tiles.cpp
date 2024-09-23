//Bipartite Machine - Hopcroft Karp
#include <bits/stdc++.h>

#define MAX 60
#define MAXN 2505
#define INF 1000000000

using namespace std;

typedef vector <int> vi;

int r, c, n, m, ca1 = 0, ca2 = 0;;

int vis[MAX][MAX];
string grid[MAX];

vector <vi> AdjList;

int M1[] = {-1, 0, 1, 0};
int M2[] = {0, 1, 0, -1};

int pairU[MAXN];
int pairV[MAXN];
int dist[MAXN];

bool bfs(){

    queue <int> q;

    for(int u = 1; u <= ca1; u++){
        
        if(!pairU[u]){
            dist[u] = 0;
            q.push(u);
        }
        else{
            dist[u] = INF;
        }

    }

    dist[0] = INF;

    while(!q.empty()){
        int u = q.front(); q.pop();

        if(dist[u] < dist[0]){
            for(int v : AdjList[u]){
                if(dist[pairV[v]] == INF){
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]); 
                }
            }
        }
    }

    return dist[0] != INF;
}

bool dfs(int u){
    if(u){
        for(int v : AdjList[u]){
            if(dist[pairV[v]] == dist[u] + 1){
                if(dfs(pairV[v])){
                    pairU[u] = v;
                    pairV[v] = u;
                    return true;
                }
            }
        }

        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroftKarp(){
    int result = 0;

    for(int u = 0; u <= ca1; u++){
        pairV[u] = pairU[u] = 0;
    }

    while(bfs()){
        for(int u = 1; u <= ca1; u++){
            if(!pairU[u] && dfs(u)){
                result++;
            }
        }
    }

    return result;
}

void colorear(int i, int j, int co){

    if(vis[i][j]) return;

    if(co == 1) vis[i][j] = ++ca1;
    else vis[i][j] = ++ca2;

    for(int k = 0; k < 4; k++){

        int x = i + M1[k], y = j + M2[k];

        if(x >= 0 && x < r && y >= 0 && y < c){

            if(grid[x][y] == '.'){

                colorear(x, y, (co + 1) % 2);

                if(co == 1){
                    AdjList[vis[i][j]].push_back(vis[x][y]);
                }

            }

        }

    }

}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while(cin >> r >> c){

        int win = 2;

        for(int i = 0; i < r; i++){
            cin >> grid[i];
        }

        n = r * c; // Cantidad de nodos

        memset(vis, 0, sizeof(vis));
        AdjList.assign(n, vi());

        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){

                if(grid[i][j] == 'X') continue;
                if(vis[i][j]) continue;

                ca1 = ca2 = 0;
                colorear(i, j, 1);

                if(ca1 != ca2 || ca1 != hopcroftKarp()){
                    win = 1;
                }

            }
        }

        cout << win << '\n';

    }

    return 0;
}