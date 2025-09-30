#include <bits/stdc++.h>
using namespace std;

struct State {
  int len = 0;
  int link = -1;
  unordered_map<int, int> next;
};

struct SuffixAutomaton {
  vector<State> st;
  int last = 0;
  SuffixAutomaton() {
    st.reserve(256);
    init();
  }
  void init() {
    st.clear();
    st.push_back(State());
    st[0].link = -1;
    last = 0;
  }
  void extend(int c) {
    int cur = (int)st.size();
    st.push_back(State());
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
      st[p].next[c] = cur;
      p = st[p].link;
    }
    if (p == -1) {
      st[cur].link = 0;
    } else {
      int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len) {
        st[cur].link = q;
      } else {
        st.push_back(st[q]);
        int clone = (int)st.size() - 1;
        st[clone].len = st[p].len + 1;
        while (p != -1 && st[p].next[c] == q) {
          st[p].next[c] = clone;
          p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }

  int longest_common_with_row(const vector<string> &row, const unordered_map<string, int> &idmap) {
    int v = 0, l = 0, best = 0;
    for (auto &tok : row) {
      auto it = idmap.find(tok);
      if (it == idmap.end()) {
        v = 0;
        l = 0;
        continue;
      }
      int c = it->second;
      if (st[v].next.count(c)) {
        v = st[v].next.at(c);
        l++;
      } else {
        while (v != -1 && !st[v].next.count(c)) v = st[v].link;
        if (v == -1) {
          v = 0;
          l = 0;
        } else {
          l = st[v].len + 1;
          v = st[v].next.at(c);
        }
      }
      best = max(best, l);
    }
    return best;
  }
};

vector<vector<string>> sort_by_lcs_with_a(const vector<string> &a, vector<vector<string>> grid) {
  unordered_map<string, int> id;
  int nextId = 1;
  for (auto &tok : a)
    if (!id.count(tok)) id[tok] = nextId++;
  SuffixAutomaton sa;
  for (auto &tok : a) sa.extend(id[tok]);

  int n = (int)grid.size();
  vector<int> score(n);
  for (int i = 0; i < n; ++i) score[i] = sa.longest_common_with_row(grid[i], id);

  vector<int> idx(n);
  iota(idx.begin(), idx.end(), 0);
  stable_sort(idx.begin(), idx.end(), [&](int x, int y) { return score[x] > score[y]; });

  vector<vector<string>> ans;
  ans.reserve(n);
  for (int i : idx) ans.push_back(move(grid[i]));
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  if (!(cin >> n)) return 0;

  // read 'a' of size n
  vector<string> a;
  a.reserve(n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    a.push_back(s);
  }

  // now read m (number of rows)
  int m;
  if (!(cin >> m)) return 0;

  vector<vector<string>> grid;
  grid.reserve(m);
  for (int i = 0; i < m; ++i) {
    int sz;
    cin >> sz;
    vector<string> row;
    row.reserve(sz);
    for (int j = 0; j < sz; ++j) {
      string t;
      cin >> t;
      row.push_back(t);
    }
    grid.push_back(move(row));
  }

  auto sorted = sort_by_lcs_with_a(a, grid);

  for (auto &row : sorted) {
    for (size_t i = 0; i < row.size(); ++i) {
      if (i) cout << ' ';
      cout << row[i];
    }
    cout << endl;
  }
  return 0;
}
