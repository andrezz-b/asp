# ASP Završni

## Binarno stablo

Za binarno stablo s  n  čvorova te visine  h  vrijedi:
- $h + 1 \leq n \leq 2^{h + 1}-1$
- $\log_{2}(n+1)-1 \leq h \leq n - 1$  

Maksimalna visina stabla s  $n$  čvorova je  $n  −  1$

**Razina/Dubina**: udaljenost od korijena do čvora
**Visina**: udaljenost od lista do čvora 

### Obilazak
#### Preorder
- čvor, lijevo, desno
- prefix izraz

#### Post-order
- lijevo, desno, čvor
- postfix izraz

#### In-order
- lijevo, čvor, desno
- infix izraz

#### Shunting-Yard algoritam
- slova dodaj u postfix izraz
- operatore dodaj na stog
	-  kada se operator dodaje na stog sve operatore većeg prioriteta od onoga kojeg dodajemo stavi u postfix izraz
- `(` - otvorenu zagradu dodaj na stog, kada dođe zatvorena zagrada `)` sve sa stoga do otvorene zagrade dodaj u postfix izraz
```cpp
string infix2postfix(string infix) {
  Stack<char> buffer(MAXN);
  std::string postfix = "";
  
  for (auto c : infix) {
  // Slova idu u postfix izraz
    if (isalpha(c)) {
      postfix += c;
    } else if (is_operator(c)) {
    // Provjera prioritea operatora sa stoga
      while (!buffer.is_empty() && priority(buffer.top()) >= priority(c)) {
        postfix += buffer.top();
        buffer.pop();
      }
      buffer.push(c);
    } else if (c == '(') {
      buffer.push(c);
    } else if (c == ')') {
    // Izbacivanje svega sa stoga do otvorene zagrade
      while (buffer.top() != '(') {
        postfix += buffer.top();
        buffer.pop();
      }
      buffer.pop();
    }
  }
  // Ako nesto preostane u stogu dodaj u postfix izraz
  while (!buffer.is_empty()) {
    postfix += buffer.top();
    buffer.pop();
  }
  
  return postfix;
}
```

## Binarno stablo pretraživanja
- prosječna dubina čvora $\log(n)$, najgora $n - 1$ (stablo je lista)
- in-order prolazak - sortirani niz (rastući)
- reverse in-order prolazak - sortirani niz (padajući)
### Prethodnik
- najveći element lijevog podstabla
- ako nema lijevog podstabla - prvi element kojem sam ja u desnom podstablu

### Nasljednik
- najmanji element desnog podstabla
- ako nema desnog podstabla - prvi element kojem sam ja u lijevom podstablu

### Brisanje elemenata
- 0 djece - normalno samo pobriši
- 1 dijete - stavi dijete na moje mjesto
- 2 djece -  nasljednika stavi na moje mjesto (ako nasljednik ima djece obavi brisanje s 1 dijeteom)

## Balansirana binarna stabla
- Faktor ravnoteže (balance factor  ) - razlika između visine lijevog i  
desnog podstabla čvora

### AVL Stablo

- visine lijevog i desnog podstabla svakog  čvora razlikuju najviše za 1
- Primjena kod baza podataka gdje je bitno vrijeme dohvata podatka

#### Lijevo lijevo
- faktor ravnoteže mene i mog lijevog djetata je pozitivan (left heavy)
- desna rotacija mene i mog lijevog djeteta

#### Desno desno
- faktor ravnoteže mene i mog desnog djetata je negativan (right heavy)
- lijeva rotacija mene i mog desnog djeteta

#### Lijevo desno
- moj faktor ravnoteže je pozitivan, ali mog lijevog djeteta je negativan (dijete - right heavy)
- prvo lijeva rotacija djeteta (imamo podslučaj *desno desno*) 
- onda postajemo left heavy pa rješavamo kao u **lijevo lijevo**

