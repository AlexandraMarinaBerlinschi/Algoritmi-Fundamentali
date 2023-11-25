//O(n+m)
#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;

const int NMAX = 1e6;
vector<int> G[NMAX+1];
vector<int> muchie(NMAX+1,0); // vector pentru numarul de muchii care intra in nod
vector<int> ordine; // vector pentru ordinea topologica
bitset<NMAX> viz; // bitset pentru a tine evidenta nodurilor vizitate
int n,m; // n= noduri, m= muchii

void citire() { //functia de citire
    cin>>n>>m;
    for (int i=0; i<m;++i) {
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        muchie[b]++; // crestem numarul de muchii pentru nodul b
    }
}

bool BFS() {
    queue<int> q; // coada pentru BFS
    for (int i=1;i<=n;++i) {
        if (muchie[i]==0) {
            q.push(i); // adaugam in coada nodurile care nu au muchii
        }
    }
    while (!q.empty()) {
        // nodul curent este primul din coada il scoatem din coada si il adaugam in vectorul de ordine
        int curs=q.front();
        q.pop();
        ordine.push_back(curs);

        for (int next:G[curs]) { // pentru fiecare nod in care intra muchie din nodul curent
            muchie[next]--;
            if (muchie[next]==0) {
                q.push(next); // daca numarul de muchii este 0 il adaugam in coada
            }
        }
    }
    return ordine.size()==n; // daca numarul de noduri din vectorul de ordine este egal cu numarul de noduri din graf
}

bool dfs(int x, int start) { // verific cu dfs daca exista ciclu
    viz[x] = 1;
    queue<int> q;
    for (int nod : G[x]) {
        if (viz[nod] == 1 && nod == start) { // daca nodul este vizitat si este egal cu nodul de start
            q.push(nod);
            return true; // => am gasit ciclu
        } else if (viz[nod] == 0) { // daca nodul nu este vizitat
            if (dfs(nod, start)) { // verific tot prin dfs daca exista ciclu
                q.push(nod);
                return true; // => am gasit ciclu
            }
        }
    }
    viz[x] = 2;
    return false; // => nu am gasit ciclu (daca se ajunge pana aici)
}

int main() {
    citire(); //citesc variabilele
    if (BFS()){
        for (int curs:ordine) { // afisez vectorul de ordine
            cout<<curs<<" ";
        }
        cout << "\n";
    } else{
        cout << "IMPOSSIBLE\n"; // imposibil de facut sortarea topologica
    }

    return 0;
}


