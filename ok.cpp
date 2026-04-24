#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<vector<int>> adj;
vector<int> vis, par;
int start = -1, endd = -1;
void dfs(int node, int parent) {
  vis[node] = 1;
  par[node] = parent;
  for (auto& it : adj[node]) {
    if (it == parent) continue;
    if (!vis[it]) {
      dfs(it, node);
      if (endd != -1) return;
    } else {
      start = it;
      endd = node;
      return;
    }
  }
}
signed main() {
  int n, m;
  cin >> n >> m;
  adj.resize(n + 1);
  vis.resize(n + 1, 0);
  par.resize(n + 1, -1);
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i, -1);
      if (endd != -1) break;
    }
  }
  if (start == -1) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  vector<int> ans;
  ans.push_back(start);
  int curr = endd;
  while (curr != start) {
    ans.push_back(curr);
    curr = par[curr];
  }
  ans.push_back(start);
  reverse(ans.begin(), ans.end());
  cout << ans.size() << endl;
  for (auto& it : ans) cout << it << " ";

  return 0;
}