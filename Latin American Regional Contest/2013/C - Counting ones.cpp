#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll num_bit[70];

void preprocess(){
    for(int i = 0; i < 64; i++){
        num_bit[i] = (((1LL << i) / 2) * i) + 1;
    }
}

ll num_bits(ll n){

    ll num_b = 0;
    ll uno = 0;

    for(int i = 63; i >= 0; i--){

        if(n & (1LL << i)){
            num_b += num_bit[i];
            num_b += (uno * (1LL << i));
            uno++;
        }

    }

    return num_b;

}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    preprocess();

    ll a, b;

    cin >> a >> b;

    ll ans = 0;

    ans = num_bits(b) - num_bits(a - 1);
    
    cout << ans << '\n';

    return 0;
}