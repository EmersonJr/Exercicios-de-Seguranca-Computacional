#include<bits/stdc++.h>

using namespace std;

signed main(){

    // Apesar de não conseguir encontrar uma forma melhor para solucionar isso, acredito
    // que usar a frequência de digrafos e trigafos é um caminho para a solução em um complexidade melhor
    // a solução atual apresenta uma complexidade de O(nD*div!) (dado nD = número de divisores)
    // além disso a solução atual gera todas as permutações com divisores menores ou iguais a 6
    
    string c; cin >> c;

    for(int i = 2; i <= 6; i++){

        if(c.size() % i) continue;

        string m = "";
        vector<int> seqs;
        vector<string> aux(i, "");

        for(int j = 0; j < i; j++){
            seqs.push_back(j);
        }

        int act = 0;

        for(int z = 0; z < c.size(); z++){

            if(aux[act].size() == c.size() / i) act++;

            aux[act].push_back(c[z]);
        }

        for(int z = 0; z < c.size() / i ;z ++){

            for(auto x : seqs){

                cout << aux[x][z];
            }
        } 

        cout << '\n';
        while (next_permutation(seqs.begin(), seqs.end())){

            for(int z = 0; z < c.size() / i ;z ++){

                for(auto x : seqs){

                    cout << aux[x][z];
                }
            } 


            cout << '\n';
        }
    }
}