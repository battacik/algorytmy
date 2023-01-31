//WYSZUKIWANIE WZORCA
#include <iostream>
#include <math.h>
using namespace std;

void naiveStringMatching(string T, string p)
{
    int i;
    for (int s = 0; s <= T.size() - p.size(); s++) {
        i = 0;
        while (i < p.size() && T[i + s] == p[i])
            i++;
        if (i == p.size())
            cout << "przesuniecie: " << s << endl;
    }
}

void rabinKarp(string T, string p){

    int hp = 0, ht = 0;
    int j = p.size() - 1;
    bool match;

    for (int i = 0; i < p.size(); i++) {     //obliczenie pierwszego haszu dla wzorca
        hp = hp + pow(2, j) * p[i];
        j--;
    }

    j = p.size() - 1;
    for (int i = 0; i < p.size(); i++) {     //obliczenie pierwszego haszu dla tekstu
        ht = ht + pow(2, j) * T[i];
        j--;
    }

    for (int s = 0; s <= T.size() - p.size(); s++) { //przeszukiwanie kolejnych wartoœci
        if (hp == ht) {
            match = true;
            for (int i = 0; i < p.size(); i++) {
                if (p[i] != T[s + i]) {
                    match = false;
                    break;
                }
            }
            if (match == true)
                cout << "przesuniecie: " << s << endl;
        }
        ht = (ht - T[s] * pow(2, p.size() - 1)) * 2 + T[s + p.size()];
    }
}

void boyerMoore(string T, string p) {
    int s = 0;
    int bc[256]; // tyle ile znaków ASCII
    int j = p.size() - 1;

    for (int i = 0; i < 256; i++)
        bc[i] = -1;

    for (int i = 0; i < p.size() - 1; i++)
        bc[p[i]] = i;

    while (s <= T.size() - p.size()) {
        j = p.size() - 1;
        while (j >= 0 && p[j] == T[s + j])
            j--;

        if (j == -1) {
            cout << "przesuniecie: " << s << endl;
            s++;
        }
        else {
            if (bc[T[s + j]] == -1) //znak T[s+1] nie wystêpuje w P
                s = s + j + 1;
            else if (bc[T[s + j]] < j) //wystêpuje na pozycji k (k<j), wtedy przesuniêcie o i-k ¿eby wyrównaæ
                s = s + j - bc[T[s + j]];
            else //jeœli ¿aden z poprzednich - przesuniêcie o 1 w prawo
                s++;
        }
    }
}

int main()
{
    string text = "abacbacccba";
    string pattern = "cba";

    naiveStringMatching(text, pattern);
    rabinKarp(text, pattern);
    boyerMoore(text, pattern);

}
