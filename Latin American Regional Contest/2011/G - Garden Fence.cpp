#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 1e9
#define pb push_back
#define L(N) N<<1
#define R(N) (N<<1) + 1

typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ii, ll> iii;

struct node{
	int x, y, v, c;
};

bool above(const node &n){
	return n.y > 0 || (n.y == 0 && n.x > 0);
}

ll cross(const node &n1, const node &n2){
	return 1ll * n1.x * n2.y - 1ll * n1.y * n2.x;
}

bool cmp(const node &n, const node &n1){
	ll cr = cross(n, n1);
	if (!above(n)) cr = -cr;
	if (!above(n1)) cr = -cr;
	return cr > 0;
}


node ns[2 * MAXN];
vector<node> chsn;

int N;

int solve(int c){
	sort(chsn.begin(), chsn.end(), cmp);

	int ans, cur = 0;
	for(int i = 0; i < N - 1; i++){
		auto &n = chsn[i];
		if (above(n) && n.c != c) cur += n.v;
		else if (!above(n) && n.c == c) cur += n.v;
	}

	ans = cur;
	
	int j = 0;
	for (int i = 0; i < N - 1; i = j){ 
		j = i;
		while (j < N - 1 && cross(chsn[j], chsn[i]) == 0){
			//Mientras j este dentro del rango y los vestores sean coolineales
			auto &n = chsn[j];
			if (above(n)) cur += n.c == c ? n.v : -n.v;
			else cur += n.c == c ? -n.v : n.v;
			++j;
		}
		ans = min(ans, cur);
	}

	return ans;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

	int P, L, x, y, v, c;
	while (cin >> P >> L){ //P - pinos // L - larches
        if(P == 0) break;
		for(int i = 0; i < P; i++){
            cin >> x >> y >> v;
			ns[i] = {x, y, v, 0}; 
		} // 0 - Pino, 1 - Larche
		for(int i = 0; i < L; i++){
			cin >> x >> y >> v;
			ns[i + P] = {x, y, v, 1};
		}
		N = P + L; //Numero de Arboles
		int ans = INF;
		for(int i = 0; i < N; i++){
			x = ns[i].x, y = ns[i].y;
			chsn.clear();
			for(int j = 0; j < N; j++){
				if (i == j) continue;
				chsn.pb({ns[j].x - x, ns[j].y - y, ns[j].v, ns[j].c});
			}
			ans = min(ans, min(solve(0), solve(1)));
		}

		cout << ans << endl;
	}
    return 0;
}