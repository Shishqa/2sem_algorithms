#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <fstream>

template<typename key_t, size_t ORDER, bool debug = false>
class Custom_BTree {
/*
 * B-tree https://en.wikipedia.org/wiki/B-tree
 */
public:

    Custom_BTree();
    Custom_BTree(const Custom_BTree<key_t, ORDER, debug> &tree);

    ~Custom_BTree();

    void insert(const key_t &key);

    key_t lower_bound(const key_t &key);

    size_t size();

    void erase(const key_t &key);

    bool count(const key_t &key);

    key_t kth_max(const int &k);

    key_t at(const int &k);

    void traverse();

private:

    struct SearchResult;

    struct Node {
        static const bool IS_LEAF_DEFAULT = true;

        bool is_leaf;
        std::vector <key_t> data;
        std::vector<Node *> child;

        int subtree_size;

        void paste(const key_t &key, const int &pos);

        void insert(const key_t &key);

        void remove(const int &pos);

        void erase(const key_t &key, bool is_root = false);

        key_t kth_max(const int &k);

        int search(const key_t &key);

        SearchResult invariant_search(const key_t &key, bool is_root = false);

        bool borrow_left(const int &idx);

        bool borrow_right(const int &idx);

        key_t get_leftmost();

        key_t get_rightmost();

        void traverse();

        void split_child(const int &idx);

        void merge_child(const int &idx);

        explicit Node(const size_t &size);

        Node(const Node &Node);

        ~Node();
    };

    struct SearchResult {
        Node *node;
        int idx;
        std::vector<Node *> track;
    };

    Node *root;
};

struct Company {

    size_t position;
    unsigned long long length;

    Company();
    Company(size_t position, unsigned long long length);

    explicit Company(const int& null_value);

    Company& operator =(const Company& c);

    friend bool operator <(const Company& a, const Company& b);
    friend bool operator >(const Company& a, const Company& b);
    friend bool operator <=(const Company& a, const Company& b);
    friend bool operator >=(const Company& a, const Company& b);
    friend bool operator ==(const Company& a, const Company& b);
    friend bool operator !=(const Company& a, const Company& b);

    friend std::ostream& operator <<(std::ostream &out, const Company& c);

};

unsigned long long squared(unsigned long long& val);

int main() {

    std::ios_base::sync_with_stdio(false);

    const size_t DEFAULT_ORDER = 35;

    std::ifstream fin("river.in");

    size_t num_of_companies = 0;
    fin >> num_of_companies;

    short garbage_subproblem = 0;
    fin >> garbage_subproblem;

    Custom_BTree<Company, DEFAULT_ORDER> river;

    Company curr_company(0,0);

    unsigned long long tax_multiplier = 0;

    for (size_t i = 0; i < num_of_companies; ++i) {

        fin >> curr_company.length;

        river.insert(curr_company);

        curr_company.position += curr_company.length;

        tax_multiplier += curr_company.length * curr_company.length;
    }

    std::ofstream fout("river.out");

    fout << tax_multiplier << std::endl;

    size_t num_of_events = 0;
    fin >> num_of_events;

    enum {

        BANKRUPTCY = 1,
        SEPARATION = 2

    };

    short event_type = 0;
    int company_idx = 0;

    for (size_t i = 0; i < num_of_events; ++i) {

        fin >> event_type >> company_idx;

        if (event_type == SEPARATION) {

            Company left_son = river.at(company_idx);

            river.erase(left_son);
            tax_multiplier -= squared(left_son.length);

            Company right_son = left_son;

            left_son.length /= 2;
            right_son.position += left_son.length;
            right_son.length -= left_son.length;

            river.insert(left_son);
            tax_multiplier += squared(left_son.length);

            river.insert(right_son);
            tax_multiplier += squared(right_son.length);

        } else {

            if (company_idx == 1) {

                Company right_successor = river.at(company_idx + 1);
                curr_company = river.at(company_idx);

                river.erase(right_successor);
                tax_multiplier -= squared(right_successor.length);

                river.erase(curr_company);
                tax_multiplier -= squared(curr_company.length);

                right_successor.length += curr_company.length;
                right_successor.position = curr_company.position;

                river.insert(right_successor);
                tax_multiplier += squared(right_successor.length);

            } else if (company_idx == river.size()) {

                Company left_successor = river.at(company_idx - 1);
                curr_company = river.at(company_idx);

                river.erase(left_successor);
                tax_multiplier -= squared(left_successor.length);

                river.erase(curr_company);
                tax_multiplier -= squared(curr_company.length);

                left_successor.length += curr_company.length;

                river.insert(left_successor);
                tax_multiplier += squared(left_successor.length);

            } else {

                Company left_successor = river.at(company_idx - 1);
                Company right_successor = river.at(company_idx + 1);
                curr_company = river.at(company_idx);

                river.erase(left_successor);
                tax_multiplier -= squared(left_successor.length);

                river.erase(curr_company);
                tax_multiplier -= squared(curr_company.length);

                river.erase(right_successor);
                tax_multiplier -= squared(right_successor.length);

                left_successor.length += curr_company.length / 2;

                right_successor.length += (curr_company.length + 1) / 2;
                right_successor.position = left_successor.position + left_successor.length;

                river.insert(left_successor);
                tax_multiplier += squared(left_successor.length);

                river.insert(right_successor);
                tax_multiplier += squared(right_successor.length);
            }
        }

        fout << tax_multiplier << std::endl;

    }

    fin.close();
    fout.close();

    return 0;
}

