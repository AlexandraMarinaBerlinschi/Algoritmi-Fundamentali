#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int NMAX = 1003;
const int INF = 1e6;

int M[NMAX][NMAX], n, m, e[NMAX], razaGraf, tata[NMAX][NMAX];
vector<int> centruGraf;

void floydWarshall() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(M[i][k] < INF && M[k][j] < INF && M[i][j] > M[i][k] + M[k][j]) {
                    M[i][j] = M[i][k] + M[k][j];
                    tata[i][j] = tata[k][j];
                }
            }
        }
    }
}

int Excent(int x) { // Distanta maxima de la nodul x la oricare alt nod
    int maxDist = -1;
    for(int i = 1; i <= n; i++) {
        maxDist = max(maxDist, M[x][i]);
    }
    return maxDist;
}

void Raza() { // Raza grafului este distanta minima dintre excentricitatile nodurilor
    razaGraf = INF;
    for(int i = 1; i <= n; i++) {
        e[i] = Excent(i);
        razaGraf = min(razaGraf, e[i]);
    }
// Centrul grafului este format din nodurile cu excentricitatea egala cu raza grafului
    for(int i = 1; i <= n; i++) {
        if(e[i] == razaGraf) {
            centruGraf.push_back(i);
        }
    }
}

int DiametruGraf() { // Diametrul grafului este distanta maxima dintre oricare doua noduri
    int diametru = 0;
    for(int i = 1; i <= n; i++) {
        diametru = max(diametru, e[i]);
    }
    return diametru;
}

vector<int> LantDiametral(int diametru) { // Lantul diametral este un lant de lungime diametru
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(M[i][j] == diametru) { // Daca distanta dintre i si j este diametru
                vector<int> path; // Construim lantul diametral
                int a = i, b = j;
                path.push_back(b);
                while(a != b) { // Cat timp nu am ajuns la capatul lantului
                    b = tata[a][b];
                    path.push_back(b);
                }
                reverse(path.begin(), path.end()); // inversez lantul
                return path;
            }
        }
    }
    return {};
}

int main() {
    ifstream in("grafpond.in");
    ofstream out("grafpond.out");

    in >> n >> m;
    for(int i = 1; i <= n; i++) { // Initializez matricea de adiacenta cu infinit
        fill(M[i] + 1, M[i] + n + 1, INF);
        M[i][i] = 0;
    }

    for(int i = 0; i < m; i++) { // Citesc muchiile
        int x, y, c;
        in >> x >> y >> c;
        M[x][y] = c;
        M[y][x] = c; // Presupunem ca graful este neorientat
        tata[x][y] = x;
        tata[y][x] = y;
    }

    floydWarshall();
    Raza();

    out << "Raza: " << razaGraf << "\nCentru: "; // Afisez raza si centrul grafului
    for(int centru : centruGraf) {
        out << centru << " ";
    }
    out << "\nDiametru: " << DiametruGraf() << "\nLant diametral: "; // Afisez diametrul si lantul diametral

    vector<int> lantDiametral = LantDiametral(DiametruGraf()); // Construiesc lantul diametral
    for(int nod : lantDiametral) {
        out << nod << " "; // Afisez lantul diametral
    }
    out << "\n";
    return 0;
}
