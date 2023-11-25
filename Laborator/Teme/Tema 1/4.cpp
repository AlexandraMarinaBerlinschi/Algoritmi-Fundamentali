// O(n+m) - Gasirea componentelor tari conexe ale unui graf orientat (Kosaraju)
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int NMAX = 1e6; //nr maxim de noduri
int n,m,ct; // n= numarul de noduri, m= numarul de muchii
int viz[NMAX],rez[NMAX];
vector <int> G[NMAX],GT[NMAX]; //graful si graful transpus
stack <int> st; // stiva pentru dfs

void Citire(){ // functia de citire
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int x,y;
        cin >> x >> y;
        G[x].push_back(y);
        GT[y].push_back(x);
    }
}

void DFS(int x){ // functia de dfs
    viz[x]=1;
    for(auto y : G[x])
        if(!viz[y])
            DFS(y); // marchez nodurile ca vizitate
    st.push(x); // adaug nodurile in stiva in ordine inversa
}

void DFS_Transpus(int x){ //functia de dfs transpus
    viz[x]=2;
    rez[x]=ct;
    for(auto y : GT[x])
        if(viz[y] != 2)
            DFS_Transpus(y); // acelasi lucru ca mai sus doar ca pe graful transpus
}

int main(){
    Citire(); //citesc valorile
    // trec prin toate nodurile iar daca nodul nu a fost vizitat aplic dfs pe el
    for(int i = 1; i <= n; i++){
        if(viz[i] != 1)
            DFS(i);
    }
    while(!st.empty()){
        // iau nodul din varful stivei si il scot din stiva
        int nod=st.top();
        st.pop();
        if(viz[nod] != 2){ // daca nodul nu a fost vizitat
            ct++; // cresc numarul de componente tari conexe
            DFS_Transpus(nod); // aplic dfs pe graful transpus
        }
    }
    // afisez numarul de componente tari conexe si componentele tari conexe
    cout<<ct<<"\n";
    for(int i=1;i<=n;i++)
        cout<<rez[i]<< " ";
    return 0;
}
