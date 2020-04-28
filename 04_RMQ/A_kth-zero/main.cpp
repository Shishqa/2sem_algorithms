#include <iostream>
#include <vector>

template <class Key>
class SegmentTree {

    typedef Key key_t;

public:

    SegmentTree() = delete;

    explicit SegmentTree(const std::vector<key_t>& init);

    ~SegmentTree();

    // Interface

    void update(const size_t& pos, const key_t& val);

    int kth_zero_idx(const size_t& l_idx, const size_t& r_idx, const size_t& k);

protected:

    struct Node {

        const size_t l_idx;
        const size_t r_idx;
        const size_t m_idx;

        size_t key_stat;
        int key_idx;

        Node* right;
        Node* left;

        Node* root;

        Node(const Node* tree_beg, const size_t& l_idx, const size_t& r_idx, const std::vector<key_t>& init);

        Node(const Node& other) = delete;

        Node() = delete;

        ~Node() = default;

        void update(const size_t& pos, const key_t& new_key);

        std::pair<size_t, int> kth_zero_idx(const size_t& l_query, const size_t& r_query, const size_t& k);

        void get_key_stat(const key_t& key);

        void relax();
    };

    Node* seg_tree;

    size_t size;
    const size_t capacity;
};

int main() {

    std::ios_base::sync_with_stdio(false);

    size_t data_size = 0;
    std::cin >> data_size;

    std::vector<int> input_data(data_size);

    for (auto& gap : input_data) {
        std::cin >> gap;
    }

    SegmentTree<int> container(input_data);

    size_t request_count = 0;
    std::cin >> request_count;

    char op_code = 0;
    size_t l_query = 0;
    size_t r_query = 0;
    size_t k = 0;
    int val = 0;

    for (size_t i = 0; i < request_count; ++i) {

        std::cin >> op_code;

        if (op_code == 'u') {
            std::cin >> l_query >> val;
            container.update(l_query, val);
        } else {
            std::cin >> l_query >> r_query >> k;
            std::cout << container.kth_zero_idx(l_query, r_query, k) << " ";
        }
    }

    return 0;
}

template <class Key>
void SegmentTree<Key>::update(const size_t& pos, const key_t& val) {

    seg_tree->update(pos - 1, val);
}

template <class Key>
int SegmentTree<Key>::kth_zero_idx(const size_t& l_idx, const size_t& r_idx, const size_t& k) {

    std::pair<size_t, int> res = seg_tree->kth_zero_idx(l_idx - 1, r_idx, k);

    return res.second + (res.second == -1 ? 0 : 1);  // idx or -1
}

template <class Key>
void SegmentTree<Key>::Node::relax() {

    key_stat = left->key_stat + right->key_stat;
    key_idx = std::max(left->key_idx, right->key_idx);
}

template <class Key>
void SegmentTree<Key>::Node::get_key_stat(const key_t &key) {

    if (r_idx - l_idx != 1) {
        throw std::runtime_error("Writing key stat to segment!\n");
    }

    if (key == 0) {
        key_stat = 1;
        key_idx  = l_idx;
    } else {
        key_stat = 0;
        key_idx  = -1;
    }
}

template <class Key>
void SegmentTree<Key>::Node::update(const size_t& pos, const key_t& new_key) {

    if (r_idx - l_idx == 1) {
        get_key_stat(new_key);
        return;
    }

    if (pos < m_idx) {
        left->update(pos, new_key);
    } else {
        right->update(pos, new_key);
    }

    relax();
}


template <class Key>
std::pair<size_t, int> SegmentTree<Key>::Node::kth_zero_idx(const size_t &l_query, const size_t &r_query, const size_t &k) {

    if (std::max(l_idx, l_query) >= std::min(r_idx, r_query)) {

        return {0, -1};             // NEUTRAL

    } else if (l_query <= l_idx && r_idx <= r_query && k >= key_stat) {

        if (k == key_stat) {
            return {key_stat, key_idx};   // this node has k zeros, so it can return idx of k-th zero
        } else {
            return {key_stat, -1};     // this node has less than k zeros
        }

    } else {

        std::pair<size_t, int> left_stat = left->kth_zero_idx(l_query, r_query, k);

        if (left_stat.first == k) {
            return left_stat;
        }

        std::pair<size_t, int> right_stat = right->kth_zero_idx(l_query, r_query, k - left_stat.first);

        right_stat.first += left_stat.first;
        return right_stat;
    }
}

template <class Key>
SegmentTree<Key>::SegmentTree(const std::vector<key_t>& init) :
        capacity(init.size()),
        size(1) {

    // real arr size to store the tree is 2^x * 2 - 1, where x = ceil(log(n))
    while (size < capacity) {
        size <<= 1;
    }
    size = size * 2 - 1;

    seg_tree = reinterpret_cast<Node*>(::operator new(sizeof(Node[size])));
    new(seg_tree) Node(seg_tree, 0, capacity, init);
}


template <class Key>
SegmentTree<Key>::~SegmentTree<Key>() {

    delete [] seg_tree;
}


template <class Key>
SegmentTree<Key>::Node::Node(const Node* tree_beg, const size_t& l_idx, const size_t& r_idx,
                             const std::vector<key_t>& init) :
        l_idx(l_idx),
        r_idx(r_idx),
        m_idx((l_idx + r_idx + 1) / 2) {

    if (r_idx - l_idx == 1) {
        get_key_stat(init[l_idx]);
        left = nullptr;
        right = nullptr;
        return;
    }

    left = const_cast<Node*>(tree_beg + (this - tree_beg) * 2 + 1);
    new(left) Node(tree_beg, l_idx, m_idx, init);

    right = const_cast<Node*>(tree_beg + (this - tree_beg) * 2 + 2);
    new(right) Node(tree_beg, m_idx, r_idx, init);

    relax();
}