#include <bits/stdc++.h>

#define MAX 5005

using namespace std;

int Rank[MAX];

bool repeat(int n){

    if(n <= 10){
        return false;
    }
    if(n < 100){
        return (n % 11) == 0;
    }
    if(n < 1000){

        int a = n % 10;
        n /= 10;
        int b = n % 10;
        n /= 10;
        int c = n % 10;
        return (a == b || a == c || b == c);
    }
    else{

        int a = n % 10;
        n /= 10;
        int b = n % 10;
        n /= 10;
        int c = n % 10;
        n /= 10;
        int d = n % 10;
        return (a == b || a == c || a == d || b == c || b == d || c == d);
    }

}

void solve(){

    Rank[0] = 0;

    for(int i = 1; i < MAX; i++){

        if(repeat(i)){
            Rank[i] = Rank[i - 1];
        }
        else{
            Rank[i] = Rank[i - 1] + 1;
        }       

    }

}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int l, r;

    solve();

    while(cin >> l >> r){
        cout << Rank[r] - Rank[l - 1] << '\n';
    }

    return 0;
}