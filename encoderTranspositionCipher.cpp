#include<bits/stdc++.h>

using namespace std;

signed main(){

    // optei por implementar a cifra por transposição mostrada em sala
    // dado o tamanho da chave adicionamos letras em ordem alfabetica ao final da
    // matriz para assim obter um texto cifrado satisfatorio

    cout << "Insira a chave e o texto a ser cifrado respectivamente:\n";

    vector<bool> alreadyTaken(26, false);

    string k, m, realK; cin >> k >> m;

    // Eu faço o tratamento da chave inserida pelo usuario aqui

    for(auto x : k){

        int val = x - 'a';

        if(val < 0) val = x - 'A';

        if(!alreadyTaken[val]){

            realK.push_back((char)(val + 'a'));
            alreadyTaken[val] = true;
        }
    }

    vector<pair<char, string>> colunms;

    // Agora eu realizo o preenchimento com as letras minusculas em ordem alfabetica

    int iniMSize = m.size();

    for(int i = 0; i < (realK.size() - (iniMSize % realK.size())) % realK.size(); i++){

        m.push_back((char)(i + 'a'));
    } 

    // Agora eu monto minha matriz

    for(int i = 0; i < realK.size(); i++){

        string colunm = "";

        for(int j = i; j < m.size(); j += realK.size()) colunm.push_back(m[j]);

        colunms.push_back({realK[i], colunm});
    }

    sort(colunms.begin(), colunms.end());

    for(auto[key, partC] : colunms) cout << partC;
}