#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
#define INT_MAX 99999999

ifstream fin("catun.in");
ofstream fout("catun.out");

vector<long long> distanta;
vector<int> tata;
vector<int> NodControl;
vector<vector<pair<int,int>>> adiacenta; // lista de adiacenta

priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> prioritati; // coada de prioritati

int n, m, k;

void initializare(int n){
    adiacenta.resize(n);
    tata.resize(n);
    distanta.resize(n);
}

void Dijkstra(){
    // se initializeaza distanta tuturor nodurilor cu infinit
    fill(distanta.begin(), distanta.end(), INT_MAX);
    // se initializeaza tatal tuturor nodurilor cu 0
    fill(tata.begin(), tata.end(), 0);

    for(auto ControlNod : NodControl){
        distanta[ControlNod] = 0;
        // adaug fortaretele la coada de prioritati cu prioritatea 0
        prioritati.push(make_pair(0, ControlNod));
    }

    while(!prioritati.empty()){
        int currentNode = prioritati.top().second;
        prioritati.pop();

        for(auto next : adiacenta[currentNode]){
            // se ia fiecare vecin si cost al nodului curent
            int nextNode = next.first;
            int nextCost = next.second;

            // daca distanta pana la vecin este mai mare decat distanta pana la nodul curent + costul dintre nodul curent si vecin
            if(distanta[nextNode] > nextCost + distanta[currentNode]){
                distanta[nextNode] = nextCost + distanta[currentNode];
                tata[nextNode] = currentNode;
                // se adauga in coada de prioritati vecinul cu distanta minima
                prioritati.push(make_pair(distanta[nextNode], nextNode));
            }
            // daca distanta pana la vecin este egala cu distanta pana la nodul curent + costul dintre nodul curent si vecin
            else if(distanta[nextNode] == nextCost + distanta[currentNode] ){
                // se ia tatal nodului curent si tatal vecinului
                int tata1 = nextNode;
                int tata2 = currentNode;

                // se merge in spate prin vectorul de tati pana cand se gaseste un nod care are parintele 0
                while(tata[tata1] != 0)
                    tata1 = tata[tata1]; // tatal nodului curent

                while(tata[tata2] != 0)
                    tata2 = tata[tata2]; // tatal vecinului

                if(tata1 > tata2) // se compara tatal nodului curent cu tatal vecinului
                    tata[nextNode] = currentNode;
            }
        }
    }
}

int main(){
    fin >> n >> m >> k;

    initializare(n + 1);

    while(k != 0){ // se citesc fortaretele
        int x;
        fin >> x;
        NodControl.push_back(x);
        k--;
    }

    while(m != 0){ // se citesc drumurile
        int x, y, cost;
        fin >> x >> y >> cost;
        adiacenta[x].push_back(make_pair(y, cost));
        adiacenta[y].push_back(make_pair(x, cost));
        m--;
    }

    Dijkstra();

    for(int i=1; i<=n; ++i){
        int last = tata[i]; // se ia tatal nodului curent
        while(tata[last] != 0)
            last = tata[last]; // se afiseaza parintii nodurilor, adica cele mai apropiate fortarete
        fout << last << " ";
    }

    return 0;
}
