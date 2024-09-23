#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define fi first
#define se second

typedef long long ll;
typedef vector<int> vi;
typedef pair <int, int> ii;

int n, m;
vector <vi> N, Q;
vi distN, distQ;

void read(int num_edges, vector<vi>& grafo) {
    for (int i = 1; i < num_edges; i++) {
        int a, b; 
        cin >> a >> b;
        a--; b--;
        grafo[a].pb(b);
        grafo[b].pb(a);
    }
}

int bfs(int node, vector<vi> &grafo, vi &dist){

    int vis[grafo.size()];
    memset(vis, -1, sizeof vis);
    queue <int> q;
    q.push(node);
    vis[node] = 0;
    int no = node;

    while (!q.empty()){
        no = q.front();
        q.pop();
        dist[no] = max(dist[no], vis[no]);
        for(int x: grafo[no]){
            if(vis[x] == -1){
                q.push(x);
                vis[x] = vis[no] + 1;
            }
        }
    }
    
    return no;

}

int maxdist(vector<vi> &grafo, vi &dist){

    dist.assign(grafo.size(), 0);

    int a = bfs(0, grafo, dist);
    int b = bfs(a, grafo, dist);
    bfs(b, grafo, dist);

    return dist[b];
}

int centroid(vi &dist){

    int a = 0, i = 0;
    for(int x: dist){
        if(dist[a] > x){
            a = i;
        }
        i++;
    }

    return a;
}

ii join(){
    return ii(centroid(distN), centroid(distQ));
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    N.resize(n);
    Q.resize(m);

    read(n, N);
    read(m, Q);

    int a = maxdist(N, distN);
    int b = maxdist(Q, distQ);
    ii j = join();
    ll maxi = max(max(a, b), distN[j.fi] + distQ[j.se] + 1);
    ll res = 0;

    sort(distQ.begin(), distQ.end());
    ll sum[m]; sum[0] = distQ[0];

    for(int i = 1; i < m; i++){
        sum[i] = sum[i - 1] + distQ[i];
    }

    for(int i = 0; i < n; i++){
        int se = (maxi - distN[i] - 1);
        int bs = (lower_bound(distQ.begin(), distQ.end(), se) - distQ.begin()) - 1;
        
        if(bs >= 0){
            res += maxi * (bs + 1);
            res += sum[m - 1] - sum[bs];
            res += ((m - bs - 1) * (distN[i] + 1));
        }
        else{
            res += sum[m - 1];
            res += (m * (distN[i] + 1));
        }
        
    }

    double ans = (double)res / (double)(n * m);
    cout << fixed << setprecision(3);
    cout << ans << '\n';

    return 0;
}
