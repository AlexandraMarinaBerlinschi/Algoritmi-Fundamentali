#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
const int NMAX = 10e6;
int tata[NMAX + 1]={0}, h[NMAX + 1]={0}; //tata[i] = tatal nodului i, h[i] = inaltimea arborelui cu radacina i

struct Muchie { //structura muchiei
    int u, v, w;
};

bool comp(Muchie a, Muchie b) { // compar muchiile
    return a.w < b.w;
}

int Find(int u) { // gaseste radacina arborelui cu radacina u
    if(tata[u] == 0)
        return u;
    return Find(tata[u]);
}

void Union(int u, int v) { // reunesc arborii cu radacinile u si v
    int ru, rv;
    ru = Find(u);
    rv = Find(v);
    if (h[ru] > h[rv]) { // daca inaltimea arborelui cu rad u este mai mare decat inaltimea arborelui cu rad v
        tata[rv] = ru; // radacina arborelui cu rad v devine radacina arborelui cu rad u
    } else {
        tata[ru] = rv; // radacina arborelui cu rad u devine radacina arborelui cu rad v
        if (h[ru] == h[rv]) { // daca inaltimile sunt egale
            h[rv]++; // inaltimea arborelui cu rad v creste cu 1
        }
    }
}

int c[1000][1000] = {0}; //matricea costurilor
int distanta(string &s1, string &s2){ //distanta dintre doua stringuri
    c[0][0] = 0; //distanta dintre doua stringuri vide este 0
    for(int i = 1; i<=s1.size(); i++){
        c[i][0] = 1 + c[i-1][0]; //calculez distanta dintre s1[0..i] si sirul vid
    }
    for(int j = 1; j<=s2.size(); j++){
        c[0][j] = 1 + c[0][j-1]; //calculez distanta dintre s2[0..j] si sirul vid
    }
    for(int i = 1; i<=s1.size(); i++){
        for(int j = 1; j<=s2.size(); j++){
            if(s1[i-1] == s2[j-1]){ //daca ultimele caractere sunt egale
                c[i][j] = c[i-1][j-1];
            }else{
                c[i][j] = 1 + min(c[i-1][j], min(c[i][j-1], c[i-1][j-1])); //calculez distanta dintre s1[0..i] si s2[0..j]
            }
        }
    }
    return c[s1.size()][s2.size()]; //returnez distanta dintre s1 si s2
}

void levenshtein(){
    ifstream f("cuvinte.in");
    int k;
    cin>>k;

    vector<string> cuvinte; //vector de cuvinte
    string cuv;

    while (f >> cuv) {
        cuvinte.push_back(cuv);
    }

    vector<string> siruri(cuvinte.size(), ""); //vector de stringuri
    vector<Muchie> muchii; //vector de muchii

    for(int i=0;i<cuvinte.size()-1;i++)
        for(int j=i+1;j<cuvinte.size();j++){
            int co = distanta(cuvinte[i],cuvinte[j]); //calculez distanta dintre cuvintele i si j
            Muchie m{}; //creez muchia
            m.u = i;
            m.v = j;
            m.w = co;
            muchii.push_back(m);
        }

    //sortez muchiile pentru kruskal
    sort(muchii.begin(), muchii.end(), comp); //sortez muchiile crescator dupa cost

    int compCon = cuvinte.size(); // numarul de componente conexe

    int gradSeparare = 0;
    //kruskal
    for (auto &i : muchii) { //parcurg muchiile
        int u = i.u;
        int v = i.v;
        int w = i.w;

        int ru = Find(u);
        int rv = Find(v);

        if (ru != rv) {
            if (compCon == k) {
                gradSeparare = w; //gradul de separare este costul muchiei
                break;
            }else{
                Union(ru, rv);
                compCon--;
            }

        }
    }
    for(int i=0; i<cuvinte.size();i++){
        int rep = Find(i); //reprezentantul componentei conexe
        siruri[rep].append(" "+cuvinte[i]); //adaug cuvantul i la sirul reprezentantului
    }

    for(const auto & cuv : siruri)
        if(!cuv.empty())
            cout<<cuv.substr(1,cuv.size())<<endl; //afisez sirurile
    cout<<gradSeparare;
}

int main () {
    levenshtein();
    return 0;
}