#### Desno lijevo
- moj fakto ravnoteže je negativan, ali mog desnog djeteta je pozitivan (dijete - left heavy)
- prvo desna rotacija djeteta (podslučaj *lijevo lijevo*)
- onda postajemo right heavy pa rješavamo kao u **desno desno**

#### Brisanje elemenata
- kao u BST samo se penjemo prema korijenu i balansiramo gdje je potrebno

### Crveno-crno stablo
- postoje listovi s vrijednostima i oni imaju NIL listovu koji su crni
- ako je čvor crven djeca moraju biti crna
- svaki put od nekog čvora do njegovih listova mora imati isti broj crnih čvorova
- Primjena kod većine stablastih struktura podataka (map, multimap,  
set, multiset ...)

## LCRS stabla
- složenost operacija (dodavanje, brisanje, pretraga): $O(n)$
- primjene:
	- potreba za korištenje stabla s više djece
	- memorijska učinkovitost
	- nije potreban direktan pristup djeci

## Stoblo
- 'stablo prefiksa'
- može biti implementirano kao LCRS stablo
- Bitovno stoblo (Bitwise Trie) - bitovi umjesto znakova
- Kompresirana stobla (Compressed / Radix Trie) - čvorovi sa samo  
jednim djetetom se spajaju  
- složenost operacija (dodavanje, brisanje, pretraga): $O(m)$
	- $m$ duljina riječi koja se dodaje
- memorijska složenost: $O(k\cdot n)$
 - primjene:
	- leksikografsko sortiranje
	- internet pretraživači
	- IP routing

## Gomila
### Pronalazak elementa
- najmanji / najveći element na vrhu $O(1)$

### Dodavanje elementa
- prvo slobodno lijevo mjesto
- radi se bubble up - usporedba s roditeljom i zamjena ovisno o vrsti gomile
- $O(\log(n))$
### Brisanje elementa
- briše se korijen - stavi zadnji element na njegovo mjesto
- radi se bubble down - usporedba s djecom i zamjena ovisno o vrsti gomile
- $O(\log(n))$
## Sortiranje

### Bubble sort
- optimizacija:
	- Nakon  *i*-tog ponavljanja posljednjih  *i*  elemenata je sortirano
	- ako nije bilo zamjena može se završiti
- $O(n^2)$
- Stabilan algoritam
	- Dva ili više slogova istih ključeva zadržvaju isti relativni poredak u  
sortiranom nizu
-  **primjene**:
	- nebitna složenost
	- kratak i jednostavan

```cpp
void bubble_sort(int array[], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 1; j < size; j++) {
      if (array[j - 1] < array[j]) {
        int tmp = array[j - 1];
        array[j - 1] = array[j];
        array[j] = tmp;
      }
    }
  }
}
```
### Selection sort
- $O(n^2)$
- **Nije** stabilan algoritam
-  **primjene**:
	- sortiranje kratke liste podataka
	- broj zapisa u memoriju je bitan (malen broj zamjena)

```cpp
void selection_sort(int array[], int n) {
  for (int i = 0; i < n - 1; i++) {
    int min = i;
    for (int j = i + 1; j < n; j++) {
      if (array[min] > array[j]) {
        min = j;
      }
    }
    
    int tmp = array[min];
    array[min] = array[i];
    array[i] = tmp;
  }
}
```
### Insertion sort
- $O(n^2)$
- Stabilan algoritam
-  primjene:
	- niz je uglavnom sortiran

```cpp
void insertion_sort(int a[], int n) {
	for (int i = 1; i < n; ++i) {
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && key < a[j]) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
```

### Merge sort
- Vremenska složenost - $O(n \cdot \log(n))$
- Memorijska složenost - $O(n)$ dodatno polje za spajanje
- Stabilan algoritam

