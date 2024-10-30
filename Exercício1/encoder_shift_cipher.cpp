#include<bits/stdc++.h>

using namespace std;

signed main(){

    int k; cin >> k;

    // a cifra de deslocamento deve contar com um inteiro K (a quantidade de deslocamentos a serem aplicados na letra)
    // Além disso sendo o texto cifrado, C = c[i] e o plaintext, M = m[i], temos c[i] = (m[i] + k) % 26;
    // O meu texto cifrado mantém as cases usadas no plaintext, então é possível usar camel case para separar as palavras

    string text, newTxt = ""; cin >> text;

    for(auto x : text){

        int val = (x - 'a' < 0 ? x - 'A' : x - 'a');

        val = (val + k) % 26;

        newTxt.push_back((char)(x - 'a' < 0 ? val + 'A' : val + 'a'));
    }
     
    cout << newTxt << '\n';

    return 0;
}