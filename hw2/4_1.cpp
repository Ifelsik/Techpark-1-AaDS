#include <iostream>
#include <sstream>

#include <cassert>
#include <cstdint>

template <typename T>
struct DefaultComparator {
    int operator()(const T& l, const T& r) const {
        if (l < r) return -1;
        if (l > r) return 1;
        return 0;
    }
};

template <typename Key, typename Comparator=DefaultComparator<Key> >
class AVLTree {
    struct Node {
        Node* left;
        Node* right;

        Key key;


        size_t count;
        uint8_t height;

        explicit Node(const Key& key):
                left(nullptr), right(nullptr),
                key(key), count(1), height(1) {
        }
    };

public:
    AVLTree(Comparator comp = Comparator()) :
            root(nullptr),
            items_count(0),
            comp(comp) {
    }

    ~AVLTree() {
        del_tree(root);
    }

    size_t size() const { return items_count; }

    Node* find(const Key& key) {
        return find_aux(key, root);
    }

    size_t insert(const Key& key) {
        size_t position = 0;
        root = insert_aux(key, root, position);
        return position;
    }

    void erase(const Key& key) {
        root = erase_aux(key, root);
    }

    Node* find_position(int k_stat) {
        auto node = root;
        size_t node_right_count = count(node->right);
        while (k_stat != node_right_count) {
            if (k_stat > node_right_count) {
                node = node->left;
            } else {
                k_stat -= (node_right_count - 1); //
                node = node->right;
            }
            node_right_count = count(node->right);
        }
        return node;
    };

private:
    Node* find_aux(const Key& key, Node* node) {
        if (!node) {
            return nullptr;
        }
        int cmp_res = comp(key, node->key);
        if (cmp_res == -1) { //key < node->key
            return find_aux(key, node->left);
        } else if (cmp_res == 1) { //key > node->key
            return find_aux(key, node->right);
        }
        //key == node->key
        return node;
    }

    Node* insert_aux(const Key& key, Node* node, size_t &position) {
        if (!node) {
            items_count++;
            return new Node(key);
        }
        int cmp_res = comp(key, node->key);
        if (cmp_res == -1) { //key < node->key
            position += count(node->right) + 1;
            node->left = insert_aux(key, node->left, position);
        } else { //key >= node->key
            node->right = insert_aux(key, node->right, position);
        }
        // after insertion must balance tree
        return balance(node);
    }

    Node* erase_aux(const Key& key, Node* node) {
        if (!node) {
            return nullptr;
        }

        int cmp_res = comp(key, node->key);
        if (cmp_res == -1) { //key < node->key
            node->left = erase_aux(key, node->left);
        } else if (cmp_res == 1) { //key > node->key
            node->right = erase_aux(key, node->right);
        } else { //key == node->key
            Node* left = node->left;
            Node* right = node->right;


            if (!right) {
                return left;
            }

            // В ДЗ ДЕЛАТЬ ОДНОЙ ФУНКЦИЕЙ find_and_remove_min_node
            Node* min_node = find_and_remove_min_node(right);

            min_node->left = left;

            delete node;
            items_count--;

            fix_count_of_subtree(min_node);
            return balance(min_node);
        }
        return balance(node);
    }

    Node* find_and_remove_min_node(Node *node) {  // check bugs
        Node* min_node = node;
        Node* previous_node = nullptr;
        while (min_node->left) {
            previous_node = min_node;
            min_node = min_node->left;
        }
        if (previous_node && min_node->right) {
            previous_node->left = min_node->right;
        }
        if (min_node != node) {
            min_node->right = node;
            previous_node->left = nullptr;
        }
        return min_node;
    }

    uint8_t height(Node* node) {
        if (!node) {
            return 0;
        }
        return node->height;
    }

    size_t count(Node* node) {
        if (!node) {
            return 0;
        }
        return node->count;
    }

    void fix_count_of_subtree(Node* node) {
        if (!node) {
            return;
        }
        fix_count_of_subtree(node->left);
        fix_count_of_subtree(node->right);
        node->count = count(node->left) + count(node->right) + 1;
    }

    void fix_height_and_count(Node* node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
        node->count = count(node->left) + count(node->right) + 1;
    }

    int balance_factor(Node* node) {
        return height(node->right) - height(node->left);
    }

    Node* balance(Node* node) {
        fix_height_and_count(node);

        int bf = balance_factor(node);
        if (bf == 2) {
            if (balance_factor(node->right) < 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }

        if (bf == -2) {
            if (balance_factor(node->left) > 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }

        return node;
    }

    Node* rotate_left(Node* node) {
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        fix_height_and_count(node);
        fix_height_and_count(temp);
        return temp;
    }

    Node* rotate_right(Node* node) {
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        fix_height_and_count(node);
        fix_height_and_count(temp);
        return temp;
    }

    void del_tree(Node* node) {
        if (!node) {
            return;
        }
        del_tree(node->left);
        del_tree(node->right);
        delete node;
    }

    Node* root;
    size_t items_count;
    Comparator comp;
};


void run(std::istream &in, std::ostream &out) {
    int n = 0, key = 0, pos = 0;
    in >> n;
    AVLTree<int> avl_tree;
    int op;
    while (n-- > 0) {
        in >> op;
        if (op == 1) {
            in >> key;
            int position = avl_tree.insert(key);
            out << position << '\n';
        } else if (op == 2) {
            in >> pos;
            auto node_to_delete = avl_tree.find_position(pos);
            avl_tree.erase(node_to_delete->key);
        }
    }
}

void test() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "5\n";
        in << "1 100\n";
        in << "1 200\n";
        in << "1 50\n";
        in << "2 1\n";
        in << "1 150\n";

        run(in, out);

        assert(out.str() == "0\n0\n2\n1\n");
    }
    {
        {
            std::stringstream in;
            std::stringstream out;

            in << "15\n";
            in << "1 41\n";
            in << "1 18467\n";
            in << "2 0\n";
            in << "1 26500\n";
            in << "1 19169\n";
            in << "2 1\n";
            in << "1 11478\n";
            in << "1 29358\n";
            in << "2 2\n";
            in << "1 24464\n";
            in << "1 5705\n";
            in << "2 0\n";
            in << "1 23281\n";
            in << "1 16827\n";
            in << "2 1\n";

            run(in, out);

            assert(out.str() == "0\n0\n0\n1\n1\n0\n2\n3\n2\n3\n");
        }
    }
    std::cout << "OK!" << std::endl;
}

int main() {
    test();
    run(std::cin, std::cout);
    return 0;
}
