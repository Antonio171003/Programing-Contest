#include <bits/stdc++.h>

#define MAX 1000
#define INF 1000000000
#define mod 1000000007

using namespace std;

typedef long long int ll;
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <int> vi;

int n, m, ans = 0, camino = 0;

vector <vii> AdjList;
vector <bool> f;

bool bfs(int nodo){

    int take = 0;
    bool aux = false;

    for(int i = 0; i < (int)AdjList[nodo].size(); i++){

        ii v = AdjList[nodo][i];

        if(bfs(v.first)){
            camino += v.second;
            if(camino > take){
                ans += take;
                take = camino;
                camino = 0;
                aux = true;
            }
            else{
                ans += camino;
            }
        }

    }

    if(aux || f[nodo]){
        camino = take;
        return true;
    }

    return false;

}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    AdjList.assign(n, vii());
    f.assign(n, false);

    for(int i = 1; i < n; i++){

        int a, b, c;

        cin >> a >> b >> c;

        a--; b--;

        AdjList[a].push_back(ii(b, c));

    }

    for(int i = 0; i < m; i++){
        int a;
        cin >> a;
        a--;
        f[a] = true;
    }

    bool ax = bfs(0);

    cout << ans << '\n';

    return 0;
}