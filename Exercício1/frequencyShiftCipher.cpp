#include<bits/stdc++.h>

using namespace std;

vector<long double> tabelaFreqs = {
    13.9, 1.0, 4.4, 5.4, 12.2, 1.0, 1.2, 0.8, 6.9, 0.4, 0.1,
    2.8, 4.2, 5.3, 10.8, 2.9, 0.9, 6.9, 7.9, 4.9, 4.0,  1.3,
    0.0, 0.3, 0.0, 0.4
};

vector<int> letters = {
    0, 4, 14
};

signed main(){

    cout << "Insira um texto cifrado:\n";

    string c, m = ""; cin >> c;

    long double erroRelat = 1000000;

    int k = 0;

    // eu tento parear as três letras de maiores frequências do alfabeto português com as três letras de maior
    // frequencia no texto cifrado, mantendo como resposta aquela que apresenta o menor erro relativo
    // isso gera a resposta com uma complexidade de O(9*c.size())
    
    vector<pair<int, int>> cnt(26);
    vector<long double> freqsCipher(26);

    for(int i = 0; i < 26; i++) cnt[i] = {0, i}; 

    for(auto x : c){

        int val = x - 'a';

            if(val < 0){

                val = x - 'A';
            }
        
        cnt[val].first++;
    }

    for(int i = 0; i < 26; i++){
        freqsCipher[i] = (long double)(cnt[i].first*100) / (long double)(c.size());
    }
    sort(cnt.begin(), cnt.end(), greater<pair<int, int>>());

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){

            int posK = abs(cnt[j].second - letters[i]);

            long double actErrRelat = 0;

            for(int z = 0; z < 26; z++){
                if(tabelaFreqs[z]) actErrRelat += (long double)((abs((long double)(freqsCipher[(z + posK) % 26]) - (tabelaFreqs[z]))) / tabelaFreqs[z]);
            }

            if(actErrRelat < erroRelat){

                erroRelat = actErrRelat;
                k = posK;
                m = "";

                for(auto x : c){

                    int val = x - 'a';

                    if(val < 0){

                        val = x - 'A';

                        val = (val - posK + 26) % 26;

                        m.push_back((char)(val + 'A'));
                        continue;
                    }

                    val = (val - posK + 26) % 26;

                    m.push_back((char)(val + 'a'));
                }
            }
        }
    }
    cout << k << " - > " << m << '\n';

}