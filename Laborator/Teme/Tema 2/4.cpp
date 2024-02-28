#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int NMAX = 100005;

int tata[NMAX],muchie;
vector<int> muchii_folosite;

struct Muchie
{
    int x, y, c; // x,y = noduri, c = cost
} muchii[NMAX];

bool cmp(Muchie x, Muchie y) // sortare muchii dupa cost
{
    return x.c < y.c;
}

void init(int n)
{
    for (int i = 1; i <= n; i++) // initializez parintii
    {
        tata[i] = 0;
    }
}
int find(int x) // caut parintele unui nod
{
    if (tata[x] == 0) // daca nu are parinte
    {
        return x;
    }
    return tata[x] = find(tata[x]);
}

int union1(int i, int sum)
{
    int x, y;
    x = find(muchii[i].x); // caut parintele nodului x
    y = find(muchii[i].y); // caut parintele nodului y
    if (x != y) { // daca nu au acelasi parinte
        tata[x] = y; // ii unesc
        muchii_folosite.push_back(i); // adaug muchia in vectorul de muchii folosite
        sum += muchii[i].c; // adaug costul muchiei la costul total
    }
    return sum;
}

int union2(int i, int sum)
{
    int x, y;
    x = find(muchii[i].x); // caut parintele nodului x
    y = find(muchii[i].y); // caut parintele nodului y
    if (x != y) { // daca nu au acelasi parinte
        tata[x] = y; // ii unesc
        sum += muchii[i].c; // adaug costul muchiei la costul total
        muchie++;// cresc numarul de muchii folosite
    }
    return sum;
}

int main()
{
    int n,m;
    cin >> n >> m;
    init(n);
    for(int i = 0; i < m; i++)
    {
        cin >> muchii[i].x >> muchii[i].y >>muchii[i].c; // citesc muchiile
    }
    sort(muchii, muchii + m, cmp); // sortez muchiile dupa cost
    int sum = 0;
    for (int i = 0; i < m; i++)
    {
        sum = union1(i, sum); // construiesc mst
    }
    cout << sum << " ";
    int mst = INT_MAX;
    sum = 0;
    for (int j = 0; j < muchii_folosite.size(); j++) // parcurg muchiile folosite
    {
        init(n); // resetez parintii
        muchie = 0; // resetez numarul de muchii folosite
        for (int i = 0; i < m; i++)
        {
            if (i == muchii_folosite[j]) // daca muchia a fost folosita in mst continui
            {
                continue;
            }
            sum = union2(i, sum); // construiesc mst
        }
        if (muchie != n - 1)// daca nu am n-1 muchii in mst continui
        {
            sum = 0;
            continue;
        }
        if (mst > sum)
        {
            mst = sum; // daca am gasit un mst mai bun decat cel initial il salvez
        }
        sum = 0;
    }

    cout << mst; // afisez costul celui de-al doilea mst
    return 0;
}
