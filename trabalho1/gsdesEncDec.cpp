#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

string key = "1010000010", plainTxt = "11010111", cypherTxt = "10101000";
vector<string> roundKeys;

int binStrToInt(string binStr) {

    int aux = 0, pot2 = 1;

    for(int i = binStr.size()-1; i > -1; i--){

        char x = binStr[i];

        if(x == '1') aux += pot2;

        pot2 *= 2;
    }

    return aux;
}

string intToBinStr8(int num) {

    string binStr = "";

    while(binStr.size() != 8){

        binStr.push_back((char)((num % 2) + '0'));

        num /= 2;
    }

    reverse(binStr.begin(), binStr.end());
    
    return binStr;
}

string intToBinStr2(int num) {

    string binStr = "";

    while(binStr.size() != 2){

        binStr.push_back((char)((num % 2) + '0'));

        num /= 2;
    }

    reverse(binStr.begin(), binStr.end());

    return binStr;
}

string intToBinStr4(int num) {

    string binStr = "";

    while(binStr.size() != 4){

        binStr.push_back((char)((num % 2) + '0'));

        num /= 2;
    }

    reverse(binStr.begin(), binStr.end());
    
    return binStr;
}

string permutRoundKey(string genKey) {

    string roundKey = "";
    for(int idx = 1; idx <= 8; idx++) {

        switch(idx) {
            case 1 :
                roundKey.push_back(genKey[5]);
                break;
            case 2 :
                roundKey.push_back(genKey[2]);
                break;
            case 3 :
                roundKey.push_back(genKey[6]);
                break;
            case 4 :
                roundKey.push_back(genKey[3]);
                break;
            case 5 :
                roundKey.push_back(genKey[7]);
                break;
            case 6 :
                roundKey.push_back(genKey[4]);
                break;
            case 7 :
                roundKey.push_back(genKey[9]);
                break;
            default:
                roundKey.push_back(genKey[8]);
                break;
        }
    }
    return roundKey;
}

