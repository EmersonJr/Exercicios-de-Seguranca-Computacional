#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

bool needKey = false;

string key = "1010000010", cypherTxt;

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
vector<string> genRoundKey(string k = key) {

    string permKey = "";

    vector<string> roundsKeys(2, "");

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

    shiftKey(permKey);
    roundsKeys[1] = permutRoundKey(permKey);
    shiftKey(permKey);
    shiftKey(permKey);
    roundsKeys[0] = permutRoundKey(permKey);

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

    r = expand(r);


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

    vector<vector<int>> idxs(4, vector<int>(4));

    for(int i = 0; i < 8; i++) {

        int aux = (r[i] - '0') ^ (roundKey[i] - '0');

        idxs[i / 4][i % 4] = aux;
    }

    string resultPart1 = "";

    resultPart1 += intToBinStr2(s0[idxs[0][0]*2 + idxs[0][3]][idxs[0][1]*2 + idxs[0][2]]);
    resultPart1 += intToBinStr2(s1[idxs[1][0]*2 + idxs[1][3]][idxs[1][1]*2 + idxs[1][2]]);


    string result = "";
    result.push_back(resultPart1[1]);
    result.push_back(resultPart1[3]);
    result.push_back(resultPart1[2]);
    result.push_back(resultPart1[0]);

    return binStrToInt(result);
}

string iniPerm(string plainTxt) {

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
    return permPlnTxt;
}

string finalPerm(string cypherText) {

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
    return permCypherTxt;
}

string desAlgo(string plainTxt) {

    string l = "", r = "";

    for(int i = 0; i < 4; i++) l.push_back(plainTxt[i]);
    for(int i = 4; i < 8; i++) r.push_back(plainTxt[i]);

    vector<string> roundKeys = genRoundKey();

    for(int i = 0; i < 2; i++) {

        int resFunc = roundFunc(roundKeys[i], r);

        int li = binStrToInt(l);

        l = intToBinStr4(li ^ resFunc);

        if(!i) swap(l, r);
    }

    return l+r;
}

void genAllKeys() {

    for(int i = 0; i < (1 << 10); i++){
        for(int j = 0; j < 10; j++){

            key[j] = ((i & (1 << j)) ? 1 : 0) + '0';
        }
        cout << "Chave: " << key << " " << "Texto em Claro: " << finalPerm(desAlgo(iniPerm(cypherTxt))) << '\n';
    }

}
int main() {

    cin >> cypherTxt;

    if(!needKey) {

        genAllKeys();
        return 0;
    }

    cout << finalPerm(desAlgo(iniPerm(cypherTxt))) << '\n';
}