//O(n+m)
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");

const int NMAX = 1e6;
vector<int> G[NMAX + 1];
int n, m, s;

void citire() {
    fin >> n >> m >> s;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}

void BFS(int start, vector<int>& dist) {
    queue<int> q;
    vector<bool> viz(n + 1, false); // vectorul de vizite

    q.push(start); // adaugam nodul de start in coada
    dist[start] = 0; // distanta de la nodul de start la el insusi este 0
    viz[start] = true; // nodul de start este vizitat

    while (!q.empty()) {
        int u = q.front(); // extragem primul nod din coada
        q.pop();

        for (int v : G[u]) { // parcurgem vecinii nodului u
            if (!viz[v]) {
                dist[v] = dist[u] + 1; // distanta de la nodul de start la nodul v este distanta de la nodul de start la nodul u + 1
                viz[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    citire();
    vector<int> puncte_control; // vectorul de puncte de control
    int point;
    while (fin >> point) {
        puncte_control.push_back(point); // adaugam punctele de control in vector
    }

    for (int punct_control : puncte_control) { // parcurgem fiecare punct de control
        vector<int> dist(n + 1, -1); // vectorul de distante
        BFS(punct_control, dist); // aplicam BFS de la punctul de control

        for (int i = 1; i <= n; i++) {
            if (i != 1) {
                fout << " ";
            }
            fout << dist[i];
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
