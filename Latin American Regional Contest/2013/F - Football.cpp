#include <bits/stdc++.h>

#define MAX 1000005
#define mod 1000000007
#define INF 1000000000

using namespace std;

typedef long long int ll;
typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    priority_queue <int, vi, greater <int> > Queue;

    int n, m, c = 0;

    cin >> n >> m;

    for(int i = 0; i < n; i++){

        int a, b;

        cin >> a >> b;

        if(a <= b){
            Queue.push(b - a);
        }
        else{
            c += 3;
        }

    }

    while(!Queue.empty() && m){

        int par = Queue.top();
        Queue.pop();

        if(par - m < 0){
            c += 3;
            m -= (par + 1);
        }
        else if(par - m == 0){
            c += 1;
            m = 0;
        }

    }

    while(!Queue.empty()){
        if(Queue.top() == 0){
            c++;
        }
        Queue.pop();
    }

    cout << c << '\n';

    return 0;
}