#include <bits/stdc++.h>

#define nl      "\n"
#define pb      push_back
#define ll      long long
#define all(a)  a.begin(),a.end()
#define INF     LONG_LONG_MAX

using namespace std;

class Flow {
    int n;
    vector<vector<int>> capacity;
    vector<vector<int>> adj;

public:

    Flow(int _n) {
        n = _n;
        capacity.resize(n, vector<int>(n, 0));
        adj.resize(n);
    }

    void addEdge(int u, int v, int cap){
        capacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int bfs(int s, int t, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = s;
        queue<pair<int, int>> q;
        q.push({s, INT_MAX});

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > 0) {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) {
        int flow = 0;
        vector<int> parent(n);
        int new_flow;

        while ((new_flow = bfs(s, t, parent)) != 0) {
            flow += new_flow;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }

        return flow;
    }

};

int main() {
    int n, k;
    cin >> n >> k;
    int s = 0, t = 1;
    Flow f((n + 1) * (n + 1));
    while (k--) {
        int x, y;
        cin >> x >> y;
        if ((x + y) & 1) {
            f.addEdge(x * n + y, t, 1);
        } else {
            f.addEdge(s, x * n + y, 1);
            int hx, hy;

            hx = x + 1; hy = y + 2;
            if (hx >= 1 && hy >= 1 && hx <= n && hy <= n) f.addEdge(x * n + y, hx * n + hy, 1);

            hx = x + 1; hy = y - 2;
            if (hx >= 1 && hy >= 1 && hx <= n && hy <= n) f.addEdge(x * n + y, hx * n + hy, 1);

            hx = x - 1; hy = y + 2;
            if (hx >= 1 && hy >= 1 && hx <= n && hy <= n) f.addEdge(x * n + y, hx * n + hy, 1);

            hx = x - 1; hy = y - 2;
            if (hx >= 1 && hy >= 1 && hx <= n && hy <= n) f.addEdge(x * n + y, hx * n + hy, 1);

            hx = x + 2; hy = y + 1;
            if (hx >= 1 && hy >= 1 && hx <= n && hy <= n) f.addEdge(x * n + y, hx * n + hy, 1);

            hx = x + 2; hy = y - 1;
            if (hx >= 1 && hy >= 1 && hx <= n && hy <= n) f.addEdge(x * n + y, hx * n + hy, 1);

            hx = x - 2; hy = y + 1;
            if (hx >= 1 && hy >= 1 && hx <= n && hy <= n) f.addEdge(x * n + y, hx * n + hy, 1);

            hx = x - 2; hy = y - 1;
            if (hx >= 1 && hy >= 1 && hx <= n && hy <= n) f.addEdge(x * n + y, hx * n + hy, 1);
        }
    }
    cout << f.maxFlow(s,t) << nl;
    return 0;
}