```cpp
void merge(int *array, int *temp, int lstart, int rp, int re) {
  int le = rp - 1;
  int lp = lstart;
  int tp = lstart;

  while ((lp <= le) && (rp <= re)) {
    // Ako je lp manji od rp njega stavi u polje i 
    // povecaj tp inace stavi rp
    if (array[lp] <= array[rp]) {
      temp[tp++] = array[lp++];
    } else {
      temp[tp++] = array[rp++];
    }
  }

  // Ako ostane nesto u lijevom to iskopriaj 
  // ako nema niceg nece uci u while
  while (lp <= le) {
    temp[tp++] = array[lp++];
  }

  // Ako ostane nesto u desnom to iskopiraj 
  // ako nema niceg nece uci u while
  while (rp <= re) {
    temp[tp++] = array[rp++];
  }

  // Nakon svih dodavanja rp ce pokazivat na 
  // 1 element iza zadnjeg
  // a mora pokazivati bas na zadnji element
  --rp;

  // Vrati sve iz pomocnog polja u pravo polje
  while (rp >= lstart) {
    array[rp] = temp[rp];
    --rp;
  }
}

void merge_sort(int *array, int *temp, int l, int r) {
  if (l < r) {
    int mid = (l + r) / 2;

    merge_sort(array, temp, l, mid);
    merge_sort(array, temp, mid + 1, r);

    merge(array, temp, l, mid + 1, r);
  }
}
```

### Quick sort
- Vremenska složenost 
	- prosječna - $\theta(n \cdot \log(n))$
	- najgora - $O(n^2)$ - pivot ekstreman po vrijednosti
- Memorijska složenost - ovisi o implementaciji 
	-  za kod dolje $O(1)$
- Stabilnost ovisi o implementacija algoritam
	-  za kod dolje nije stablian

```cpp
void quick_sort(int *array, int l, int r) {
  int pivot = random_int(l, r + 1);
  int pivotValue = array[pivot];

  std::swap(array[pivot], array[r]);

  int i = l - 1;
  // Svi manji od pivota idu lijevo, 
  // a svi veći idu desno
  for (int j = l; j < r; ++j) {
    if (array[j] <= pivotValue)  {
      i++;
      std::swap(array[i], array[j]);
    }
  }
	// Stavi pivota na pravu poziciju
  std::swap(array[++i], array[r]);
  // Ako je nesto preostalo u lijevom dijelu
  if (l < i) quick_sort(array, l, i - 1);
  // Ako je nesto preostalo u denso dijelu
  if (i < r) quick_sort(array, i + 1, r);
}
```

### Heap sort
- vremenska složenost - $O(n \cdot \log(n))$
- memorijska složenost
	- $O(1)$ - ako stavljamo sortirane elemente na kraj gomile
- rastući poredak - **max heap**
- padajućo poredak - **min heap**
```cpp
void heap_sort(int *array, int heap_size) {
  // Izrada gomile, bubble up
  for (int i = 0; i < heap_size; ++i) {
    int j = i;
    while (j != 0 && array[PARENT(j)] < array[j]) {
      std::swap(array[PARENT(j)], array[j]);
      j = PARENT(j);
    }
  }
  while (heap_size > 0) {
    // heap_size pokazuje na elemnt izvan niza
    heap_size--;
    // stavljamo prvi element na svoju poziciju na kraj
    std::swap(array[0], array[heap_size]);
    // novi element sa kraja moramo bubble down-at na dobru poziciju
    max_heapify(array, 0, heap_size);
  }
}
```

## Sortiranje bez usporedivanja
### Counting sort
- vremenska složenost - $O(n + k)$
	- $k$ - najveći očekivani broj
- memorijska složenost - $O(max)$ - moramo imati kutija za sve elemente do najvećeg
-  **primjene**:
	- Sortiranje velikog broja manjih cijelih brojeva
	- potreba za linearnom vremenskom složenosti

### Radix sort
- vremenska složenost - $O(d(n + k))$
	- $d$ - broj znamenki
- memorijska složenost - $O(max)$ dodatno polje
-  **primjene**:
	- Sortiranje brojeva velikog raspona

