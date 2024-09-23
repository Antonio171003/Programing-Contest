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

    ios::sync_with_stdio(0);
    cin.tie(0);

    int a, b, c, d, e, A, B, C, D, E;

    while(cin >> a >> b >> c >> d >> e){

        cin >> A >> B >> C >> D >> E;

        if(A == a || B == b || C == c || D == d || E == e){
            cout << "N\n";
        }
        else{
            cout << "Y\n";
        }

    }

    return 0;
}