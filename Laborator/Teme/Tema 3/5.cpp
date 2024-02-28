#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;

const int NMAX = 1e4 + 1;
const int INF = 1e9;

int n, d[NMAX], aparitii[NMAX], parent[NMAX];
bool ciclu_bool;
bitset<NMAX> vizitat;
vector<pair<int, int>> G[NMAX]; // vector de perechi (nod, cost)
queue<int> q; // coada de noduri

void AfisareCiclu(int x, int y, ofstream &out) { // afisare ciclu de cost negativ
    vector<int> ciclu;
    // parcurg ciclul de la y la x si il adaug in  ciclu
    while (x != y) {
        ciclu.push_back(x);
        x = parent[x];
    }
    ciclu.push_back(x); // adaug si nodul y
    for (int i = ciclu.size() - 1; i >= 0; i--) {  // afisez ciclul
        out << ciclu[i] << " ";
    }
}

void AfisareDrum(int s, ofstream &out) { // afisez drum de la s la orice nod
    vector<int> drum;
    while (parent[s] != 0) { // parcurg drumul de la s la 0 si il adaug in drum
        drum.push_back(s);
        s = parent[s];
    }
    drum.push_back(s);
    out << "Drum: ";
    for (int i = drum.size() - 1; i >= 0; i--) { // afisez drumul
        out << drum[i] << " ";
    }
}

void bellmanFord(int z, ifstream &in, ofstream &out) {
    for (int i = 2; i <= n; i++) {
        d[i] = INF; // initializez distantele cu infinit
    }
    d[z] = 0;
    q.push(z);
    aparitii[z]++; // numarul de aparitii ale lui z in coada
    vizitat[z] = true;
    while (!q.empty()) {
        int x = q.front(); // extrag primul nod din coada
        q.pop();
        vizitat[x] = false;
        for (auto &p: G[x]) { // parcurg vecinii nodului x
            int y = p.first, cost = p.second;
            // daca distanta de la z la y este mai mare decat distanta de la z la x + costul muchiei
            if (d[y] > d[x] + cost) {
                d[y] = d[x] + cost;
                if (!vizitat[y]) { // daca nodul y nu a fost vizitat, il adaug in coada
                    q.push(y);
                    aparitii[y]++; // numarul de aparitii ale lui y in coada
                    vizitat[y] = true;
                    parent[y] = x;
                    // daca numarul de aparitii ale lui y in coada este egal cu n, atunci exista ciclu de cost negativ
                    if (aparitii[y] == n) {
                        ciclu_bool = true;
                        out << "Circuit de cost negativ: \n";
                        AfisareCiclu(x, y, out); // afisez ciclul
                        return;
                    }
                }
            }
        }
    }
}

int main() {
    ifstream in("grafpond.in");
    ofstream out("grafpond.out");

    int m;
    in >> n >> m;
    for (int i = 0; i < m; i++) { // citesc muchiile
        int x, y, cost;
        in >> x >> y >> cost;
        G[x].push_back({y, cost}); // adaug muchia in graf
    }

    int nod_start;
    in >> nod_start;
    bellmanFord(nod_start, in, out);

    if (!ciclu_bool) { // daca nu exista ciclu de cost negativ
        for (int i = 2; i <= n; i++) {
            AfisareDrum(i, out);
            out << "Cost: " << d[i] << "\n";
        }
    }

    return 0;
}
