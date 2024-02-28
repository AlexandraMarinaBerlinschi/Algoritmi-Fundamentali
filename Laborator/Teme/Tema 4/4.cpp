#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int NMAX = 1000;
int dp[NMAX][NMAX];

// Gaseste lungimea maxima a subsirului comun
void GasesteSir(string &sir1, string &sir2, int n, int m) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(sir1[i-1] == sir2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
}

// Afiseaza subsirul comun
void AfisareLcs(string sir1, string sir2, int n, int m, ofstream &out) {
    int i = n, j = m;
    string lcs;
    while (i > 0 && j > 0) {
        if (sir1[i - 1] == sir2[j - 1]) { // daca caracterele sunt egale
            lcs = sir1[i - 1] + lcs; // adaug caracterul la subsir
            i--; j--;

            // daca caracterul din sir1[i-1] nu se afla in subsir
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    out << lcs << endl;
}

int main() {
    ifstream in("lcs.in");
    ofstream out("lcs.out");

    string sir1, sir2;
    in >> sir1 >> sir2;
    int n = sir1.length();
    int m = sir2.length();

    GasesteSir(sir1, sir2, n, m);
    AfisareLcs(sir1, sir2, n, m, out);

    in.close();
    out.close();
    return 0;
}
