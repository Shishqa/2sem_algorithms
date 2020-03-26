#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <cstdio>
#include <ctime>

template<typename key_t, size_t ORDER, bool debug = false>
class Custom_BTree {
/*
 * B-tree https://en.wikipedia.org/wiki/B-tree
 */
public:

    void insert(const key_t &key);

    key_t sum(const key_t &l_bound, const key_t &r_bound);

    void traverse();

    explicit Custom_BTree();

    Custom_BTree(const Custom_BTree<key_t, ORDER, debug> &tree);

    ~Custom_BTree();

private:

    struct Node {
        static const bool IS_LEAF_DEFAULT = true;

        bool is_leaf;
        std::vector<key_t> data;
        std::vector<Node *> child;

        key_t subtree_sum;

        key_t sum(const key_t &l_bound, const key_t &r_bound);

        void paste(const key_t &key, const int &pos);

        void insert(const key_t &key);

        int search(const key_t &key);

        void traverse();

        void split_child(const int &idx);

        explicit Node(const size_t &size);

        Node(const Node &Node);

        ~Node();
    };

    Node *root;
};

int main() {

    std::ios_base::sync_with_stdio(false);

    const size_t DEFAULT_ORDER = 500;

    const char OP_ADD = '+';
    const char OP_SUM = '?';

    const unsigned long long MOD = 1000000000;

    size_t num_requests = 0;
    std::cin >> num_requests;

    Custom_BTree<unsigned long long, DEFAULT_ORDER> set;

    char op_type = 0;

    bool after_ans = false;
    unsigned long long prev_ans = 0;

    for (size_t i = 0; i < num_requests; ++i) {

        std::cin >> op_type;

        if (op_type == OP_ADD) {

            unsigned long long element = 0;
            std::cin >> element;

            if (after_ans) {

                element = (prev_ans + element) % MOD;
                after_ans = false;

            }

            set.insert(element);

        } else {

            unsigned long long l_bound = 0;
            std::cin >> l_bound;

            unsigned long long r_bound = 0;
            std::cin >> r_bound;

            prev_ans = set.sum(l_bound, r_bound);

            std::cout << prev_ans << std::endl;

            prev_ans %= MOD;
            after_ans = true;
        }

    }

    return 0;
}

template<typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Custom_BTree()
        : root(nullptr) {}

template<typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Custom_BTree(const Custom_BTree<key_t, ORDER, debug> &tree) {
    root = new Node(tree.root);
}

template<typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::~Custom_BTree() {
    delete root;
}

template<typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Node::Node(const size_t &size)
        : is_leaf(IS_LEAF_DEFAULT), data(std::vector<key_t>(size)),
          child(std::vector<Node *>(size + 1, nullptr)), subtree_sum(0) {}

template<typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Node::Node(const Custom_BTree<key_t, ORDER, debug>::Node &node)
        : is_leaf(node.is_leaf), data(node.data), child(std::vector<Node *>(node.child.size(), nullptr)),
          subtree_sum(0) {

    if (!is_leaf) {
        for (size_t i = 0; i < child.size(); ++i) {
            child[i] = new Node(node.child[i]);
        }
    }
}

template<typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Node::~Node() {
    for (size_t i = 0; i < child.size(); ++i) {
        delete child[i];
    }
}

