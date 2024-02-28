#include <fstream>
#include <vector>
#include <stack>
using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

const int NMAX = 1e4 + 1;

vector <int> G[NMAX];
int grad[NMAX];

void AfisareCircuit(const vector<int> &circuit)
{
    if(circuit.size() == 0)
    {
        out << "Nu exista circuit eulerian\n";
        return;
    }
    for(int i = (int)circuit.size() - 1; i >= 0; i--) // afisez circuitul in ordine inversa
    {
        out << circuit[i] << " ";
    }
}

void CautaCiclu()
{
    stack <int> s; // stiva in care retin nodurile prin care trec
    s.push(1);
    vector<int> circuit;
    while(!s.empty())
    {
        int nod_curent = s.top(); // nodul curent este ultimul nod din stiva
        if(G[nod_curent].size() > 0) // daca mai am muchii de parcurs
        {
            int next = G[nod_curent].back(); // next este ultimul nod adiacent nodului curent
            G[nod_curent].pop_back(); // sterg muchia
            s.push(next);
        }
        else
        {
            // daca nu mai am muchii de parcurs, adaug nodul curent in circuit
            circuit.push_back(nod_curent);
            nod_curent = s.top();
            s.pop();
        }
    }
    AfisareCircuit(circuit);
}

int main(int argc, const char * argv[])
{
    int n,m;
    in >> n >> m;
    for(int i = 0; i < m; i++) // citesc muchiile
    {
        int x,y;
        in >> x >> y;
        G[x].push_back(y);
    }
    for(int i = 1; i <= n; i++)
    {
        grad[i] = (int)G[i].size(); // retin gradul fiecarui nod
    }
    CautaCiclu();
    return 0;
}
