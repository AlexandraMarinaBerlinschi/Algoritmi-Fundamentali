//O(n+m)
#include <iostream>
#include <vector>
using namespace std;

const int NMAX = 1e5;
vector<int> G[NMAX + 1];
int d[NMAX + 1], low[NMAX + 1], cnt, sol; // d = discovery time, low = lowest d, cnt = contor, sol = solutie
int art[NMAX + 1], h, vis[NMAX + 1], r; // art = articulation point, h = height, r = root

void dfs(int x, int p) {
    vis[x] = 1;
    h++;
    d[x] = low[x] = h;
    for(auto next : G[x]) {
        if(!vis[next]) {
            dfs(next, x);
            low[x] = min(low[x], low[next]);
            if(x == r) { cnt++;
            } else {
                if(low[next] >= d[x]) art[x] = 1;
            }
        } else {
            if(next != p) low[x] = min(low[x], d[next]);
        }
    }
}

int main() {
    while(true) {
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        while(m--) {
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        r = 1;
        sol = 0;
        cnt = 0;
        h = 0;
        dfs(r, 0);
        if(cnt >= 2) art[1] = 1;
        for(int i = 1; i <= n; i++) {
            if(art[i] == 1) sol++;
        }
        for(int i = 1; i <= n; i++) {
            G[i].clear();
            art[i] = vis[i] = d[i] = low[i] = 0;
        }
        cout << sol << '\n';
    }
    return 0;
}
