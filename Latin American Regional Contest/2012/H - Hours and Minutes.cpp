#include <bits/stdc++.h>

#define MAX 1000
#define INF 1000000000
#define mod 1000000007

using namespace std;

typedef long long int ll;
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <int> vi;

int main(){

    bool Ans[MAX];

    memset(Ans, false, sizeof(Ans));

    for(int i = 0, h = 0; i < 12; i++){

        for(int j = 0, m = 0; j <= 60; j++, m += 6){

            if(j % 12 == 0 && j != 0){
                h += 6;
            }

            if(m > h){
                Ans[m - h] = true;
            }
            else{
                Ans[h - m] = true;
            }

        }

    }

    int ask;

    while(scanf("%d", &ask) != EOF){
        if(Ans[ask]){
            printf("Y\n");
        }
        else{
            printf("N\n");
        }
    }

    return 0;
}