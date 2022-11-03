#include <iostream>

#define SIZE 10

template <typename T> struct Stog {
    T *array;
    int tops[2];

    int *getStog() {
        return array;
    }

    Stog() {
        array = new T[SIZE];
        tops[0] = -1;
        tops[1] = SIZE;
    }

    int push(const int &stack_nr, const T &val) {
        if (stack_nr != 1 && stack_nr != 2) return -2;
        // Ako su jedan do drugoga
        if (tops[0] + 1 == tops[1]) return -1;

        // Ako je prvi stog povećavamo tops, ako je drugi smanjujemo
        tops[stack_nr - 1] += stack_nr == 1 ? 1 : -1;
        array[tops[stack_nr - 1]] = val;

        return 0;
    }

    int pop(const int &stack_nr) {
        // Ako nije jedan od 2 dostupna stoga vrati se
        if (stack_nr != 1 && stack_nr != 2) return -2;

        // Ako je stog u koji dodajemo prazan vrati se
        if ((stack_nr == 1 && tops[0] <= - 1) || (stack_nr == 2 && tops[1] >= SIZE)) {
            return -1;
        }
        // Ako je 1. stog idemo u lijevo (-1) ako je 2. idemo u desno (+1)
        tops[stack_nr - 1] += stack_nr == 1 ? -1 : 1;

        return 0;
    }

    int print(const int &stack_nr) {
        if ((stack_nr == 1 && tops[0] <= - 1) || (stack_nr == 2 && tops[1] >= SIZE)) {
            return -1;
        }
        const int start = stack_nr == 1 ? 0 : SIZE - 1;
        const int end = tops[stack_nr - 1];

        std::cout << "Stog: ";
        // Dok start ne postane end, ne ukljucuje end
        // Ako je 1. stog idemo s lijeva u desno (+1), ako je
        // 2. stog idemo s lijeva u desno (-1)
        for (int i = start; i != end; i += stack_nr == 1 ? 1 : -1) {
            std::cout << array[i] << " ";
        }

        std::cout << array[end] << std::endl;
        return 0;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    char menu_choice = 0;
    Stog<int> stack;
    int val, retval, stack_nr;

    //DEBUG("\n(d) dodaj - push\n(b) brisi - pop\n(i) ispis - print\n(e) Exit\n");
    do {
        std::cin >> menu_choice;
        switch (menu_choice) {
        case 'd':
            std::cin >> stack_nr;
            std::cin >> val;
            retval = stack.push(stack_nr, val);
            if (retval == -1) {
                std::cout << "Stog je " << stack_nr << " pun. Ne mogu dodati element.\n";
            } else if (retval == -2) {
                std::cout << "Stog je " << stack_nr << " ne postoji.\n" ;
            }
            break;
        case 'b':
            std::cin >> stack_nr;
            retval = stack.pop(stack_nr);
            if (retval == -1) {
                std::cout << "Stog je " << stack_nr << " prazan. Ne mogu obrisati element.\n";
            } else if (retval == -2) {
                std::cout << "Stog je " << stack_nr << " ne postoji.\n";
            }
            break;
        case 'i':
            std::cin >> stack_nr;
            stack.print(stack_nr);
            break;
        }
    } while (menu_choice != 'e');
    return 0;
}