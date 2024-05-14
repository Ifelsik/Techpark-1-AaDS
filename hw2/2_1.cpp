#include <iostream>
#include <sstream>
#include <cassert>

#include <stack>

struct DefaultComparator {
    bool operator() (const int &key1, const int &key2) {
        return key1 > key2;
    }
};

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

template <typename Comparator = DefaultComparator>
class BinTree {
public:
    BinTree(Comparator comp = Comparator()) : root(nullptr), comp(comp) {}

    ~BinTree() {
        std::stack<Node*> nodeStack;
        if (root == nullptr) {
            return;
        }
        nodeStack.push(root);
        while (!nodeStack.empty()) {
            Node* current = nodeStack.top();
            nodeStack.pop();
            if (current->right != nullptr) {
                nodeStack.push(current->right);
            }
            if (current->left != nullptr) {
                nodeStack.push(current->left);
            }
            delete current;
        }
    }

    void add(int key) {
        if (root == nullptr) {
            root = new Node(key);
            return;
        }
        Node* current = root;
        while (current != nullptr) {
            if (comp(current->key, key)) {
                if (current->left == nullptr) {
                    current->left = new Node(key);
                    return;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = new Node(key);
                    return;
                }
                current = current->right;
            }
        }
    }

    std::string in_order() {
        std::stack<Node*> nodeStack;
        if (root != nullptr) {
            nodeStack.push(root);
        }
        std::string visit;
        while (!nodeStack.empty()) {
            while (nodeStack.top()->left != nullptr) {
                nodeStack.push(nodeStack.top()->left);
            }
            visit += (std::to_string(nodeStack.top()->key) + ' ');
            while (!nodeStack.empty() && nodeStack.top()->right == nullptr) {
                nodeStack.pop();
                if (!nodeStack.empty()) {
                    visit += (std::to_string(nodeStack.top()->key) + ' ');
                }
            }
            if (!nodeStack.empty() && nodeStack.top()->right != nullptr) {
                Node* right_node = nodeStack.top()->right;
                nodeStack.pop();
                nodeStack.push(right_node);
            }
        }
        return visit;
    }
private:
    Node* root;
    Comparator comp;
};

void run(std::istream &in, std::ostream &out) {
    BinTree tree;
    int n = 0;
    in >> n;
    int key = 0;
    for (int i = 0; i < n; i++) {
        in >> key;
        tree.add(key);
    }
    out << tree.in_order();
}

void test() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "10 9 10 4 3 2 7 8 5 1 6\n";

        run(in, out);

        assert(out.str() == "1 2 3 4 5 6 7 8 9 10 ");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "1 -5\n";

        run(in, out);

        assert(out.str() == "-5 ");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "5 10 5 -2 17 23\n";

        run(in, out);

        assert(out.str() == "-2 5 10 17 23 ");
    }
    std::cout << "OK!" << std::endl;
}

int main() {
//    test();
    run(std::cin, std::cout);
    return 0;
}
