#include <fstream>
#include <vector>
using namespace std;

ifstream in("hamilton.in");
ofstream out("hamilton.out");


const int NMAX = 19;
const int MMAX = (1 << 18) + 1;
const int INF = 1e9 + 1;

vector<pair<int,int>> G[NMAX];

int cost[MMAX][NMAX],n,m;

int hamilton()
{
    cost[1][0] = 0;
    // dp[masca][i] = costul minim pentru a vizita nodurile din masca si a ajunge in nodul i
    for(int masca = 0; masca < (1 << n); masca++)
    {
        for(int i = 0; i < n; i++)
        {
            if((masca & (1 << i)) != 0) // daca nodul i este in masca
            {
                for(auto next : G[i]) // pentru fiecare vecin al lui i
                {
                    if((masca & (1 << next.first)) != 0) // daca vecinul lui i este in masca
                    {
                        // costul minim pentru a ajunge in nodul i din masca este costul minim pentru a ajunge in vecinul lui i din masca fara i + costul de la vecinul lui i la i
                        cost[masca][i] = min(cost[masca][i],cost[masca ^ (1 << i)][next.first] + next.second);
                    }
                }
            }
        }
    }
    int cost_minim = INF;
    for(auto nod : G[0]) // pentru fiecare vecin al lui 0
    {
        // costul minim pentru a vizita toate nodurile si a ajunge in nodul 0 este costul minim pentru a ajunge in nodul 0 din masca completa + costul de la nodul 0 la nodul i
        cost_minim = min(cost_minim,cost[(1 << n) - 1][nod.first] + nod.second);
    }
    return cost_minim;
}

int main(int argc, const char * argv[])
{
    in >> n >> m;
    for(int i = 0; i < m; i++)  // citesc muchiile
    {
        int x,y,c;
        in >> x >> y >> c;
        G[x].push_back({y,c});
    }
    in.close();
    for (int i = 0; i < (1 << n); i++ ) // initializez costurile cu INF
    {
        for (int j = 0; j < n; j++)
        {
            cost[i][j] = INF;
        }
    }
    int cost_minim = hamilton(); // calculez costul minim
    if(cost_minim == INF)
    {
        out << "Nu exista solutie\n";
    }
    else
    {
        out << cost_minim << "\n";
    }
    return 0;
}
