#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define inf (1LL << 60)
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define pi pair<int, int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpi vector<pair<int, int>>
#define ff first
#define ss second
// Loop macros
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

int power(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res *= a;
    a *= a;
    b >>= 1;
  }
  return res;
}

int modpow(int a, int b, int mod = MOD) {
  int res = 1;
  a %= mod;
  while (b) {
    if (b & 1) res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res;
}

// ---------------- Debug & Printing ----------------
template <typename T>
void print1D(const vector<T>& v) {
  FORE(x, v) cout << x << ' ';
  cout << endl;
}

template <typename T>
void print2D(const vector<vector<T>>& mat) {
  FORE(row, mat) {
    FORE(x, row) cout << x << ' ';
    cout << endl;
  }
}

// ---------------- Main ----------------
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> v(n);
    int count_of_zero = 0;
    for (auto& it : v) {
      cin >> it;
      if (it == 0) count_of_zero++;
    }
    // if the vector has more than equal to
    // two zeroes then then indices +1
    if (count_of_zero >= 2) {
      int i = 0;
      while (v[i] != 0) i++;
      int j = n - 1;
      while (v[j] != 0) j--;
      cout << j - i + 1 << endl;
      continue;
    }
    // if the vector has only zero and it is
    // the remaining number
    // int expected_sum = (n) * (n + 1) / 2;
    // int calculated_sum = accumulate(v.begin(), v.end(), 0);
    // int remaining = calculated_sum - expected_sum;
    // getting the first unsorted element
    int start = -1;
    int end = 0;
    for (int i = 0; i < n;i++){
      if(v[i]!=i+1 && v[i]!=0){
        if(start==-1){
          start = i;
        }else{
          end = i;
        }
      }
    }
    if (end == 0) cout << "0" << endl;
    else
      cout << end - start + 1 << endl;

    // ab peeche se aana chalu
  }
  return 0;
}