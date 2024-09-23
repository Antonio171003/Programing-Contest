#include <bits/stdc++.h>

using namespace std;

typedef vector <int> vi;

class SegmentTree{

    private:
        int n, neutral;
        vi st;
        int left(int v) {return (v << 1);}
        int right(int v){return (v << 1) + 1;}

        void update(int id, int value, int v, int l, int r){

            if(l == r){
                st[v] = value;
                return;
            }

            int m = (l + r) / 2;
            if(id <= m){
                update(id, value, left(v), l, m);
            }
            else{
                update(id, value, right(v), m + 1, r);
            }
            st[v] = st[left(v)] * st[right(v)];
        }
        int query(int sl, int sr, int v, int l, int r){

            if(sl > r || sr < l){
                return neutral;
            }
            if(l >= sl && r <= sr){
                return st[v];
            }
            int m = (l + r) / 2;
            return query(sl, sr, left(v), l, m) * query(sl, sr, right(v), m + 1, r);
        }

    public:

        SegmentTree(int N){
            n = N;
            neutral = 1;
            st.assign(n * 4, neutral);
        }
        void reset(int N){
            n = N;
            st.assign(n * 4, neutral);
        }
        int query(int l, int r){
            return query(l, r, 1, 1, n);
        }
        void update(int id, int value){
            update(id, value, 1, 1, n);
        }

};

SegmentTree st(1);

int signo(int n){

    if(n > 0) return 1;
    if(n < 0) return -1;
    return 0;
}

void Print(int n){

    if(n == 0){
        cout << "0";
    }
    else if(n > 0){
        cout << "+";
    }
    else{
        cout << "-";
    }
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q;

    while(cin >> n >> q){

        st.reset(n);

        for(int i = 1; i <= n; i++){
            int aux;
            cin >> aux;
            st.update(i, signo(aux));
        }

        for(int i = 0; i < q; i++){

            string op;
            int a, b;
            cin >> op >> a >> b;
            if(op[0] == 'C'){
                st.update(a, signo(b));
            }
            else{
                Print(st.query(a, b));
            }

        }

        cout << '\n';

    }

}