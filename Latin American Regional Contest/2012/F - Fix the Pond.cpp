#include <bits/stdc++.h>

#define MAX 605

using namespace std;

int Ma[MAX][MAX];
bool vis[MAX][MAX];
int n;

int M1[] = {-1, 0, 1, 0};
int M2[] = {0, 1, 0, -1};

int a, b, c;

void dfs(int i, int j){

    if(i < 0 || j < 0 || i >= b || j >= a) return;
    if(vis[i][j]) return;

    vis[i][j] = true;

    for(int k = 0; k < 4; k++){
        if(Ma[i][j] & (1 << k)) continue;
        dfs(i + M1[k], j + M2[k]);
    }

}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while(cin >> n){

        int m = (2 * n) - 1;
        memset(Ma, 0, sizeof(Ma));
        memset(vis, false, sizeof(vis));

        for(int i = 0; i < m; i++){
            for(int j = 0, k = (i & 1); j < n; j++, k+=2){
                char aux;{
                    cin >> aux;
                    if(aux == 'H'){
                        Ma[i][k] |= (1 << 2);
                        Ma[i][k+1] |= (1 << 2);
                        Ma[i+1][k] |= (1 << 0);
                        Ma[i+1][k+1] |= (1 << 0);
                    }
                    else if(aux == 'V'){
                        Ma[i][k] |= (1 << 1);
                        Ma[i][k+1] |= (1 << 3);
                        Ma[i+1][k] |= (1 << 1);
                        Ma[i+1][k+1] |= (1 << 3);
                    }
                    else{
                        j--;
                    }
                }
            }
        }

        a = (2 * n) + 1, b = 2 * n, c = 0;

        for(int i = 0; i < b; i++){
            for(int j = 0; j < a; j++){
                if(vis[i][j]) continue;
                c++;
                dfs(i, j);
            }
        }

        /*for(int i = 0; i < b; i++){
            for(int j = 0; j < a; j++){
                cout << Ma[i][j] << " ";
            }
            cout << endl;
        }*/

        cout << c-1 << '\n';

    }

    return 0;
}