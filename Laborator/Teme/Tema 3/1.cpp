#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

// definesc dfs ul
void dfs(int curr, stack<int>& sortate, vector<bool>& vizitate, vector<int> muchii[]) {
    vizitate[curr] = true;
    for (const int v : muchii[curr]) { // parcurg vecinii
        if (!vizitate[v]) {
            dfs(v, sortate, vizitate, muchii); // aplic dfs pe vecini
        }
    }

    sortate.push(curr); // adaug nodul in stiva
}

stack<int> sortare(int n, vector<int> muchii[]) { // sortare topologica
    stack<int> sortate;
    vector<bool> vizitate(n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (!vizitate[i]) {
            dfs(i, sortate, vizitate, muchii); // aplic dfs pe nodurile nevizitate
        }
    }

    return sortate; // returnez stiva cu nodurile sortate
}

void drumuri() {
    ifstream f("activitati.in");

    vector<int> durata = {0};
    int n, m;
    f >> n;
    for (int i = 0; i < n; i++) { // citesc durata
        int timp;
        f >> timp;
        durata.push_back(timp); // adaug in vector
    }
    f >> m;
    vector<int> muchii[m+1];

    for (int i = 0; i < m; ++i) {
        int u,v;
        f >> u >> v;
        muchii[u].push_back(v); //citesc si  adaug muchiile in vector
    }
    vector<int> tata(n+1,0);
    //vectorii de timp
    vector<int> inceput(n+1,0);
    vector<int> sfarsit(n+1,0);

    stack<int> ordine = sortare(n, muchii); // sortez topologic nodurile

    int timp_min = 0, nmax=0;   // timpul minim si nodul maxim

    while(!ordine.empty()){
        // iau nodul din varful stivei si calculez timpul de sfarsit
        int r = ordine.top();
        sfarsit[r] = inceput[r]+durata[r];
        // daca timpul de sfarsit al nodului curent > timpul minim
        if(sfarsit[r] > timp_min){
            timp_min = sfarsit[r];
            nmax = r;
        }
        ordine.pop(); // scot nodul din stiva

        for(auto v: muchii[r]){  // parcurg vecinii nodului curent
            // daca timpul de inceput al vecinului < timpul de inceput al nodului curent + durata nodului curent ii ia locul
            if(inceput[v] < inceput[r] + durata[r]){
                inceput[v] = inceput[r] + durata[r];
                tata[v] = r; // tatal vecinului devine nodul curent
            }
        }
    }

    cout<<"Timp minim: "<<timp_min<<endl;

    string final;
    while(nmax != 0){ // cat timp nu am ajuns la nodul de start adaug nodul in sirul final
        final = to_string(nmax)+" "+final;
        nmax = tata[nmax]; // trec la tatal nodului curent
    }
    cout<<"Activitati critice: "<<final<<endl;

    for (int i = 1; i <= n; ++i) {
        cout<<i<<": "<<inceput[i]<<" "<<sfarsit[i]<<endl;
    }

    f.close();
}
int main()
{
    drumuri();
    return 0;
}
