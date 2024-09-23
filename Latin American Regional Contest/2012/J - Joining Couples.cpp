#include <bits/stdc++.h>

#define LOG 20
#define MAXN 100005

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vi depth, uf, normal, cicle;
vector <vi> Tree, up;
map <int, int> mp; //Tamaño de cada ciclo
int n;

int father(int x){
    if(uf[x] == x) return x;
    return uf[x] = father(uf[x]);
}

void dfs_cicle(int u, int p){

    cicle[u] = p;

    if(cicle[normal[u]] > 0){
        mp[father(u)] = p;
        return;
    }

    dfs_cicle(normal[u], p+1);
}

void dfs(int a, int ans){

    depth[a] = depth[ans] + 1;
    up[a][0] = ans;

    for(int i = 1; i < LOG; i++){
        if(up[a][i - 1] != -1)
            up[a][i] = up[up[a][i - 1]][i - 1];
    }

    for(int i = 0; i < (int) Tree[a].size(); i++){
        int v = Tree[a][i];
        if(cicle[v] == -1)
            dfs(v, a);
    }

}

int move(int a, int k){
    for(int i = LOG -1; k > 0; i--){
        if(k & (1 << i)){
            a = up[a][i];
            k -= (1 << i);
        }
    }
    return a;
}

int dist_lca(int a, int b){
    if(depth[a] < depth[b]){
        swap(a, b);
    }
    int k = depth[a] - depth[b];
    a = move(a, k);

    if(a == b){
        return k;
    }

    int fa = move(a, depth[a]), fb = move(b, depth[b]);
    if(fa != fb){
        return k + depth[a] + depth[b] + min(abs(cicle[fa] - cicle[fb]), mp[father(a)] - abs(cicle[fa] - cicle[fb]));
    }


    fa = depth[a]; fb = depth[b];

    for(int i = LOG - 1; i >= 0; i--){
        if(up[a][i] != up[b][i]){
            a = up[a][i];
            b = up[b][i];
        }
    }

    return (k + fa + fb) - (2 * depth[up[a][0]]);

}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while(cin >> n){

        depth.assign(n, -1);
        uf.assign(n, 0);
        cicle.assign(n, -1);
        normal.reserve(n);
        Tree.assign(n, vi());
        up.assign(n, vi(LOG, -1));

        //cout << "| " << n << " |\n";

        for(int i = 0; i < n; i++){ //Inicializar union find
            uf[i] = i;
        }

        for(int i = 0; i < n; i++){
            int v;
            cin >> v;
            v--;
            normal[i] = v;
            Tree[v].push_back(i);
            if(father(v) != i){ //I Siempre sera su padre
                uf[i] = father(v);
            }
            else{ //Mismo conjunto hay ciclo
                cicle[i] = 0;
            }
        }

        for(int i = 0; i < n; i++){
            if(cicle[i] == 0){ //Exploracion de ciclo
                dfs_cicle(i, 1);
            }
        }
        for(int i = 0; i < n; i++){
            if(cicle[i] != -1){//Exploracion del subarbol
                dfs(i, i);
            }
        }

        int q;

        cin >> q;

        for(int i = 0; i < q; i++){
            int u, k;
            cin >> u >> k;
            u--; k--;

            if(father(u) != father(k)){ //Diferentes conjuntos
                cout << -1 << "\n";     //No hay camino
                continue;
            }
            else{
                cout << dist_lca(u, k) << "\n";
            }

        }

    }

    return 0;
}