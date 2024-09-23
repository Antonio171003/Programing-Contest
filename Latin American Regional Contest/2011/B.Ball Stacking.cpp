#include <bits/stdc++.h>

using namespace std;

int Ma[1005][1005];
int sum[1005], best[1005];
int m, Max = 0;

void solve(){
    Max = 0;

    sum[0] = Ma[0][0];
    for(int i = 1; i < m; i++){
        sum[i] = sum[i-1] + Ma[i][0];
    }
    best[m - 1] = sum[m - 1];
    Max = max(Max, best[m - 1]);

    for(int i = m - 2; i >= 0; i--){
        best[i] = max(best[i + 1], sum[i]);
        Max = max(Max, best[i]);
    }

    for(int j = 1; j < m; j++){
        sum[j] = Ma[j][j];
        for(int i = j + 1; i < m; i++){
            sum[i] = sum[i-1] + Ma[i][j];
        }
        best[m - 1] = sum[m - 1] + best[m - 2];
        Max = max(Max, best[m - 1]);

        for(int i = m - 2; i >= j; i--){
            best[i] = max(best[i + 1], sum[i] + best[i - 1]);
            Max = max(Max, best[i]);
        }
    }

}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while(cin >> m){

        if(m == 0) return 0;

        for(int j = 0; j < m; j++){
            for(int k = 0; k <= j; k++){
                cin >> Ma[j][k];
            }
        }

        solve();
        cout << Max << "\n";
    }

    return 0;
}