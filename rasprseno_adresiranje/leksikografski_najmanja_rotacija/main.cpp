#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000001
typedef long long ll;

const int MOD = 1e9 + 7;
string s;
int n, h[MAXN * 2], p[MAXN * 2];

// vraca hash vrijednost za podniz koji pocinje u indeksu i duljine je l
ll hsh(int i, int l) {
  ll ret = (ll)h[i - 1 + l] - (i ? (ll)h[i - 1] * p[l] : 0);
  ret %= MOD;
  if (ret < 0) ret += MOD;
  return ret;
}

// Duljina najduljeg zajednickog prefiksa za niz koji pocinje u indeksu i
// te niz koji pocinje s indeksom j.
// binarno pretrazivanje
int lcp(int i, int j) {
  int lo = 0, hi = n + 1;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    if (hsh(i, mid) == hsh(j, mid)) lo = mid;
    else hi = mid;
  }
  return lo;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> s;
  // Udvostruciti s kako bi se olaksalo rotiranje - rotiranje postaje pomak u desno.
  s = s + s;
  // Predizracunaj hasheve i potencije baze.
  for (int i = 0; i < n * 2; ++i) {
    h[i] = i ? ( (ll)h[i - 1] * 127 + s[i]) % MOD
           : s[0];
    p[i] = i ? ( (ll)p[i - 1] * 127) % MOD
           : 1;
  }
  int mn = 0;
  for (int i = 1; i < n; ++i) {
    // Duljine najduljeg zajednickog prefiksa za nizove koji su rotirani za i te za mn.
    int k = lcp(i, mn);
    // Prvi znak koji se razlikuje izmedju trenutno minimalnog niza koji ima mn rotacija
    // i trenutnog niza sa i rotacija je s[mn+k] odnosno s[i+k]. Ako je s[i+k] manji
    // tada je novi minimalni broj rotacija i.
    if (k < n && s[i + k] < s[mn + k]) mn = i;
  }
  cout << mn << endl;
  return 0;
}