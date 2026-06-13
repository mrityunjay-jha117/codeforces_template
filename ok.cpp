#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF (1LL << 60)
#define endl '\n'
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define pi pair<int, int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpi vector<pair<int, int>>
#define ff first
#define ss second
#define FOR(i, n) for (int i = 0; i < (n); i++)
#define FOR1(i, n) for (int i = 1; i <= (n); i++)
#define FORR(i, n) for (int i = (n) - 1; i >= 0; i--)
#define FORE(x, v) for (auto& x : v)
const int MOD = 1e9 + 7;

int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b) {
  return (a / gcd(a, b)) * b;
}

int modpow(int a, int b, int mod = MOD) {
  int res = 1;
  a %= mod;
  while (b) {
    if (b & 1) res = (1LL * res * a) % mod;
    a = (1LL * a * a) % mod;
    b >>= 1;
  }
  return res;
}

const int MAXVAL = 5001;
const int MAXN = 3001;

struct Subsegment {
  int x, i;
};

vector<Subsegment> good_at_L[MAXN];
int min_i[MAXVAL];
int max_i[MAXVAL];
int last_pos_cnt[MAXVAL];
int cnt = 0;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  fill(min_i, min_i + MAXVAL, INT_MAX);
  fill(max_i, max_i + MAXVAL, INT_MIN);
  fill(last_pos_cnt, last_pos_cnt + MAXVAL, 0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int maxi = n / 2;
    for (int L = 1; L <= maxi; L++) good_at_L[L].clear();

    for (int i = 0; i < n; i++) {
      int mn = a[i], mx = a[i];
      cnt++;
      for (int j = i; j < n; j++) {
        if (last_pos_cnt[a[j]] == cnt) break;
        last_pos_cnt[a[j]] = cnt;

        if (a[j] < mn) mn = a[j];
        if (a[j] > mx) mx = a[j];

        if (mx - mn == j - i) {
          int L = j - i + 1;
          if (L >= 1 && L <= maxi) {
            good_at_L[L].push_back({mn, i});
          }
        }
      }
    }

    int ans = 0;

    for (int L = maxi; L >= 1; L--) {
      if (good_at_L[L].empty()) continue;

      static vector<int> modified_x;
      modified_x.clear();

      for (auto& s : good_at_L[L]) {
        int x = s.x;
        int pos = s.i;
        if (min_i[x] == INT_MAX) modified_x.push_back(x);
        if (pos < min_i[x]) min_i[x] = pos;
        if (pos > max_i[x]) max_i[x] = pos;
      }

      bool mila = false;
      for (int x : modified_x) {
        int next_x = x + L;
        if (next_x < MAXVAL && min_i[next_x] != INT_MAX) {
          if (max_i[next_x] - min_i[x] >= L || max_i[x] - min_i[next_x] >= L) {
            mila = true;
            break;
          }
        }
      }

      for (int x : modified_x) {
        min_i[x] = INT_MAX;
        max_i[x] = INT_MIN;
      }
      if (mila) {
        ans = L;
        break;
      }
    }
    cout << ans << endl;
  }

  return 0;
}