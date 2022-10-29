#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

struct Node
{
    int key;
    Node *parent;
    Node *left;
    Node *right;

    Node (int key) {
        this->key = key;
        parent = right = left = NULL;
    }
} ;

struct BST
{
    Node *root;
    BST()
    {
        root = NULL;
    }

    void add_node(int key)
    {
        Node *new_node, *trenutni, *prethodni = NULL;

        new_node = new Node(key);

        trenutni = root;
        while (trenutni != NULL)
        {
            prethodni = trenutni;
            if (new_node->key < trenutni->key)
            {
                trenutni = trenutni->left;
            }
            else
            {
                trenutni = trenutni->right;
            }
        }

        new_node->parent = prethodni;
        if (prethodni == NULL)
        {
            root = new_node;
        }
        else if (new_node->key < prethodni->key)
        {
            prethodni->left = new_node;
        }
        else
        {
            prethodni->right = new_node;
        }
    }

    int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH])
    {
        int i, left, right, width = 5;
        char b[width + 1];

        if (!tree)
            return 0;
        sprintf(b, "(%03d)", tree->key);
        left = print_tree(tree->left, 1, offset, depth + 1, s);
        right = print_tree(tree->right, 0, offset + left + width, depth + 1, s);
        for (i = 0; i < width; i++)
        {
            s[depth][offset + left + i] = b[i];
        }
        if (depth)
        {
            if (is_left)
            {
                for (i = 0; i < width + right; i++)
                {
                    s[depth - 1][offset + left + width / 2 + i] = '-';
                }
            }
            else
            {
                for (i = 0; i < left + width; i++)
                {
                    s[depth - 1][offset - width / 2 + i] = '-';
                }
            }
            s[depth - 1][offset + left + width / 2] = '.';
        }
        return left + width + right;
    }
};

Node *vrati_n_ti(Node *node, int *val) {
  if (!node) return NULL;

  Node *tmp = NULL;

  tmp = vrati_n_ti(node->left, val);

  // Tmp je uvijek NULL osim kada nađemo n-ti
  // ako ga nađemo u lijevom podstablu trebamo ga odmah
  // vratiti jer inače ćemo otići u desno podstablo
  // i vratiti NULL u jednom trenutku te ćemo "izgubiti"
  // onaj n-ti koji smo našli u lijevom podstablu
  if (tmp) return tmp;

  *val -= 1;
  if (*val == 0) return node;

  tmp = node->right ? vrati_n_ti(node->right, val) : tmp;

  return tmp;
}

int main()
{
    int i, menu_choice, val;
    char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    Node *nti = NULL;
    BST *bst = new BST();

    setbuf(stdout, NULL);
    do
    {
        scanf("%d", &menu_choice);

        switch (menu_choice)
        {
        case 1:
            cin >> val;

            nti = vrati_n_ti(bst->root, &val);

            if (nti)
                printf("%d\n", nti->key);
            else
                printf("0\n");
            break;
        case 2:
            int val;
            while (cin >> val)
            {
                if (val < 1 || val > 999)
                    continue;
                bst->add_node(val);
            }
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            cin.clear();
            break;
        case 3:
            sprintf(print_format, "%%%ds", WIDTH - 1);
            for (i = 0; i < HEIGHT; i++)
                sprintf(s[i], print_format, " ");

            bst->print_tree(bst->root, 0, 0, 0, s);

            sprintf(empty_line, print_format, " ");
            for (i = 0; i < HEIGHT; i++)
            {
                if (strcmp(s[i], empty_line))
                    cout << s[i] << "\n";
            }
            break;
        case 4:
            break;
        default:
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    } while (menu_choice != 4);

    return 0;
}