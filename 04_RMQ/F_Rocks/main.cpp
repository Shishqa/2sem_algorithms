#include <iostream>
#include <vector>
#include <algorithm>

template <class Key>
class SegmentTree {

    typedef Key key_t;

public:

    SegmentTree() = delete;

    SegmentTree(const size_t& tree_size, const key_t& infinity);

    ~SegmentTree();

    // Interface

    void add(const size_t& l_query, const size_t& r_query, const key_t& val);

    key_t get_min(const size_t& l_query, const size_t& r_query);

    key_t get_max(const size_t& l_query, const size_t& r_query);

protected:

    struct Node {

        const size_t l_idx;
        const size_t r_idx;
        const size_t m_idx;

        const key_t INF;

        key_t maximum;
        key_t minimum;
        key_t delta;

        Node* right;
        Node* left;

        Node(const Node* tree_beg, const size_t& l_idx, const size_t& r_idx,
             const key_t& infinity);

        Node(const Node& other) = delete;

        Node() = delete;

        ~Node() = default;

        void add(const size_t& l_query, const size_t& r_query, const key_t& val);

        key_t get_min(const size_t& l_query, const size_t& r_query);

        key_t get_max(const size_t& l_query, const size_t& r_query);

        void relax();

        void push();
    };

    Node* seg_tree;

    size_t size;
    const size_t capacity;
};

int main() {

    std::ios_base::sync_with_stdio(false);

    size_t stone_count = 0;
    std::cin >> stone_count;

    SegmentTree<int> balance(stone_count, 500000);

    enum {
        LEFT = 1,
        RIGHT = 2
    };

    int side = 0;
    int stone_idx = 0;
    int max_stone_idx = 0;

    int balance_max = 0;
    int balance_min = 0;

    std::vector<int> ans(stone_count, -1);

    for (size_t i = 0; i < stone_count; ++i) {

        std::cin >> stone_idx >> side;

        if (side == LEFT) {

            balance.add(0, stone_idx, 1);

        } else if (side == RIGHT) {

            balance.add(0, stone_idx, -1);

        } else {

            throw std::runtime_error("UB???");

        }

        max_stone_idx = std::max(max_stone_idx, stone_idx);

        balance_max = balance.get_max(0, max_stone_idx);
        balance_min = balance.get_min(0, max_stone_idx);

        if (balance_min <= 0 && balance_max <= 0) {
            ans[i] = 1;
        } else if (balance_min >= 0 && balance_max >= 0) {
            ans[i] = 2;
        } else {
            ans[i] = 3;
        }
    }

    for (size_t i = 0; i < stone_count; ++i) {

        switch (ans[i]) {
            case 1:
                std::cout << "<";
                break;
            case 3:
                std::cout << "?";
                break;
            case 2:
                std::cout << ">";
                break;
        }

        if (i != stone_count - 1) {
            std::cout << std::endl;
        }
    }

    return 0;
}

template <class Key>
void SegmentTree<Key>::add(const size_t& l_query, const size_t& r_query, const key_t& val) {

    seg_tree->add(l_query, r_query, val);
}

template <class Key>
Key SegmentTree<Key>::get_max(const size_t &l_query, const size_t &r_query) {

    return seg_tree->get_max(l_query, r_query);
}

template <class Key>
Key SegmentTree<Key>::get_min(const size_t &l_query, const size_t &r_query) {

    return seg_tree->get_min(l_query, r_query);
}


template <class Key>
void SegmentTree<Key>::Node::push() {

    maximum += delta;
    minimum += delta;

    left->delta  += delta;
    right->delta += delta;

    delta = 0;
}

template <class Key>
void SegmentTree<Key>::Node::relax() {

    maximum = std::max(left->maximum + left->delta, right->maximum + right->delta);
    minimum = std::min(left->minimum + left->delta, right->minimum + right->delta);
}

template <class Key>
void SegmentTree<Key>::Node::add(const size_t& l_query, const size_t& r_query, const key_t& val) {

    if (std::max(l_idx, l_query) >= std::min(r_idx, r_query)) {

        return;

    } else if (l_query <= l_idx && r_idx <= r_query) {

        delta += val;
        return;
    }

    push();

    left->add(l_query, r_query, val);
    right->add(l_query, r_query, val);

    relax();
}

template <class Key>
Key SegmentTree<Key>::Node::get_max(const size_t& l_query, const size_t& r_query) {

    if (std::max(l_idx, l_query) >= std::min(r_idx, r_query)) {

        return -INF;

    } else if (l_query <= l_idx && r_idx <= r_query) {

        return maximum + delta;
    }

    push();

    key_t left_max  = left->get_max(l_query, r_query);
    key_t right_max = right->get_max(l_query, r_query);

    return std::max(left_max, right_max);
}

template <class Key>
Key SegmentTree<Key>::Node::get_min(const size_t& l_query, const size_t& r_query) {

    if (std::max(l_idx, l_query) >= std::min(r_idx, r_query)) {

        return INF;

    } else if (l_query <= l_idx && r_idx <= r_query) {

        return minimum + delta;
    }

    push();

    key_t left_min  = left->get_min(l_query, r_query);
    key_t right_min = right->get_min(l_query, r_query);

    return std::min(left_min, right_min);
}

template <class Key>
SegmentTree<Key>::SegmentTree(const size_t& tree_size, const key_t& infinity) :
        capacity(tree_size),
        size(1) {

    // real arr size to store the tree is 2^x * 2 - 1, where x = ceil(log(n))
    while (size < capacity) {
        size <<= 1;
    }
    size = size * 2 - 1;

    seg_tree = reinterpret_cast<Node*>(::operator new(sizeof(Node[size])));
    new(seg_tree) Node(seg_tree, 0, capacity, infinity);
}


template <class Key>
SegmentTree<Key>::~SegmentTree<Key>() {

    delete[] seg_tree;
}


template <class Key>
SegmentTree<Key>::Node::Node(const Node* tree_beg, const size_t& l_idx, const size_t& r_idx,
                             const key_t& infinity) :
        INF(infinity),
        l_idx(l_idx),
        r_idx(r_idx),
        m_idx((l_idx + r_idx + 1) / 2),
        maximum(0),
        minimum(0),
        delta(0) {

    if (r_idx - l_idx == 1) {

        maximum = 0;
        minimum = 0;
        delta = 0;

        left  = nullptr;
        right = nullptr;

        return;
    }

    left = const_cast<Node*>(tree_beg + (this - tree_beg) * 2 + 1);
    new(left) Node(tree_beg, l_idx, m_idx, infinity);

    right = const_cast<Node*>(tree_beg + (this - tree_beg) * 2 + 2);
    new(right) Node(tree_beg, m_idx, r_idx, infinity);

    relax();
}