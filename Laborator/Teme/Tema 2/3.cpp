#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> muchii;
int tati[10001]; //vectorul de tati
int h[10001]; //vectorul de inaltimi

bool compara(vector<int>& v1, vector<int>& v2){ //functie de comparare pentru sortare
    return v1[2] < v2[2];
}

int find(int x){ //functie de gasire a tatalui
    if(x != tati[x]) //daca x nu este tatal lui
        tati[x] = find(tati[x]);  //gaseste tatal lui x
    return tati[x];
}

int main(){
    // iau datele din fisier
    ifstream f("apm2.in");
    ofstream g("apm2.out");

    int n, m, q;
    f >> n >> m >> q; //citesc numarul de noduri, muchii si query-uri

    for(int i = 0; i < m; ++i){
        int x, y, t;
        f >> x >> y >> t; //citesc nodul de plecare, nodul de sosire si costul
        muchii.push_back({x, y, t}); //adaug muchia in vectorul de muchii
    }

    sort(muchii.begin(), muchii.end(), compara); //sortez muchiile crescator dupa cost

    vector<vector<int>> rez; //vectorul de rezultate
    for(int i = 0; i < q; i++){ //citesc query-urile
        int x, y;
        f >> x >> y;//citesc nodul de plecare si nodul de sosire
        rez.push_back({x, y, -1});//adaug query-ul in vectorul de rezultate
    }

    for(int i = 1; i <= n; i++)
        tati[i] = i; //initializez vectorul de tati

    for(int i = 0; i < m; i++){ //parcurg muchiile
        //daca nodurile nu sunt in aceeasi componenta conexa
        if(find(muchii[i][0]) != find(muchii[i][1])){
            int t1 = find(muchii[i][0]); //gasesc tatal nodului de plecare
            int t2 = find(muchii[i][1]); //gasesc tatal nodului de sosire

            //daca inaltimea nodului de plecare este mai mica decat inaltimea nodului de sosire
            if(h[t1] < h[t2])
                tati[t1] = t2; //nodul de sosire devine tatal nodului de plecare
            else if(h[t1] > h[t2])
                tati[t2] = t1; //nodul de plecare devine tatal nodului de sosire
            else{
                tati[t2] = t1; //nodul de plecare devine tatal nodului de sosire
                ++h[t1]; //inaltimea nodului de plecare creste cu 1
            }

            for(int j = 0; j < rez.size(); j++){
                //daca nodurile din query sunt in aceeasi componenta conexa
                if((find(rez[j][0]) == find(rez[j][1])) && rez[j][2] == -1){
                    rez[j][2] = muchii[i][2]-1; //costul muchiei devine costul muchiei din query
                }
            }
        }
    }

    for(int i = 0; i < q; i++)
        g << rez[i][2] << '\n'; //afisez costul muchiei
    return 0;
}
