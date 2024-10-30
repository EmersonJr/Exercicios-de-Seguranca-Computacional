#include<bits/stdc++.h>

using namespace std;

vector<long double> tabelaFreqs = {
    13.9, 1.0, 4.4, 5.4, 12.2, 1.0, 1.2, 0.8, 6.9, 0.4, 0.1,
    2.8, 4.2, 5.3, 10.8, 2.9, 0.9, 6.9, 7.9, 4.9, 4.0,  1.3,
    0.0, 0.3, 0.0, 0.4
    };

signed main(){

    cout << "Insira um texto cifrado:\n";

    string c, m = ""; cin >> c;

    long double erroRelat = 1000000;

    int k = 0;

    // A partir de então devo gerar todas as chaves e possíveis e adotar
    // a chave com menor erro relativo nas frequencias
    // O algoritmo implementado apresenta complexidade O(25*c.size()) e com isso
    // soluciona para todo texto de tamanho até 1e7 em menos de 5 segundos

    for(int i = 1; i < 26; i++){

        vector<int> cnt(26);
        string possM = "";

        for(auto x : c){

            int val = x - 'a';

            if(val < 0){

                val = x - 'A';

                val = (val - i + 26) % 26;

                possM.push_back((char)(val + 'A'));
                continue;
            }

            val = (val - i + 26) % 26;

            cnt[val]++;

            possM.push_back((char)(val + 'a'));
        }

        long double actErrRelat = 0;

        for(int j = 0; j < 26; j++){
           if(tabelaFreqs[j]) actErrRelat += (long double)((abs((long double)(cnt[j]*100 / (c.size())) - (tabelaFreqs[j]))) / tabelaFreqs[j]);
        }
        
        if(erroRelat > actErrRelat){

            erroRelat = actErrRelat;
            m = possM;
            k = i;
        }
    }

    cout << k << " - > " << m << '\n';

}