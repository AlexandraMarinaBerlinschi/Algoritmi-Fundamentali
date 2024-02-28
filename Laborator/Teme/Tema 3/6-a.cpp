#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int NMAX = 100;
const int INF = 1e9;
int M[NMAX][NMAX], nxt[NMAX][NMAX];
bool exista_ciclu;

void AfisareCiclu(int p, ofstream &out) {
    vector<int> cale;
    int nod = p;
    do { // caut un ciclu
        cale.push_back(nod);
        nod = nxt[nod][p];
    } while (nod != p);
    for (int nod : cale) { // afisez ciclul
        out << nod << " ";
    }
    out << '\n';
}

void floydWarshall(int n, ofstream &out) {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(M[i][k] < INF && M[k][j] < INF && M[i][j] > M[i][k] + M[k][j]) {
                    M[i][j] = M[i][k] + M[k][j];
                    nxt[i][j] = nxt[i][k];
                }
                if(i == j && M[i][j] < 0) { // daca am gasit un ciclu de cost negativ
                    exista_ciclu = true;
                    out << "Circuit de cost negativ\n";
                    AfisareCiclu(i, out);
                    return;
                }
            }
        }
    }
}

int main() {
    ifstream in("grafpond.in");
    ofstream out("grafpond.out");

    int n, m;
    in >> n >> m;

    // Initializare matrice
    for(int i = 1; i <= n; i++) {
        fill(M[i] + 1, M[i] + n + 1, INF);
        M[i][i] = 0;
    }

    for(int i = 0; i < m; i++) { // Citire muchii
        int x, y, c;
        in >> x >> y >> c;
        M[x][y] = c;
        nxt[x][y] = y;
    }

    floydWarshall(n, out);

    if(!exista_ciclu) { // Daca nu exista ciclu de cost negativ
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                out << (M[i][j] == INF ? 0 : M[i][j]) << " "; // Afisare matrice
            }
            out << "\n";
        }
    }

    return 0;
}
