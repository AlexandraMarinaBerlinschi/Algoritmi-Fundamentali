#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4;
int d[NMAX + 1]; // distanta intre statii
bool vis[NMAX + 1];
vector<pair<int, int>> G[NMAX + 1];

int main() {
    int t;
    cin >> t; // nr de teste
    while(t--) {
        int n, m, L, k;
        cin >> n >> m >> L >> k; // n - nr de statii, m - nr de drumuri, L - costul de transmitere , k - nr de statii cu programul instalat
        set<pair<int, int>> s; // evidenta statiilor cu programul instalat
        for(int i = 1; i <= n; i++) { // initializez distante
            d[i] = 1e9;
            vis[i] = 0;
        }
        for(int i = 1; i <= k; i++) { // citesc statiile cu programul instalat
            int x;
            cin >> x;
            d[x] = 0;
            s.insert({0, x});
        }
        for(int i = 1; i <= m; i++) { // citesc drumurile
            int x, y, c;
            cin >> x >> y >> c;
            G[x].push_back({y, c});
            G[y].push_back({x, c});
        }
        long long sol = 0; // solutia
        while(!s.empty()) { // daca mai am statii cu programul instalat
            auto it = s.begin();// aleg statia cu costul minim
            s.erase(it); // o sterg din multime
            int cost = (*it).first;
            int node = (*it).second;
            if(vis[node]) { // daca am mai vizitat-o o sar
                continue;
            }
            vis[node] = 1;
            sol += 1LL * cost; // adaug costul la solutie
            for(auto next : G[node]) { // parcurg vecinii
                if(d[next.first] > next.second) { // daca distanta pana la vecin este mai mare decat distanta pana la nodul curent + costul muchiei
                    d[next.first] = next.second; // actualizez distanta
                    s.insert({d[next.first], next.first}); // adaug vecinul in multime
                }
            }
        }
        for(int i = 1; i <= n; i++) { // resetez graful
            G[i].clear();
        }
        sol += 1LL * (n - k) * L; // adaug la solutie costul de transmitere pentru statiile fara program
        cout << sol << '\n';
    }
    return 0;
}
