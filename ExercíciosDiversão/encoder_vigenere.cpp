#include<bits/stdc++.h>
using namespace std;

signed main(){

    string k, s; cin >> k;

    int idx = 0;

    while(cin >> s){

        for(auto x : s){

            int val = x - 'a';

            if(val < 0) val = x - 'A';

            int valK = k[idx] - 'a';

            if(valK < 0) valK = k[idx] - 'A';

            int newLetter = (val + valK) % 26;

            cout << (char)(newLetter + (x - 'a' < 0 ? 'A' : 'a'));

            idx = (idx + 1) % k.size();
        }
    }

    cout << '\n';
}