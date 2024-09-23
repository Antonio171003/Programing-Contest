#include <bits/stdc++.h>

using namespace std;

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int a, b, c;

    while(cin >> a >> b >> c){ //Is the best hand

        if(a == 0 || b == 0 || c == 0) break;

        if(a == 13 && b == 13 && c == 13){
            cout << "*\n";
            continue;
        }

        if(a == b && b == c){ //Is a set
            a++;
            cout << a << " " << a << " " << a << '\n';
            continue;
        }

        if(a == b || a == c || b == c){ //Is a pair
            
            int king = 0;

            king += a == 13? 1 : 0;
            king += b == 13? 1 : 0;
            king += c == 13? 1 : 0;

            if(king == 1){ //Is a pair with king, always win a pair+1 and A
                if(a == 13){
                    b++;
                    cout << "1 " << b << " " << b << '\n';
                }
                else{
                    a++;
                    cout << "1 " << a << " " << a << '\n';
                }
                continue;
            }
            else if(king == 2){ //K's pair

                int other = a;
                if(other == b) other = c;
                else if(other == c) other = b;

                if(other == 12){ //The other card is Q, only win a set
                    cout << "1 1 1\n";
                }
                else{
                    other++;
                    cout << other << " 13 13\n";
                }
                continue;
            }
            else{ //Is a simple pair, win the same pair and other card+1
                int other = a, pair = b;
                if(other == b) other = c;
                else if(other == c){
                    other = b;
                    pair = c;
                }
                other++;
                if(other == pair){
                    other++;
                }
                if(other > pair){
                    cout << pair << " " << pair << " " << other << '\n';
                }
                else{
                    cout << other << " " << pair << " " << pair << '\n';
                }
            }
            continue;
        }

        //No hand, always win 1 1 2

        cout << "1 1 2\n";

    }

    return 0;
}
