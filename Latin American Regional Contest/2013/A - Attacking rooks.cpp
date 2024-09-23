#include <bits/stdc++.h>

#define ENDL '\n'
#define INF 1000000000
#define MAX 105

using namespace std;

typedef long long ll;
typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

struct HopcroftKrap {
    using F = ll; // flow type
    int N, n1, n2;
    vi pairU, pairV, dist;
    vector <vi> adj;

    void init(int _N, int M){
        N = _N + M;
        n1 = _N; n2 = M;
        adj.assign(N, vi());
        pairU.resize(_N + 1);
        dist.resize(_N + 1);
        pairV.resize(M + 1);
    }

    void ae(int a, int b){ adj[a].push_back(b); }

    bool bfs(){
        queue<int> q;

        for(int u = 1; u <= n1; u++){
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
                for(int v : adj[u]){
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
            for(int v : adj[u]){
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

    int maxMachine(){
        int result = 0;

        for(int u = 0; u <= n1; u++){
            pairU[u] = 0;
        }
        for(int u = 0; u <= n2; u++){
            pairV[u] = 0;
        }

        while(bfs()){
            for(int u = 1; u <= n1; u++){
                if(!pairU[u] && dfs(u)){
                    result++;
                }
            }
        }
        return result;
    }
};

int n, c1, c2;
int Ma[MAX][MAX], A[MAX][MAX], B[MAX][MAX];

HopcroftKrap hp;

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            char ax;
            cin >> ax;
            if(ax != '.' && ax != 'X')j--;
            Ma[i][j] = ax == 'X';
        }
    }

    c1 = c2 = 1;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Ma[i][j]){
                c1++;
            }
            else{
                A[i][j] = c1;
            }
        }
        c1++;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Ma[j][i]){
                c2++;
            }
            else{
                B[j][i] = c2;
            }
        }
        c2++;
    }

    hp.init(c1, c2);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Ma[i][j]) continue;
            hp.ae(A[i][j], B[i][j]);
        }
    }

    cout << hp.maxMachine() << ENDL;

    return 0;
}