template<typename key_t, size_t ORDER, bool debug>
int Custom_BTree<key_t, ORDER, debug>::Node::search(const key_t &key) {

    int l_idx = 0;
    int r_idx = data.size();
    int m_idx = 0;

    while (l_idx < r_idx) {

        m_idx = (l_idx + r_idx) / 2;

        if (data[m_idx] < key) {
            l_idx = m_idx + 1;
        } else {
            r_idx = m_idx;
        }
    }

    return l_idx;
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::paste(const key_t &key, const int &pos) {

    if (data.size() == 2 * ORDER - 1) {
        throw std::logic_error("Pasting to the full Node!\n");
    }

    child.push_back(child[child.size() - 1]);

    if (!data.empty()) {
        data.push_back(data[data.size() - 1]);
    } else {
        data.resize(1);
    }

    for (int i = data.size() - 2; i > pos; --i) {
        data[i] = data[i - 1];
    }
    for (int i = child.size() - 2; i > pos; --i) {
        child[i] = child[i - 1];
    }
    data[pos] = key;
    subtree_sum += key;

    if (child.size() != 1 + data.size()) {

        throw std::logic_error("Node (child size) != (data size + 1) !\n");
    }
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::split_child(const int &idx) {

    if (child[idx]->data.size() != 2 * ORDER - 1) {
        throw std::logic_error("Splitting non-full child!\n");
    } else if (data.size() == 2 * ORDER - 1) {
        throw std::logic_error("Splitting child of full node!\n");
    }

    auto suffix = new Node(ORDER - 1);

    suffix->is_leaf = child[idx]->is_leaf;

    key_t sep = child[idx]->data[ORDER - 1];
    child[idx]->subtree_sum -= sep;

    for (size_t i = ORDER; i < 2 * ORDER - 1; ++i) {
        suffix->data[i - ORDER] = child[idx]->data[i];

        suffix->subtree_sum     += suffix->data[i - ORDER];
        child[idx]->subtree_sum -= suffix->data[i - ORDER];
    }

    for (size_t i = ORDER; i < 2 * ORDER; ++i) {
        suffix->child[i - ORDER] = child[idx]->child[i];

        if (!suffix->is_leaf) {
            suffix->subtree_sum     += suffix->child[i - ORDER]->subtree_sum;
            child[idx]->subtree_sum -= suffix->child[i - ORDER]->subtree_sum;
        }
    }

    paste(sep, idx);
    subtree_sum -= sep;

    child[idx + 1] = suffix;

    child[idx]->data.resize(ORDER - 1);
    child[idx]->child.resize(ORDER);
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::traverse() {

    std::cout << (is_leaf ? "[ " : "{ ");
    for (size_t i = 0; i < data.size(); ++i) {
        if (!is_leaf) {
            child[i]->traverse();
        }
        std::cout << data[i] << " ";
    }

    if (!is_leaf) {
        child[data.size()]->traverse();
    }
    std::cout << "(sum = " << subtree_sum << ")";
    std::cout << (is_leaf ? "] " : "} ");
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::traverse() {

    if (!root) {
        std::cout << "Tree is empty\n";
        return;
    }

    root->traverse();

    std::cout << std::endl;
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::insert(const key_t &key) {

    if (data.size() == 2 * ORDER - 1) {
        throw std::logic_error("Inserting to the full node!\n");
    }

    int search_idx = search(key);

    if (search_idx < data.size() && data[search_idx] == key) {
        return;
    }

    if (is_leaf) {

        paste(key, search_idx);

    } else {

        if (child[search_idx]->data.size() == 2 * ORDER - 1) {

            split_child(search_idx);

            if (key > data[search_idx]) {
                ++search_idx;
            }
        }

        child[search_idx]->insert(key);

        subtree_sum += key;
    }
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::insert(const key_t &key) {

    if (!root) {

        root = new Node(1);
        root->data[0] = key;

        root->subtree_sum += key;

    } else {

        if (root->data.size() == 2 * ORDER - 1) {

            auto new_root = new Node(0);
            new_root->is_leaf = false;

            new_root->subtree_sum = root->subtree_sum + key;

            new_root->child[0] = root;

            root = new_root;
            root->split_child(0);

            if (key < root->data[0]) {
                root->child[0]->insert(key);
            } else {
                root->child[1]->insert(key);
            }

        } else {

            root->insert(key);

        }
    }
}

template<typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::sum(const key_t &l_bound, const key_t &r_bound) {

    if (!root || l_bound > r_bound) {
        return 0;
    }

    return root->sum(l_bound, r_bound);
}

template<typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::Node::sum(const key_t &l_bound, const key_t &r_bound) {

    key_t sum = 0;

    int l_idx = search(l_bound);

    if (l_idx == data.size()) {

        if (is_leaf) {
            return 0;
        } else {
            return child[l_idx]->sum(l_bound, r_bound);
        }

    }

    int r_idx = search(r_bound);

    if (l_idx < r_idx) {

        sum += data[l_idx];

        if (data[l_idx] != l_bound && !is_leaf) {

            sum += child[l_idx]->sum(l_bound, r_bound);

        }

        for (int i = l_idx + 1; i < r_idx; ++i) {

            if (!is_leaf) {
                sum += child[i]->subtree_sum;
            }

            sum += data[i];

        }

        if (r_idx < data.size() && data[r_idx] == r_bound) {

            sum += data[r_idx];

            if (!is_leaf) {
                sum += child[r_idx]->subtree_sum;
            }

        } else if (!is_leaf) {

            sum += child[r_idx]->sum(l_bound, r_bound);

        }

    } else {

        if (data[l_idx] <= r_bound) {

            sum += data[l_idx];

        }

        if (data[l_idx] > l_bound && !is_leaf) {

            sum += child[l_idx]->sum(l_bound, r_bound);

        }

    }

    return sum;
}