void shiftKey(string &k) {

    char actLetter = k[4];

    for(int i = 3; i > -1; i--) {

        swap(k[i], actLetter);
    }

    k[4] = actLetter;

    actLetter = k[9];

    for(int i = 8; i > 4; i--) {

        swap(k[i], actLetter);
    }

    k[9] = actLetter;
}
vector<string> genRoundKey(bool decrypt = false, string k = key) {

    cout << "Gerando chave -> \n";

    string permKey = "";

    vector<string> roundsKeys(2, "");

    cout << "Chave: " << key << '\n';

    for(int idx = 1; idx <= 10; idx++) {

        switch(idx) {
            case 1 :
                permKey.push_back(k[2]);
                break;
            case 2 :
                permKey.push_back(k[4]);
                break;
            case 3 :
                permKey.push_back(k[1]);
                break;
            case 4 :
                permKey.push_back(k[6]);
                break;
            case 5 :
                permKey.push_back(k[3]);
                break;
            case 6 :
                permKey.push_back(k[9]);
                break;
            case 7 :
                permKey.push_back(k[0]);
                break;
            case 8 :
                permKey.push_back(k[8]);
                break;
            case 9 :
                permKey.push_back(k[7]);
                break;
            default:
                permKey.push_back(k[5]);
                break;
        }
    }

    cout << "Chave permutada: " << permKey << '\n';
    shiftKey(permKey);
    cout << "Chave pós shift: " << permKey << '\n';
    roundsKeys[0] = permutRoundKey(permKey);
    cout << "Subchave 1: " << roundsKeys[0] << '\n';
    shiftKey(permKey);
    shiftKey(permKey);
    cout << "Chave pós 2 shift's: " << permKey << '\n';
    roundsKeys[1] = permutRoundKey(permKey);
    cout << "Subchave 2: " << roundsKeys[1] << '\n';

    if(decrypt){
        reverse(roundsKeys.begin(), roundsKeys.end());

        // se estiver decriptando basta inverter as chaves e realizar
        // o restante do algoritmo da mesma maneira que a encriptação

        cout << "Subchave 0 Decriptação: " << roundsKeys[0] << '\n';
        cout << "Subchave 1 Decriptação: " << roundsKeys[1] << '\n';
    }

    cout << "--------------\n";

    return roundsKeys;
}
string expand(string bt) {

    string btExpanded = "";
    for(int idx = 1; idx <= 8; idx++) {

        switch(idx) {
            case 1 :
                btExpanded.push_back(bt[3]);
                break;
            case 2 :
                btExpanded.push_back(bt[0]);
                break;
            case 3 :
                btExpanded.push_back(bt[1]);
                break;
            case 4 :
                btExpanded.push_back(bt[2]);
                break;
            case 5 :
                btExpanded.push_back(bt[1]);
                break;
            case 6 :
                btExpanded.push_back(bt[2]);
                break;
            case 7 :
                btExpanded.push_back(bt[3]);
                break;
            default:
                btExpanded.push_back(bt[0]);
                break;
        }
    }
    return btExpanded;
}
int roundFunc(string roundKey, string r) {

    cout << "Funcao F ->\n";
    r = expand(r);
    cout << "r expandido: " << r << '\n';

    vector<vector<int>> s0 = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };

    vector<vector<int>> s1 = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3},
    };

    vector<vector<int>> idxs(2, vector<int>(4));

    for(int i = 0; i < 8; i++) {

        int aux = (r[i] - '0') ^ (roundKey[i] - '0');

        idxs[i / 4][i % 4] = aux;
    }

    cout << "Matrix XOR subchave e r expandido: " << '\n';

    for(auto x : idxs){

        for(auto y : x){

            cout << y << " ";
        }

        cout << '\n';
    }

    string resultPart1 = "";

    resultPart1 += intToBinStr2(s0[idxs[0][0]*2 + idxs[0][3]][idxs[0][1]*2 + idxs[0][2]]);
    resultPart1 += intToBinStr2(s1[idxs[1][0]*2 + idxs[1][3]][idxs[1][1]*2 + idxs[1][2]]);

    cout << "S0: " << resultPart1[0] << resultPart1[1] << '\n';
    cout << "S1: " << resultPart1[2] << resultPart1[3] << '\n';

    string result = "";
    result.push_back(resultPart1[1]);
    result.push_back(resultPart1[3]);
    result.push_back(resultPart1[2]);
    result.push_back(resultPart1[0]);

    cout << "Resultado funcao F: " << result << '\n';
    cout << "--------------\n";
    return binStrToInt(result);
}


string iniPerm(string plainTxt) {

    cout << "Permutando o texto com IP ->\n";
    cout << "Texto: " << plainTxt << '\n';
    string permPlnTxt = "";
    for(int idx = 1; idx <= 8; idx++) {

        switch(idx) {
            case 1 :
                permPlnTxt.push_back(plainTxt[1]);
                break;
            case 2 :
                permPlnTxt.push_back(plainTxt[5]);
                break;
            case 3 :
                permPlnTxt.push_back(plainTxt[2]);
                break;
            case 4 :
                permPlnTxt.push_back(plainTxt[0]);
                break;
            case 5 :
                permPlnTxt.push_back(plainTxt[3]);
                break;
            case 6 :
                permPlnTxt.push_back(plainTxt[7]);
                break;
            case 7 :
                permPlnTxt.push_back(plainTxt[4]);
                break;
            default:
                permPlnTxt.push_back(plainTxt[6]);
                break;
        }
    }

    cout << "Texto Permutado: " << permPlnTxt << '\n';
    cout << "--------------\n";
    return permPlnTxt;
}

