#include <iostream>

struct Cvor {
  int val;
  Cvor *next, *prev;

  Cvor(int val) {
    this->val = val;
    next = NULL;
    prev = NULL;
  }
};

void swap_nodes(Cvor **a, Cvor **b) {
  Cvor *tmp = *a;
  *a = *b;
  *b = tmp;
}

struct Stog {
  Cvor *head, *half, *end;
  int size;

  Stog()
    : head(NULL), half(NULL), end(NULL), size(0)
  {}

  void push(int val) {
    // implementirati funkciju push, pratiti half, head i end pokazivace
    // paziti na velicinu size
    Cvor *newNode = new Cvor(val);

    if (!size) {
      // Ako je veličina 0 svi pokazuju na na novi element
      head = newNode;
      half = newNode;
      end = newNode;
      size++;
    } else {
      size++;
      // Inače dodajemo novi element na kraj te ga spajamo s prev i next
      head->next = newNode;
      newNode->prev = head;
      head = newNode;
      /*
       * Half je uvijek prvi element ako bi se napravio permute
       * Parna veličina: 1 2 3 4 -- Neparna veličina: 1 2 3 4 5
       *                     ^                            ^
       * zato ga samo pomičemo kada dođemo na parnu veličinu jer se tada
       * granica pomiče kako zaokružujemo na niže
       * 1 2 3    ->      1 2 3 4      ->    1 2 3 4 5
       *   ^                  ^                  ^
       *     N -> P                  P -> N
       * pa pomičemo u Naprijed     ostaje na istom mjestu
       * N - neparna veličina, P - parna veličina
       */
      half = !(size % 2) ? half->next : half;
    }
  }

  void pop() {
    if (size <= 0) return;

    if (size == 1) {
      // Ako je trenutna veličina 1, znači da brisanjem brišemo
      // sve elemente niza pa sve pokazivače stavljamo na NULL
      size--;
      delete end;
      head = NULL;
      end = NULL;
      half = NULL;
    } else {
      size--;
      Cvor *tmp = head;
      head = head->prev;
      head->next = NULL;

      delete tmp;
      /*
       * Half je uvijek prvi element ako bi se napravio permute
       * Parna veličina: 1 2 3 4 -- Neparna veličina: 1 2 3 4 5
       *                     ^                            ^
       * kada brišemo elemnt idemo suprotno nego kad dodajemo
       * pa half mičemo unazad kada dođemo na neparnu veličinu
       * 1 2 3 4 5   ->      1 2 3 4      ->    1 2 3
       *     ^                   ^                ^
       *           N -> P               P -> N
       *   ostaje na istom mjestu    pomičemo za 1 unazad
       * N - neparna veličina, P - parna veličina
       */
      half = size % 2 ? half->prev : half;
    }
  }

  void permute() {
    if (size <= 1) return;

    head->next = end;
    end->prev = head;

    swap_nodes(&end, &half);
    /*
     * Kod permutacije neparne veličine liste half završi jedno
     * mjesto unaprijed pa se mora pomaknuti unazad
     *
     * Permutacija neparne veličine:
     * 1 2 3 4 5 -> 3 4 5 1 2 -> 5 1 2 3 4
     * ^   ^        ^   ^        ^     ^
     * E   H        H   E        E     H
     *
     * Kod permutacije parne veličine half završi na dobroj poziciji
     *
     * Permutacija parne veličine:
     * 1 2 3 4 -> 1 2 3 4 -> 3 4 1 2
     * ^   ^      ^   ^      ^   ^
     * E   H      H   E      E   H
     * 
     * E - end, H - half
     */
    half = size % 2 ? half->prev : half;

    head = end->prev;
    end->prev = NULL;
    head->next = NULL;
  }

  void ispis() {
    std::cout << size << "\n";
    if (size <= 0) return;

    for (Cvor *curr = end; curr != NULL ; curr = curr->next) {
      std::cout << curr->val << " ";
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(true);
  std::cin.tie(NULL);

  int n;
  Stog *p = new Stog();
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    char c;
    std::cin >> c;

    if (c == 'd') {
      int x;

      std::cin >> x;

      p->push(x);
    } else if (c == 'o') {
      p->pop();
    } else {
      p->permute();
    }
  }

  p->ispis();

  return 0;
}