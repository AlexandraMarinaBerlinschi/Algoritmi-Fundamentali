#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream fin("bfs.in");
ofstream fout("bfs.out");

const int NMAX=1e6;
vector <int> G[NMAX+1];
int viz[NMAX+1],d[NMAX+1];
int n,m,s;

void citire(){
    fin >> n >> m >> s;
    for(int i=1;i<=m;++i){
        int x,y;
        fin>>x>>y;
        G[x].push_back(y);
    }
}
void BFS(int x){
    queue <int> q;
    q.push(x);
    d[x]=0; viz[x]=1;
    while(!q.empty()){
        int y=q.front(); q.pop();
        for(auto next:G[y]){
            if(!viz[next]){
                q.push(next); viz[next]=1;
                d[next]=d[y]+1;
            }
        }
    }
}

void afisare(){
    for(int i=1;i<=n;++i){
        for(auto v:G[i]) fout<<v<<" ";
        fout << "\n";
    }
}
int main() {
    citire();
    BFS(s);
    for(int i=1;i<=n; i++){
        if(!d[i] && i != s)
            d[i]=-1;
        fout << d[i] << " ";
    }
    return 0;
}
