#include <iostream>
#include <cstring>

#define MAXS 10001

const char M[3] = "([";

struct Stog {
    char *arr;
    int top;

    char *getStog() {
        return arr;
    }

    Stog(const int &n) {
        arr = new char[n];
        top = -1;
    }

    int stack_is_empty() {
        return top == -1;
    }

    void stack_push(const char &val) {
        if (top == MAXS) return;
        arr[++top] = val;
    }

    void stack_pop() {
        if (top <= -1) return;
        top--;
    }

    void stack_clear() {
        top = -1;
    }

    bool checkParen(const char &zag) {
        if (top == -1) return false;
        const int pos = zag == ']';
        for (int i = top; i >= 0; --i) {
            if (arr[i] == M[pos]) return true;
        }

        return false;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;

    char *a = new char[MAXS + 1];

    std::cin >> n;
    Stog stack(MAXS);

    for (int i = 0; i < n; ++i) {
        bool valid = true;
        std::cin >> a;

        for (int j = 0; j < (int) strlen(a); ++j) {
            // Ako je otvorena zagrada dodajemo na stack
            if (strchr(M, a[j])) {
                stack.stack_push(a[j]);
            } else {
                // Ako je zatvorena provjeravamo ako postoji ista otvorena
                if (!stack.checkParen(a[j])) {
                    valid = false;
                    break;
                }
                // Brisemo dobru otvorenu s stacka
                stack.stack_pop();
            }
        }
        // Ako je tocno mora biti i prazno jer brisemo svaki par zagrada
        if (valid && stack.stack_is_empty()) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
        stack.stack_clear();
    }

    delete[] a;

    return 0;
}