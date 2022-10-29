#include <iostream>
#include <string.h>

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

    Node(int key) {
        this->key = key;
        parent = left = right = NULL;
    }
};

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

void rekombiniraj(Node *node) {
    if (!node) return;

    Node *tmp = node->left;
    node->left = node->right;
    node->right = tmp;

    rekombiniraj(node->left);
    rekombiniraj(node->right);

}

int main()
{
    int i, menu_choice;
    char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    BST *bst = new BST();

    setbuf(stdout, NULL);
    do
    {
        DEBUG("\n1.Rekombiniraj (rekombiniraj)");
        DEBUG("\n2.Unos vrijednost(i) kljuceva (1-999)\n3.Ispis\n4.Izlaz\n");
        cin >> menu_choice;

        switch (menu_choice)
        {
        case 1:
            rekombiniraj(bst->root);
            break;
        case 2:
            DEBUG("\nUnos zakljucite bilo kojim nebrojcanim znakom: ");
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