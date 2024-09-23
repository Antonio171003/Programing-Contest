#include <bits/stdc++.h>

using namespace std;

int main(){

    int a, b;

    while(scanf("%d %d", &a, &b), a != 0 && b != 0){

        int izq[a], der[a];

        for(int i = 0; i < a; i++){
            izq[i] = i - 1;
            der[i] = i + 1;
        }
        der[a - 1] = -1;

        for(int i = 0; i < b; i++){

            int l, r;

            scanf("%d %d", &l, &r);
            l--; r--;

            if(izq[l] == -1 && der[r] == -1){
                cout << "* *\n";
            }
            else if(izq[l] == -1){
                izq[der[r]] = -1;
                cout << "* " << der[r] + 1 << "\n";
            }
            else if(der[r] == -1){
                der[izq[l]] = -1;
                cout << izq[l] + 1 << " *" << "\n";
            }
            else{
                izq[der[r]] = izq[l];
                der[izq[l]] = der[r];
                cout << izq[l] + 1 << " " << der[r] + 1 << "\n";
            }

        }
        
        cout << "-\n";
    }



    return 0;
}