string finalPerm(string cypherText) {

    cout << "Permutando o texto com IP(inv) ->\n";
    cout << "Texto: " << cypherText << '\n';

    string permCypherTxt = "";
    for(int idx = 1; idx <= 8; idx++) {

        switch(idx) {
            case 1 :
                permCypherTxt.push_back(cypherText[3]);
                break;
            case 2 :
                permCypherTxt.push_back(cypherText[0]);
                break;
            case 3 :
                permCypherTxt.push_back(cypherText[2]);
                break;
            case 4 :
                permCypherTxt.push_back(cypherText[4]);
                break;
            case 5 :
                permCypherTxt.push_back(cypherText[6]);
                break;
            case 6 :
                permCypherTxt.push_back(cypherText[1]);
                break;
            case 7 :
                permCypherTxt.push_back(cypherText[7]);
                break;
            default:
                permCypherTxt.push_back(cypherText[5]);
                break;
        }
    }
    cout << "Texto Permutado: " << permCypherTxt << '\n';
    cout << "--------------\n";
    return permCypherTxt;
}

string desAlgo(string plainTxt) {

    string l = "", r = "";

    for(int i = 0; i < 4; i++) l.push_back(plainTxt[i]);
    for(int i = 4; i < 8; i++) r.push_back(plainTxt[i]);

    for(int i = 0; i < 2; i++) {

        cout << "Round " << i+1 << " ->\n";
        cout << "l: " << l << " r: " << r << '\n';
        cout << "--------------\n";

        int resFunc = roundFunc(roundKeys[i], r);

        int li = binStrToInt(l);

        l = intToBinStr4(li ^ resFunc);

        cout << "Novo l: " << l << '\n';

        if(!i) swap(l, r);

        cout << "proximo l: " << l << " proximo r: " << r << '\n';
        cout << "--------------\n";
    }

    return l+r;
}

void genAllKeys() {

    for(int i = 0; i < (1 << 10); i++){
        for(int j = 0; j < 10; j++){

            key[j] = ((i & (1 << j)) ? 1 : 0) + '0';
        }
        roundKeys = genRoundKey(true);
        cout << "Chave: " << key << " " << "Texto em Claro: " << finalPerm(desAlgo(iniPerm(cypherTxt))) << '\n';
    }
}

void decrypt(){

    string padrao;
    do{

        cout << "Deseja utilizar os valores padrões do projeto? [Y/N] ";
        cin >> padrao;

        if(padrao == "Y"){

            string respAns;

            do{

                cout << "Gerar todas as chaves? [Y/N] ";
                cin >> respAns;
            }while(respAns != "Y" && respAns != "N");

            if(respAns == "Y") {

                genAllKeys();
                return;
            }

            cout << "--------------\n";
            roundKeys = genRoundKey(true);
            cout << "Decriptando ->\n " << finalPerm(desAlgo(iniPerm(cypherTxt))) << '\n';
            return;
        }

    }while(padrao != "Y" && padrao != "N");

    cout << "Insira o texto cifrado: ";
    cin >> cypherTxt;
    string respAns;

    do{

        cout << "Voce tem acesso a chave? [Y/N] ";
        cin >> respAns;
    }while(respAns != "Y" && respAns != "N");

    if(respAns == "N") {

        genAllKeys();
        return;
    }

    cout << "Insira a chave: ";

    cin >> key;

    roundKeys = genRoundKey(true);

    cout << "Texto em claro: " << finalPerm(desAlgo(iniPerm(cypherTxt))) << '\n';
}

void encrypt() {

    string padrao;

    do{

        cout << "Deseja utilizar os valores padrões do projeto? [Y/N] ";
        cin >> padrao;

        if(padrao == "Y"){

            cout << "--------------\n";
            roundKeys = genRoundKey();
            cout << "Encriptando ->\n " << finalPerm(desAlgo(iniPerm(plainTxt))) << '\n';
            return;
        }

    }while(padrao != "Y" && padrao != "N");
    cout << "Insira a chave: ";

    cin >> key;

    cout << "Insira o texto em claro: ";

    cin >> plainTxt;

    cout << "--------------\n";
    roundKeys = genRoundKey();
    cout << "Encriptando ->\n " << finalPerm(desAlgo(iniPerm(plainTxt))) << '\n';
}
signed main() {

    string personInput;

    do{
        cout << "Voce quer decriptar ou encriptar? [D/E] ";

        cin >> personInput;

        if (personInput == "D") decrypt();
        else if (personInput == "E") encrypt();
    }while(personInput != "QUIT");

    
}