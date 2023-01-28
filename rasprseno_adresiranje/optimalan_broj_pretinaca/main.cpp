#include <bits/stdc++.h>

using namespace std;

#define MAXN 100
#define ALPHA 127

struct HashTable {
    explicit HashTable (int size) : size(size) {
        table.resize(size);
    }
    vector<string> table;
    int size;

    int hash(string &k) {
        int ret = 0;
        for (auto c : k) {
            ret += ret * ALPHA + (int)c;
            ret %= size;
        }
        return ret;
    }

    int oahash(string &key, int i) {
        return (hash(key) + (i + (long long)i * i) / 2) % size;
    }

    pair<int, int> insert(string &key) {
        for (int i = 0; i < size; i++) {
            int slot = oahash(key, i);
            if (table[slot] == "") {
                table[slot] = key;
                return make_pair(slot, i);
            } else if (table[slot] == key) {
                return make_pair(slot, i);
            }
        }
        return make_pair(-1, -1);
    }

    string get(string &k) {
        for (int i = 0; i < size; i++) {
            int slot = oahash(k, i);
            if (table[slot] == "") break;
            if (table[slot] == k) {
                return table[slot];
            }
        }
        return "";
    }
};
/**
 * Zadatak: Za veličine tablica između mlo i mhi
 * treba vidjetit koja će pri umetanju svih elemenata vratiti
 * najmanji broj ispitivanja, -> povratna vrijednost metode insert, 2. element para
 * (ako nisu umetnuti svi elementi tablica se ne računa)
 * 
 * */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int mlo, mhi, n;
    cin >> n >> mlo >> mhi;

    string keys[MAXN];
    for (int i = 0; i < n; ++i) {
        cin >> keys[i];
    }
    int optimalSize = 0, minNumberOfChecks = INT_MAX;
    for (int size = mlo; size <= mhi; ++size) {
        HashTable ht(size);
        int numberOfChecksCurrent = 0;
        bool all_inserted = true;
        for (int i = 0; i < n; ++i) {
            int slot, checksForKey;
            tie(slot, checksForKey) = ht.insert(keys[i]);
            all_inserted = slot != -1;
            numberOfChecksCurrent += checksForKey;
        }

        // Ako ih ne možemo sve staviti ne razmatramo tu tablicu
        if (all_inserted && numberOfChecksCurrent < minNumberOfChecks) {
            minNumberOfChecks = numberOfChecksCurrent;
            // odgovor je ta velicina tablice
            optimalSize = size;
        }
    }

    cout << optimalSize << endl;

    return 0;
}