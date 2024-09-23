#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef vector <ll> vi;

ll base, mod;
int m, q;

vi pot;

ll extGcd(ll a, ll b, ll & x, ll &y){
	if (b == 0){
		x = 1, y = 0;
		return a;
	}
	ll g = extGcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}

ll inv_mod(ll a, ll m){
	ll x, y;
	extGcd(a, m, x, y);
	return (x % m + m ) % m;
}

ll modExp(ll a, ll b, ll m){
	if (b == 0)return 1;
	ll c = modExp(a, b / 2, m);
	c = (c * c) % m;
	if (b % 2 != 0)c = (c * a) % m;
	return c;
}
 
class SegmentTree{

    private:
        int n;
        vi st;
        int left(int v){
            return (v << 1);
        }
        int right(int v){
            return (v << 1) + 1;
        }

        void build(int id, int value, int v, int l, int r){
            if(l == r){
                st[v] = (value * pot[m - id]) % mod;
                return;
            }
            int mid = (l + r) / 2;
            if(id <= mid){
                build(id, value, left(v), l, mid);
            }
            else{
                build(id, value, right(v), mid + 1, r);
            }
            st[v] = (st[left(v)] + st[right(v)]) % mod;
        }
        int query(int sl, int sr, int v, int l, int r){
            if(sl > r || sr < l){
                return 0;
            }
            if(l >= sl && r <= sr){
                return st[v];
            }
            int mid = (l + r) / 2;

            return (query(sl, sr, left(v), l, mid) + query(sl, sr, right(v), mid + 1, r)) % mod;
        }

    public:
        SegmentTree(int N){
            n = N;
            st.assign(4 * (n+1), 0);
        }
        void reasing(int N){
            n = N;
            st.assign(4 * (n+1), 0);
        }
        int query(int l, int r){
            return query(l, r, 1, 0, n);
        }
        void update(int id, int value){
            return build(id, value, 1, 0, n);
        }

};

SegmentTree st(500);

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while(cin >> base >> mod >> m >> q, base != 0){

        st.reasing(m);
        pot.assign(m, 1);

        for(int i = 1; i < m; i++){ //Precalculo de las potencias
            pot[i] = (pot[i - 1] * base) % mod;
        }

        for(int i = 0; i < q; i++){
            string ax;
            int a, b;
            
            cin >> ax >> a >> b;

            if(ax[0] == 'E'){
                st.update(a, b);
            }
            else{
                ll que = (st.query(a, b) * inv_mod(modExp(base, m - b, mod), mod)) % mod;
                cout << que << '\n';
            }

        }

        cout << "-\n";

    }

    return 0;
}