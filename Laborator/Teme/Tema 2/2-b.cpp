#include <bits/stdc++.h>
using namespace std;

ifstream f("retea2.in");
ofstream g("retea2.out");

struct punct {
    long long x, y; // coordonatele punctului
};
punct c[2001], b[2001]; // c - centrale, b - blocuri
long long d[2001], vis[2001];
long long dist(punct a, punct b) { // distanta euclidiana la patrat
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    int n, m;
    f >> n >> m; // n - nr centrale, m - nr blocuri
    for(int i = 1; i <= n; i++) { // citesc centralele
        f >> c[i].x >> c[i].y;
    }
    for(int i = 1; i <= m; i++) { // citesc blocurile
        f >> b[i].x >> b[i].y;
        d[i] = 1e18;
    }
    for(int i = 1; i <= m; i++) { // calculez distanta minima de la fiecare bloc la o centrala
        long long mn = 1e18;
        for(int j = 1; j <= n; j++) { // parcurg centralele
            mn = min(mn, dist(b[i], c[j])); // calculez distanta minima
        }
        d[i] = mn; // salvez distanta minima
    }
    for(int i = 1; i <= m; i++) { // aplic algoritmul lui Prim
        long long mn = 1e18; // mn - distanta minima
        int pos = 0; // pos - pozitia blocului
        for(int j = 1; j <= m; j++) { // parcurg blocurile
            if(!vis[j] && d[j] < mn) { // daca nu am vizitat blocul si distanta este mai mica decat distanta minima
                mn = d[j]; // actualizez distanta minima
                pos = j; // actualizez pozitia blocului
            }
        }
        vis[pos] = 1; // marchez blocul ca vizitat
        for(int j = 1; j <= m; j++) { // parcurg blocurile
            // daca nu am vizitat blocul si distanta este mai mare decat distanta de la blocul curent la blocul j
            if(!vis[j] && d[j] > dist(b[pos], b[j])) {
                d[j] = dist(b[pos], b[j]); // actualizez distanta
            }
        }
    }
    double sol = 0;
    for(int i = 1; i <= m; i++) { // calculez suma distantei de la fiecare bloc la o centrala
        sol += sqrt(d[i]);
    }
    g << fixed << setprecision(7) << sol; // afisez solutia cu 7 zecimale
    return 0;
}