### Bucket sort
- vremenska složenost 
	- Najbolji slučaj - $\Omega(n + k)$
		- elementi jednako raspoređeni po svim kutijama
		- $O(n)$ - složenost izrada kutija
		- $O(k)$ - složenost sortiranja svake kutije
	- Najgori slučaj - $O(n^2)$
		- ako elementi odgovaraju istom ključu i završavaju u istoj kutiji
		- složenost ovisi o algoritmu sortiranja kutija
- memorijska složenost - $O(n + k)$ dodatno polje
-  **primjene**:
	- Sortiranje brojeva uniformnog raspršenja
	- sortiranje decimalnih brojeva

## Grafovi
### Primjene
- Komunikacije:
	- telekomunikacijske mreže
	- mobilne komunikacije
	- VoIP
- Networking
	- Internet
- Mreže senzora
- Društvene mreže
- Neuronske mreže
- Proteinske veze
- Međuovisnosti softverskih modula

### Reprezentacija grafova

#### Matrica susjedstava
- redovi i stupci su indeksirani po čvorovima

Memorijska složenost:
- **neučinkovito** kada graf ima **malo bridova** 
	- matrica ispunjena 0 - neiskorištena memorija
- memorijska složenost $O(n^2)$

 Vremenska složenost:
- sporo **dodavanje i brisanje čvorova** - potrebno je kopirati matricu - $O(n^2)$
- brze **operacije s bridovima** jer se u matricu samo stavlja 1 ili 0 - $O(1)$  
 
 
#### Lista susjedstava
-	polje je indeksirano po čvorovima

Memorijska složenost:
-	memorijska složenost: $O(n + m)$, $m$ - broj bridova
	-	polje za sve čvorove treba $O(n)$ memorije
	-  ostatak memorije ovisi koliki je zbroj stupnjeva svih čvorova

Vremenska složenost:
- sporo **brisanje čvorova** - $O(m)$
	- treba pronaći svaki njegov brid s drugim čvorovima i izbrisat ga
- sporo **brisanje bridova** - $O(n)$
- brzo **dodavanje brida ili čvora** - $O(1)$
	- samo se doda na kraj polja


#### Matrica incidencije
- redovi su indeksirani po čvorovima, a stupci po bridovima
	- `A[x][y] = -1` - brid *y* izlazi iz čvora *x*
	- `A[x][y] = 1` - brid *y* ulazi u čvor *x*

Memorijska složenost: 
- **neunčikovito** kada graf ima **puno čvorova**
	- svaki brid povezuje 2 čvora pa ćemo imati velike stupce sa samo dvije 1
- memorijska složenost - $O(n \cdot m)$

Vremenska složenost:
 - sporo **dodavanje čvorova i bridova**, sporo **brisanje čvorova i bridova** - $O(n \cdot m)$
	 - treba kopirati matricu

### Obilazak grafa

#### Dijkstra
- originalna implementacija algoritma ne pronalazi najkraće puteve na usmjerenim grafovima s negativnim težinama
	- svaki se čvor doda u prioritetni red samo 1 pa se ne može dogoditi da put kasnije s negativnim bridom bude manji
	- naša implementacija može naći najkraći put jer više puta dodaje čvorove u prioritetni red
- **ne može detektirati negativni ciklus** - beskonačna petlja
- **vremenska složenost** - $O(n^2)$

#### Bellman-ford
- opušta svaki od bridova $n - 1$ puta
	- računa udaljenost do nekog čvora temeljem težine od ishodišta
	- nakon $n - 1$ puta sigurno su sve udaljenosti najmanje (može se dogoditi i prije, ali ovo garantira)
- **detektira negativni ciklus**
	- ako se nakon tih $n - 1$ puta prođe ponovno kroz graf i traže se manje udaljenosti ne bi se smjele naći opet manje, ako se nađu onda je to negativni ciklus
- **vremenska složenost** - $O(n \cdot m)$ ~ $O(n^3)$

