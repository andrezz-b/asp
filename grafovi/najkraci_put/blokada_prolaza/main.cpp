/*
 * Osnovna ideja je odrediti najjeftiniji put od prvog do zadnjeg stupca pri cemu cijena
 * koraka koji vodi na crno polje je 0 jer ga nije potrebno obojati, a cijena koraka
 * koji vodi na bijelo polje je 1. Algoritam: Dijkstra.
 *
 * Pretraga od prvog stupca do zadnjeg stupca, najkraci put ce predstavljati broj blokada
 * koje je potrebno postaviti. Cijena prolaska kroz bijelo polje (".") iznosi 1, a kroz
 * crno polje ("#") iznosi 0.
 *
 * Ovim pristupom cemo odrediti broj blokada koje je potrebno postaviti.
 */
#include <bits/stdc++.h>

using namespace std;

#define MAXN 1001

const int INF = 0x3f3f3f3f;

// Definicije pomaka do susjeda, sva polja koja dijele kut ili stranicu s trenutnim se smatraju susjedima
int dx[8] = {1,  1,  0, -1, -1, -1,  0,  1};
int dy[8] = {0, -1, -1, -1,  0,  1,  1,  1};

/*
 * Razmotrimo trenutno obilazak susjeda; u zadatku stoji da je put onaj kojeg je moguc
 * prolazak samo ako dva bijela polja dijele stranicu. Zasto onda gore imamo svih 8 susjeda
 * za obilazak. Pogledajmo primjer
 * .....
 * .#.##
 * ..#..
 * .....
 * U ovom primjeru mozemo postaviti blokadu na dva mjesta: na koordinate (0, 1) te (0, 2) i
 * time blokirati put. Posto nas algoritam trazi najmanji broj polja koje je potrebno
 * blokirati, dijagonalno blokiranje je moguce. Pa tako se odabirom blokade na (0, 2) ne
 * omogucava prolaz. Samim time, vidljivo je da se u pretrazi blokada moraju gledati i kutni
 * susjedi.
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    string a[MAXN];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Polje u kojem se u [i][j] spremaju cijene do sada najjeftinijih otkrivenih puteva do (i, j)
    int dist[MAXN][MAXN];
    memset(dist, 0x3f, sizeof(dist));

    // U najgorem slucaju, kad su sva polja bijela, potrebno je blokirati jedan cijeli redak (m elemenata)
    int ans = m;

    // min heap {udaljenost, {i, j}} <- Dijekstra: istražuju se polja i, j s trenutno najmanjom udaljenosti
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>> > pq;

    // Dodaj sva polja iz prvog stupca u priority queue, udaljenost od lijevog ruba ovisi o tome sta se nalazi u polju stupca, za bijela polja (".") cijena je 1, a za crna 0 ("#")
    for (int i = 1; i < n - 1; ++i) {
        // Segment a[i][0] == '.' vraca odgovarajucu cijenu, 1 za bijelo polje, 0 za crno
        pq.push({a[i][0] == '.', {i, 0}});
    }

    while (!pq.empty()) {
        // Varijable za dohvacanje podataka iz pq-a
        // u - par koordinati i, j
        // d - udaljenost od lijevog ruba
        pair<int, int> u;
        int d;
        tie(d, u) = pq.top();

        int i, j;
        tie(i, j) = u;
        pq.pop();

        // Ako je trenutno polje (i, j) već obidjeno preskoci provjeru
        if (dist[i][j] < d) continue;

        // Ako nije obidjeno relaksiraj udaljenost - postavljamo ju na trenutnu udaljenost
        // Ovo se temelji na znacajci djikstre da se po prvom posjetu nekog cvora ono najkraceg puta
        dist[i][j] = d;

        // Prvi put kad se dospije u zadnji stupac to je rjesenje problema, najkraca udaljenost predstavlja najmanji broj blokada koje je potrebno postaviti, odnosno najmanji broj bijelih polja u putu
        if (j == m - 1) {
            ans = d;
            break;
        }

        // Prolazimo svakog od 8 susjeda (I, J) i dodajemo u pq
        for (int di = 0; di < 8; ++di) {
            // Koristeci pomake dx i dy odredimo nove kooridnate tocaka
            int I = i + dx[di];
            int J = j + dy[di];

            // Provjeravamo ako se te koordinate nalaze unutar mape. Ako su izvan, preskoci
            if (I < 0 || I >= n || J < 0 || J >= m) continue;

            // Ako je trenutna udaljenost susjednog polja (I, J) preko trenutnog polja (i, j) veca od postojece preskoci
            if (dist[I][J] <= d + (a[I][J] == '.')) continue;

            // Inace, ako je dio puta, relaksiraj i ubaci ih (potencijalno ponovno) u pq
            dist[I][J] = d + (a[I][J] == '.');
            pq.push({dist[I][J], {I, J}});
        }
    }

    cout << ans << endl;
    return 0;
}