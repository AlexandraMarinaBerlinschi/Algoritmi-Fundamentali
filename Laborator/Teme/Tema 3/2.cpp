#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <stack>
#include <set>
#include <climits>

using namespace std;

vector<long long> distanta;
vector<int> tata;
vector<int> puncteControl;
vector<vector<pair<int, int>>> muchii_costuri; // lista de adiacenta

void read(int& n, int& m, int& source, ifstream& fin) { // citesc datelor din fisier
    fin >> n >> m;
    muchii_costuri.resize(n + 1);
    while (m--) {
        int x, y, cost;
        fin >> x >> y >> cost;
        muchii_costuri[x].push_back(make_pair(y, cost));
        muchii_costuri[y].push_back(make_pair(x, cost));
    }

    int k; // punct de control
    fin >> k;
    while (k--) {
        int x;
        fin >> x;
        puncteControl.push_back(x); // adaug punctele de control in vector
    }

    fin >> source; // nodul sursa
}

// functie pentru a gasi drumul minim de la sursa la un punct de control
void Dijkstra(int n, int source, ofstream& fout) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> dist; // coada de prioritati
     tata.resize(n + 1, 0);
    distanta.resize(n + 1, INT_MAX);
    distanta[source] = 0;
    dist.push(make_pair(0, source)); // adaug sursa in coada
    while (!dist.empty()){
        // iau nodul cu cea mai mica distanta din coada
        int curr = dist.top().second;
        dist.pop();

        // ne plimbam prin vecini
        for (auto next : muchii_costuri[curr]){
            int nextNode = next.first;
            int nextCost = next.second;

            if (distanta[nextNode] > nextCost + distanta[curr]){
                // actualizez distanta si tatal
                distanta[nextNode] = nextCost + distanta[curr];
                tata[nextNode] = curr;
                dist.push(make_pair(distanta[nextNode], nextNode));
            }
        }
    }

    int PunctControlApropiat;
    int DistantaMin = INT_MAX;

    // gasesc cel mai apropiat punct de control de sursa
    for (int cp : puncteControl){
        if (distanta[cp] < DistantaMin){
            DistantaMin = distanta[cp];
            PunctControlApropiat = cp;
        }
    }

        fout << PunctControlApropiat << endl;

        stack<int> path; // stiva pentru a retine drumul de la sursa la un punct de control

        while(tata[PunctControlApropiat] != 0){ // cat timp nu am ajuns la sursa adaug in stiva
            path.push(PunctControlApropiat);
            PunctControlApropiat = tata[PunctControlApropiat];
        }
        path.push(PunctControlApropiat);

        // afisez drumul cu cost minim de la sursa la un punct de control
        while (!path.empty()){
            fout << path.top() << " ";
            path.pop();
        }

}

int main() {
    ifstream fin("grafpond.in");
    ofstream fout("grafpond.out");
    int n, m, source;

    read(n, m, source, fin);
    Dijkstra(n, source, fout);

    fin.close();
    fout.close();
    return 0;
}
