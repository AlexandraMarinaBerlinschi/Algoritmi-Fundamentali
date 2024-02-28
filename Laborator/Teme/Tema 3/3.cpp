#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

ifstream fin("retea.in");
ofstream fout("retea.out");

vector<long long> distanta;
vector<int> tata;
vector<vector<pair<int, int>>> adiacenta ; // lista de adiacenta
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> prioritati; // coada de prioritati

void initializare(int n){
    adiacenta.resize(n);
    tata.resize(n, 0);
    distanta.resize(n, INT_MAX);
}

void Dijkstra(int n, int src, int dest){
    distanta[src] = 0;
    prioritati.push(make_pair(0, src));  // adaugam sursa in coada

    while (!prioritati.empty()) { // cat timp mai avem noduri de vizitat
        int curr = prioritati.top().second; // luam nodul cu cea mai mica distanta din coada
        prioritati.pop(); // il scoatem din coada

        // merg prin vecini
        for (auto next: adiacenta[curr]) {
            int nextNod = next.first;
            int nextCost = next.second;

            // daca distanta pana la nodul curent + costul muchiei este mai mic decat distanta pana la nodul vecin
            if (nextCost + distanta[curr] < distanta[nextNod]) {
                // actualizez distantele si tatii
                distanta[nextNod] = nextCost + distanta[curr];
                tata[nextNod] = curr;
                prioritati.push(make_pair(distanta[nextNod], nextNod));
            }
        }
    }

    // gasesc cel mai scurt drum de la sursa la destinatie
    stack<int> path;
    while (dest != 0){
        path.push(dest);
        dest = tata[dest];
    }

    while (!path.empty()){
        fout << path.top() << " ";
        path.pop();
    }
}

int main(){
    int n, m, src, dest;

    fin >> n >> m;

    initializare(n + 1);

    // construiesc lista de adiacenta a grafului ponderat
    while (m != 0){
        int x, y, cost;
        fin >> x >> y >> cost;
        adiacenta[x].push_back(make_pair(y, -cost)); // adaug muchia in lista de adiacenta
        m--;
    }

    fin >> src >> dest;
    Dijkstra(n, src, dest);

    return 0;
}
