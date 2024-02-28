#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;

ifstream in("retea.in");
ofstream out("retea.out");

const int NMAX = 101;
const int INF = 1e8;
int capacitate[NMAX][NMAX], flux[NMAX][NMAX], tata[NMAX];
int n,m;
vector <int> G[NMAX];
bitset <NMAX> vizitat;

int Edmonds_Karp(int sursa, int dist)
{
    queue <int> q;
    int flow = INF;

    q.push(sursa);
    vizitat[sursa] = true;
    while(!q.empty())
    {
        int nod = q.front();
        q.pop();
        for(auto next : G[nod])
        {
            // daca nu am vizitat nodul si capacitatea este mai mare decat fluxul
            if(capacitate[nod][next] - flux[nod][next] > 0 && !vizitat[next])
            {
                tata[next] = nod; // retin tatal
                q.push(next); // adaug in coada
                vizitat[next] = true;
            }
            if(next == dist) // daca am ajuns la destinatie
            {
                int dest_curr = dist; // retin destinatia si sursa
                int sursa_curr = sursa;
                while(dest_curr != sursa_curr) // cat timp nu am ajuns la sursa
                {
                    // retin fluxul minim
                    flow = min(flow, capacitate[tata[dest_curr]][dest_curr] - flux[tata[dest_curr]][dest_curr]);
                    dest_curr = tata[dest_curr]; // trec la urmatorul nod
                }
                return flow;
            }
        }

    }
    return 0;
}

int FluxMaxim(int sursa, int dist)
{
    int sum = 0;
    while(true)
    {
        int f = Edmonds_Karp(sursa, dist); // retin fluxul si il adaug la fluxul total
        sum += f;
        if(f == 0) // daca fluxul este 0, inseamna ca nu mai exista drumuri
        {
            break;
        }
        else
        {
            int desc = dist, Sursa = sursa; // retin destinatia si sursa
            while(desc != Sursa) // cat timp nu am ajuns la sursa
            {
                flux[tata[desc]][desc] += f; // adaug fluxul
                flux[desc][tata[desc]] -= f; // scad fluxul
                desc = tata[desc]; // trec la urmatorul nod
            }
        }
    }
    return sum; // returnez fluxul total
}

bool ConservareFlux(int &sursa, int &dist)
{
    for(int nod = 1; nod <= n; nod++) // parcurg toate nodurile
    {
        if(nod == sursa || nod == dist)  // daca este sursa sau destinatia, trec mai departe
        {
            continue;
        }
        int f_val = 0;
        for(int nod_n = 1; nod_n <= n; nod_n++) // parcurg vecinii nodului
        {
            f_val += flux[nod][nod_n]; // adaug fluxul
        }
        return (f_val != 0) ? true : false; // daca fluxul este diferit de 0, returnez true
    }
    return false;
}

void dfs(int nod, int sursa)
{
    vizitat[nod] = true;
    for(auto next : G[nod]) // parcurg vecinii nodului
    {
        // daca nu am vizitat nodul si capacitatea este mai mare decat fluxul
        if(!vizitat[next] && capacitate[nod][next] - flux[nod][next] > 0)
        {
            dfs(next,sursa); // trec la urmatorul nod
        }
    }
}

void taietura_minima(int &start)
{
    vizitat.reset();
    dfs(start,start);
    for(int i = 1; i <= n; i++)
    {
        for(auto next: G[i])
        {
            // daca am vizitat nodul si vecinul si capacitatea este mai mare decat fluxul
            if(vizitat[i] && vizitat[next] && capacitate[i][next] > 0)
            {
                out << i << " " << next << "\n"; // afisez nodul si vecinul
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    int sursa,dist;
    in >> n;
    in >> sursa >> dist;
    in >> m;
    for(int i = 0; i < m; i++) // parcurg toate muchiile
    {
        int x,y,c,f;
        in >> x >> y >> c >> f;
        G[x].push_back(y);
        G[y].push_back(x);
        if(f < 0 || f > c) // daca fluxul este mai mic decat 0 sau mai mare decat capacitatea
        {
            out << "Fluxul nu respecta conditia de marginire pentru muchia " << x << "-" << y << '\n';
        }
        capacitate[x][y] = c; // retin capacitatea
        // retin fluxul
        flux[x][y] += f;
        flux[y][x] -= -f;
    }
    in.close();
    if(ConservareFlux(sursa, dist)) // daca nu se conserva fluxul
    {
        out << "NU\n";
        return 0;
    }
    else
    {
        out << "DA\n";
    }
    int flux_val = 0;
    for(auto next : G[sursa]) // parcurg vecinii sursei
    {
        flux_val += flux[sursa][next]; // adaug fluxul
    }
    int flux_max = flux_val + FluxMaxim(sursa, dist); // retin fluxul maxim si il afisez
    out << flux_max << "\n";
    for(int i = 1; i <= n; i++) // parcurg toate nodurile
    {
        for(auto next : G[i])  // parcurg vecinii nodului
        {
            // daca fluxul este mai mare decat 0 si capacitatea este mai mare decat 0
            if(flux[i][next] >= 0 && capacitate[i][next] > 0)
            {
                out << i << " " << next << " " << flux[i][next] << "\n"; // afisez nodul, vecinul si fluxul
            }
        }
    }
    out << flux_max << "\n";
    taietura_minima(sursa);
    out.close();
    return 0;
}
