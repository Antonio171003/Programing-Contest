#include <bits/stdc++.h>

#define MAX 1000
#define INF 1000000000
#define mod 1000000007

using namespace std;

typedef long long int ll;
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <int> vi;

typedef struct{

    char ca;
    int count;
    vi sons;

}node;

vector <node> pre;
int sum = 0;

void add(int n, string cad, int p){

    pre[n].count++;
    if(p >= cad.length()) return;

    int l = (int) pre[n].sons.size();

    for(int i = 0; i < l; i++){
        char v = pre[pre[n].sons[i]].ca;
        if(v == cad[p]){
            add(pre[n].sons[i], cad, p + 1);
            return;
        }
    }
    node no;
    no.ca = cad[p]; no.count = 0;
    pre.push_back(no);
    pre[n].sons.push_back(pre.size() - 1);
    add(pre[n].sons[l], cad, p+1);
}

void check(int cad, int n){

    if(cad != pre[n].count){
        sum += pre[n].count;
        cad = pre[n].count;
    }

    if(cad == 1){
        return;
    }

    int l = (int) pre[n].sons.size();
    for(int i = 0; i < l; i++){
        check(cad, pre[n].sons[i]);
    }

}

int main(){

    int n;

    while(scanf("%d", &n) != EOF){

        node nod = {'-', 0, vi()};
        sum = 0;
        pre.assign(1, nod);

        string cadena;

        for(int i = 0; i < n; i++){
            cin >> cadena;
            add(0, cadena, 0);
        }

        int num = pre[0].sons.size();

        for(int i = 0; i < num; i++){
            check(n * 2, pre[0].sons[i]);
        }

        double ans = sum / (n * 1.0);

        printf("%.2f\n", ans);

    }

    return 0;
}