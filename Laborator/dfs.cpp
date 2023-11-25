#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream fin("dfs.in");
ofstream fout("dfs.out");

const int NMAX=1e6;
vector <int> G[NMAX+1];
int viz[NMAX+1],d[NMAX+1];
int n,m;

void citire(){
    fin>>n>>m;
    for(int i=1;i<=m;++i){
        int x,y;
        fin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}

void DFS(int x){
    viz[x]=1;
    for(auto next:G[x])
        if(!viz[next]) DFS(next);
}

void Afisare(){
    for(int i=1;i<=n;++i){
        for(auto v:G[i]) fout<<v<<" ";
        fout<<"\n";
    }
}
int main() {
    citire();
    int ct=0;
    for(int i=1;i<=n;++i){
        if(!viz[i]) { ct++; DFS(i);}
    }
    fout<<ct;
    return 0;
}
