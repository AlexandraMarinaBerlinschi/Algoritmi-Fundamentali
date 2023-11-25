//O(n*m)

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int NMAX = 1000;
char Cladire[NMAX][NMAX];
int n, m;
int camera = 0;
vector<vector<bool>> numaratoare(NMAX, vector<bool>(NMAX, false));
// fac o matrice cu NMAX randuri si NMAX coloane care are ca valori pentru fiecare camp false

void dfs(int x, int y) {
    // daca iese din matrice sau daca a fost deja vizitat sau daca e perete
    if (x < 0 || x >= n || y < 0 || y >= m || numaratoare[x][y] || Cladire[x][y] == '#') {
        return;
    }

    numaratoare[x][y] = true;

    //incercam pentru fiecare pozitie - x pentru axa Ox si y pentru axa Oy
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int Camere_numaratoare() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!numaratoare[i][j] && Cladire[i][j] == '.') { // daca nu a fost vizitat si daca e camera
                ++camera;
                dfs(i, j);
            }
        }
    }
    return camera;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> Cladire[i][j];
        }
    }

    int rez = Camere_numaratoare();
    cout << rez << endl;

    return 0;
}