#### A* algoritam
- razvijen za problem navigacije robota
- koristi heuristički pristup
	- računa se estimacija cijene puta do susjednog čvora $n$ - $f(n)$
	- $f(n) = g(n) + h(n)$
		- $g(n)$ - težinska udaljenost (ono kao kod dijkstre)
		- $h(n)$ - heuristička estimacija cijene puta od čvora do odredišta
- $f(n)$ se potom koristi pri obilasku kod Dijkstre

#### Floyd-Warshall algoritam
- udaljenosti za svaki čvor do svih ostalih čvorova

#### Single-source shortest path
- put od ishodišta do svih čvorova
- kod netežnskih najkraći put daje BFS
- kod težinskih **Dijkstra** i **Bellman-ford**

#### Single-pair shortest path
- put od ishodišta do odredišta
- posebna verzija *Single-source shortest path* gdje imamo zadano odredište - možemo riješiti na isti način
- poznavanjem odredišta možemo koristiti heuristiku - **A\* algoritam**

#### Single-destination shortest path
- put od svih čvorova do odredišta
- možemo promatrati kao *Single-source shortest path*
	- rješavanje pomoću **Dijkstre** ili **Bellman-Forda**
- **neusmjereni grafovi** 
	- samo obrnemo odredište i ishodište
- **usmjereni grafovi**
	- obrnemo odredište i ishodište
	- obrnemo smjer svih bridova

#### All-pairs shortest path
- računanje udaljenosti svih parova čvorova
- koristi se **Floyd-Warshall algoritam**

### Topološko sortiranje
- sortiranje čvorova u ovisnosti o prethodnicama
	- usmjereni aciklički graf (*Directed Acyclic Graph - DAG*)
- moguće i kod nepovezanih grafova
- više mogućih rješenja
- primjene - Međuovisnosti softverskih modula

## Dinamičko programiranje
- metoda pojednostavljanja složenih problema
- rastavljamo složeni problem na jednostavnije potprobleme

**Iscrpno pretraživanje** (*Exhaustive search*)
- isprobamo sve moguće kombinacije i odaberemo rješenje koje nam odgovara

**Pohlepno pretraživanje** (*Greedy search*)
- odaberemo onaj element koji u trenutnoj iteraciji izgleda optimalno (lokalni optimalni izbor)
- ne rezultira nužno optimalnim rješenjem

### Uvjeti
Optimalna podstruktura (*optimal substructure*):
- optimalno rješenje osnovnog problema sadrži optimalna rješenja potproblema
- ako se može formulirati rekurzivni izraz za iscrpno pretraživanje

Preklapajući potproblemi (*overlapping sub-problems*):
- mali broj zasebnih potproblema
- rješenja potproblema se više puta traže

### Pristupi

#### Top-down pristup (memoizacija)
- normalna rekurzija i memoizacijska tablica
1. rekurzija vraća rješenje
	- osnovni slučaj ili napredak
2. rješenje se zapisuje u memoizacijsku tablicu
3. kada dođemo na isti potproblem dohvaćamo rješenje iz tablice te ga ne moramo ponovno računati

Prednosti:
- jednostavna modifikacija rekurzije
- izračunava potprobleme samo kad je potrebno

Nedostatci:
- sporije ako je puno potproblema zbog rekurzivnih poziva
- veličina tablice ne može biti optimizirana - spremaju se sva stanja

#### Bottom-up pristup (tabuliranje)
- Pripremiti tablicu koja ima onoliko prostora koliko ima različitih stanja
1. Prepoznati topološki poredak poopunjavanja tablice
2. Popuniti inicijanle vrijednosti
3. Nastaviti popunjavati vrijednosti pomoću prethodno izračunatih

Prednosti:
- brže ako je puno potproblema
- može se uštediti memorija ako se za izračun stanja koristi samo dio prethodnih

Nedostatci:
- neintuitivna metoda
- posjećuje sva stanja
