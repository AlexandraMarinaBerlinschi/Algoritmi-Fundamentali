//O(n+m)
#include <iostream>
#include <vector>
using namespace std;

const int NMAX = 1e6;
vector<int> G[NMAX + 1]; //vector pentru prietenii lui G[i]
int viz[NMAX + 1];
int n,m; // n = nr elevi , m = nr prietenii
vector<int> echipa(NMAX + 1, -1); // vector pentru retinerea echipei fiecarui elev.
// -1 = fara echipa , 0 = echipa 1, 1 = echipa 2

void citire() { //functia de citire
    cin>>n>>m;
    for (int i=1;i<=m;++i) {
        int x,y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}

bool DFS(int x,int e) { // x= elev , e=echipa
    viz[x] =1;
    echipa[x]=e;
    // parcurg vectorul de prieteni ca sa vad daca fiecare elev e verificat si daca e in aceeasi echipa
    for (auto next:G[x]) {
        if (viz[next]==0) { // daca nu a fost vizitat
            if (!DFS(next,1 - e))
                return false; // => doi prieteni in aceeasi echipa, nu e bine
        } else if (echipa[next]==e) {
            return false; // => doi prieteni in aceeasi echipa, nu e bine
        }
    }
    return true;
}

void Afisare() { // functia de afisare
    for (int i=1;i<= n;++i) {
        cout << echipa[i] + 1 << " "; // (+1 pentru ca am pus -1 si 0 in vectorul de echipe)
    }
    cout << "\n";
}

int main() {
    citire(); // citesc valorile
    bool ok = true;
    // parcurg vectorul de elevi si verific daca dfs ul returneaza true sau false
    for (int i=1;i<=n;++i) {
        if (!viz[i]) {
            if (!DFS(i,0)) {
                ok = false;
                break;
            }
        }
    }
    if (ok) { // daca e ok afisez echipele
        Afisare();
    } else {
        cout << "IMPOSSIBLE\n"; // daca nu e ok afisez IMPOSSIBLE
    }

    return 0;
}
