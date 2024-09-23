#include <bits/stdc++.h>

#define MAX_N 1005

using namespace std;

typedef vector <int> vi;

vector <vi> AdjList;

int dp[MAX_N][MAX_N];
int ans = 0;
int nodes, edges;

void solve(){

    for(int i = 0; i < nodes; i++){

        for(int j = i; j < nodes; j++){

            dp[i][j] = 0;
            dp[j][i] = 0;

            if(i == j){
                continue;
            }

            for(int k = 0; k < (int)AdjList[j].size(); k++){
                int v = AdjList[j][k];
                if(dp[i][v] || v == 0){
                    dp[i][j] = 1;
                    dp[j][i] = 1;
                    ans++;
                    break;
                }

            }

        }

    }

}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> nodes >> edges;

    AdjList.assign(nodes, vi());

    for(int i = 0; i < edges; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        AdjList[b].push_back(a);
    }

    solve();

    cout << ans << '\n';

    return 0;
}