unsigned long long squared(unsigned long long& val) {

    return val * val;

}

Company::Company() : position(-1), length(-1) {}
Company::Company(const int& null_value) : position(-1), length(-1) {}
Company::Company(size_t position, unsigned long long length) : position(position), length(length) {}

bool operator <(const Company& a, const Company& b) {

    return a.position < b.position;

}

bool operator >(const Company& a, const Company& b) {

    return b < a;

}

bool operator >=(const Company& a, const Company& b) {

    return !(a < b);

}

bool operator <=(const Company& a, const Company& b) {

    return !(b < a);

}

bool operator ==(const Company& a, const Company& b) {

    return (a <= b) && (a >= b);

}

bool operator !=(const Company& a, const Company& b) {

    return !(a == b);

}

std::ostream& operator <<(std::ostream& out, const Company& c) {

    out << "|~[" << c.position << "]~" << c.length << "~~";

    return out;
}

Company& Company::operator =(const Company& c) {

    if (this == &c) {
        return *this;
    }

    position = c.position;
    length = c.length;

    return *this;
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
          child(std::vector<Node *>(size + 1, nullptr)), subtree_size(0) {}

template<typename key_t, size_t ORDER, bool debug>
Custom_BTree<key_t, ORDER, debug>::Node::Node(const Custom_BTree<key_t, ORDER, debug>::Node &node)
        : is_leaf(node.is_leaf), data(node.data), child(std::vector<Node *>(node.child.size(), nullptr)),
          subtree_size(node.subtree_size) {

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

    ++subtree_size;

    if (child.size() != 1 + data.size()) {

        throw std::logic_error("Node (child size) != (data size + 1) !\n");
    }
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::remove(const int &pos) {

    if (child.size() != 1 + data.size()) {

        throw std::logic_error("Node (child size) != (data size + 1) !\n");
    }

    for (int i = pos; i < data.size() - 1; ++i) {
        data[i] = data[i + 1];
    }
    for (int i = pos; i < child.size() - 1; ++i) {
        child[i] = child[i + 1];
    }

    data.pop_back();
    child.pop_back();

    --subtree_size;
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
    --child[idx]->subtree_size;

    for (size_t i = ORDER; i < 2 * ORDER - 1; ++i) {
        suffix->data[i - ORDER] = child[idx]->data[i];
        ++suffix->subtree_size;
        --child[idx]->subtree_size;
    }
    for (size_t i = ORDER; i < 2 * ORDER; ++i) {
        suffix->child[i - ORDER] = child[idx]->child[i];

        if (!suffix->is_leaf) {
            suffix->subtree_size += suffix->child[i - ORDER]->subtree_size;
            child[idx]->subtree_size -= suffix->child[i - ORDER]->subtree_size;
        }
    }

    paste(sep, idx);
    --subtree_size;

    child[idx + 1] = suffix;

    child[idx]->data.resize(ORDER - 1);
    child[idx]->child.resize(ORDER);
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::Node::merge_child(const int &idx) {

    if (child[idx]->data.size() != ORDER - 1 ||
        child[idx + 1]->data.size() != ORDER - 1) {
        throw std::logic_error("Merging nodes with more than T - 1 elements!\n");
    }

    child[idx]->data.resize(2 * ORDER - 1);
    child[idx]->child.resize(2 * ORDER);

    child[idx]->data[ORDER - 1] = data[idx];
    for (size_t i = ORDER; i < 2 * ORDER - 1; ++i) {
        child[idx]->data[i] = child[idx + 1]->data[i - ORDER];
    }
    child[idx]->subtree_size += ORDER;

    for (size_t i = ORDER; i < 2 * ORDER; ++i) {
        child[idx]->child[i] = child[idx + 1]->child[i - ORDER];
        child[idx + 1]->child[i - ORDER] = nullptr;

        if (!child[idx]->is_leaf) {
            child[idx]->subtree_size += child[idx]->child[i]->subtree_size;
        }
    }

    delete child[idx + 1];

    Node *tmp = child[idx];

    remove(idx);
    ++subtree_size;

    child[idx] = tmp;
}

template<typename key_t, size_t ORDER, bool debug>
bool Custom_BTree<key_t, ORDER, debug>::Node::borrow_left(const int &idx) {

    if (idx < 0 || idx > data.size()) {
        throw std::out_of_range("borrow_left::idx is out of range!\n");
    }

    if (idx == 0 || (idx > 0 && child[idx - 1]->data.size() == ORDER - 1)) {
        return false;
    }

    size_t brother_size = child[idx - 1]->data.size();

    child[idx]->paste(data[idx - 1], 0);
    child[idx]->child[0] = child[idx - 1]->child[brother_size];
    data[idx - 1] = child[idx - 1]->data[brother_size - 1];

    if (!child[idx]->is_leaf) {
        child[idx]->subtree_size += child[idx]->child[0]->subtree_size;
        child[idx - 1]->subtree_size -= child[idx]->child[0]->subtree_size;
    }
    --child[idx - 1]->subtree_size;

    child[idx - 1]->data.pop_back();
    child[idx - 1]->child.pop_back();

    return true;
}

template<typename key_t, size_t ORDER, bool debug>
bool Custom_BTree<key_t, ORDER, debug>::Node::borrow_right(const int &idx) {

    if (idx < 0 || idx > data.size()) {
        throw std::out_of_range("borrow_right::idx is out of range!\n");
    }

    if (idx == data.size() || (idx < data.size() && child[idx + 1]->data.size() == ORDER - 1)) {
        return false;
    }

    child[idx]->paste(data[idx], ORDER - 1);
    child[idx]->child[ORDER] = child[idx + 1]->child[0];
    data[idx] = child[idx + 1]->data[0];

    if (!child[idx]->is_leaf) {
        child[idx]->subtree_size += child[idx]->child[ORDER]->subtree_size;
        child[idx + 1]->subtree_size -= child[idx]->child[ORDER]->subtree_size;
    }

    child[idx + 1]->remove(0);

    return true;
}

template<typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::Node::get_leftmost() {

    if (is_leaf) {

        return data[0];
    }

    return child[0]->get_leftmost();
}

template<typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::Node::get_rightmost() {

    if (is_leaf) {

        return data[data.size() - 1];
    }

    return child[child.size() - 1]->get_rightmost();
}


template<typename key_t, size_t ORDER, bool debug>
typename Custom_BTree<key_t, ORDER, debug>::SearchResult
Custom_BTree<key_t, ORDER, debug>::Node::invariant_search(const key_t &key,
                                                          const bool is_root) {

    if (!is_root && data.size() == ORDER - 1) {
        throw std::logic_error("Invariant search :: invariant is broken!\n");
    }

    int search_idx = search(key);
    SearchResult result = {};

    if (search_idx < data.size() && data[search_idx] == key) {

        result = {this, search_idx};
        return result;

    } else if (is_leaf && ((search_idx < data.size() && data[search_idx] != key) || search_idx == data.size())) {

        result = {nullptr, 0};
        return result;

    }

    if (child[search_idx]->data.size() == ORDER - 1) {

        bool took_flag = borrow_left(search_idx);

        if (!took_flag) {
            took_flag = borrow_right(search_idx);
        }

        if (!took_flag) {

            if (search_idx == data.size()) {
                --search_idx;
            }

            merge_child(search_idx);
        }

    }

    result = child[search_idx]->invariant_search(key);
    result.track.push_back(this);

    return result;
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
    std::cout << "(" << subtree_size << (is_leaf ? ")] " : ")} ");
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
        ++subtree_size;
    }
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::insert(const key_t &key) {

    if (!root) {

        root = new Node(1);
        root->data[0] = key;
        ++root->subtree_size;

    } else {

        if (root->data.size() == 2 * ORDER - 1) {

            auto new_root = new Node(0);
            new_root->is_leaf = false;
            new_root->subtree_size = root->subtree_size + 1;
            new_root->child[0] = root;

            root = new_root;
            root->split_child(0);

            if (root->child[0] == root->child[1]) {
                throw std::logic_error("children are equal!\n");
            }

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
void Custom_BTree<key_t, ORDER, debug>::Node::erase(const key_t &key, const bool is_root) {

    SearchResult result = invariant_search(key, is_root);

    if (!result.node) {
        throw std::logic_error("Removing nonexistent key!\n");
    }

    for (size_t i = 0; i < result.track.size(); ++i) {
        --result.track[i]->subtree_size;
    }

    if (result.node->is_leaf) {

        result.node->remove(result.idx);

    } else {

        if (result.node->subtree_size == 0) {
            throw std::logic_error("Negative subtree size!\n");
        }

        --result.node->subtree_size;

        if (result.node->child[result.idx]->data.size() >= ORDER) {

            key_t rightmost = result.node->child[result.idx]->get_rightmost();
            result.node->data[result.idx] = rightmost;
            result.node->child[result.idx]->erase(rightmost);

        } else if (result.node->child[result.idx + 1]->data.size() >= ORDER) {

            key_t leftmost = result.node->child[result.idx + 1]->get_leftmost();
            result.node->data[result.idx] = leftmost;
            result.node->child[result.idx + 1]->erase(leftmost);

        } else {

            result.node->merge_child(result.idx);
            result.node->child[result.idx]->erase(key);

        }
    }
}

template<typename key_t, size_t ORDER, bool debug>
void Custom_BTree<key_t, ORDER, debug>::erase(const key_t &key) {

    if (!root) {
        return;
    }

    root->erase(key, true);

    if (root->data.empty()) {

        Node *tmp = root;

        if (root->is_leaf) {

            root = nullptr;

        } else {

            root = root->child[0];
            tmp->child[0] = nullptr;

        }

        delete tmp;
    }
}

template<typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::lower_bound(const key_t &key) {

    if (!root) {
        return key_t(-1);
    }

    Node *curr_node = root;

    int search_idx = curr_node->search(key);

    key_t answer = -1;

    while (!curr_node->is_leaf) {

        if (search_idx != curr_node->data.size() && curr_node->data[search_idx] >= key) {
            answer = curr_node->data[search_idx];
        }

        curr_node = curr_node->child[search_idx];
        search_idx = curr_node->search(key);
    }

    if (search_idx != curr_node->data.size()) {
        answer = curr_node->data[search_idx];
    }

    return answer;
}

template<typename key_t, size_t ORDER, bool debug>
bool Custom_BTree<key_t, ORDER, debug>::count(const key_t &key) {

    if (!root) {
        return false;
    }

    SearchResult result = root->invariant_search(key, true);

    return result.node != nullptr;
}

template<typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::Node::kth_max(const int &k) {

    if (k > subtree_size) {

        return key_t(-1);

    } else if (is_leaf) {

        return data[data.size() - k];
    }

    int tmp_k = k;

    for (int i = data.size(); i >= 0; --i) {

        if (child[i]->subtree_size >= tmp_k) {
            key_t ans = child[i]->kth_max(tmp_k);

            return ans;
        }

        tmp_k -= child[i]->subtree_size;

        if (tmp_k == 1) {
            return data[i - 1];
        }

        --tmp_k;
    }

    return key_t(-1);
}

template<typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::kth_max(const int &k) {

    if (!root) {
        return key_t(-1);
    }

    return root->kth_max(k);
}

template<typename key_t, size_t ORDER, bool debug>
key_t Custom_BTree<key_t, ORDER, debug>::at(const int &k) {

    if (!root) {
        return key_t(-1);
    }

    return root->kth_max(root->subtree_size + 1 - k);
}

template<typename key_t, size_t ORDER, bool debug>
size_t Custom_BTree<key_t, ORDER, debug>::size() {

    if (!root) {
        return 0;
    }

    return root->subtree_size;
}
