#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <cstdio>


template <typename key_t, size_t CHUNK_DEGREE, bool debug = false>
class Custom_BTree {
/*
 * B-tree https://en.wikipedia.org/wiki/B-tree
 */
public:

    void insert(const key_t& key);
    key_t lower_bound(const key_t& key);
    void erase(const key_t& key);
    bool count(const key_t& key);

    void traverse();

    explicit Custom_BTree();
    Custom_BTree(const Custom_BTree<key_t, CHUNK_DEGREE, debug>& tree);
    ~Custom_BTree();

private:

    struct Chunk {
        static const bool IS_LEAF_DEFAULT = true;

        bool is_leaf;
        std::vector<key_t> data;
        std::vector<Chunk*> child;

        void paste(const key_t& key, const int& pos);
        void insert(const key_t& key);
        void erase(const int& pos);
        int search(const key_t& key);

        void traverse();

        void split_child(const int& idx);

        //std::pair<Chunk*, Chunk*> split();

        explicit Chunk(const size_t& size);
        Chunk(const Chunk& chunk);
        Chunk(const Chunk& chunk_1, const key_t& x_val, const Chunk& chunk_2);
        ~Chunk();
    };

    struct SearchResult {
        Chunk* chunk;
        int idx;
    };

    Chunk* root;

    SearchResult search(key_t key, Chunk* chunk);

};

int main() {

    /*
     * raw solution
     */

    const int MOD = static_cast<int>(1e9);

    size_t num_requests = 0;
    char operation = 0;
    int request = 0;

    bool after_next = false;
    int last_answer = 0;

    Custom_BTree<int, 100> set;

    std::cin >> num_requests;

    for (size_t i = 0; i < num_requests; ++i) {

        std::cin >> operation >> request;

        if (operation == '+') {

            if (after_next) {
                set.insert((request + last_answer) % MOD);
            } else {
                set.insert(request);
            }

            after_next = false;
        } else {

            last_answer = set.lower_bound(request);

            printf("%d\n", last_answer);

            after_next = true;
        }

    }

    return 0;
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::Custom_BTree()
    : root(nullptr) {}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::Custom_BTree(const Custom_BTree<key_t, CHUNK_DEGREE, debug>& tree) {
    root = new Chunk(tree.root);
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::~Custom_BTree() {
    delete root;
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::Chunk(const size_t& size)
    : is_leaf(IS_LEAF_DEFAULT), data(std::vector<key_t>(size)),
      child(std::vector<Chunk*>(size + 1)) {}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::Chunk(const Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk& chunk)
    : is_leaf(chunk.is_leaf), data(chunk.data), child(std::vector<Chunk*>(chunk.child.size())) {

    if (!is_leaf) {
        for (size_t i = 0; i < child.size(); ++i) {
            child[i] = new Chunk(chunk.child[i]);
        }
    }
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::Chunk(const Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk &chunk_1,
                                                       const key_t &x_val, const Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk &chunk_2)
                                                       : is_leaf(chunk_1.is_leaf & chunk_2.is_leaf),
                                                         data(std::vector<key_t>(2 * CHUNK_DEGREE - 1)),
                                                         child(std::vector<Chunk*>(2 * CHUNK_DEGREE)) {

    if (chunk_1.data.size() != CHUNK_DEGREE - 1 ||
        chunk_2.data.size() != CHUNK_DEGREE - 1) {
        throw std::out_of_range("Trying to build chunk of chunks with incorrect size! (not 2t - 1)\n");
    }

    for (size_t i = 0; i < CHUNK_DEGREE - 1; ++i) {
        data[i] = chunk_1.data[i];
        child[i] = chunk_1.child[i];
    }

    child[CHUNK_DEGREE - 1] = chunk_1.child[CHUNK_DEGREE - 1];
    data[CHUNK_DEGREE - 1] = x_val;
    child[CHUNK_DEGREE] = chunk_2.child[0];

    for (size_t i = CHUNK_DEGREE; i < 2 * CHUNK_DEGREE - 1; ++i) {
        data[i] = chunk_2.data[i - CHUNK_DEGREE];
        child[i + 1] = chunk_2.child[i + 1 - CHUNK_DEGREE];
    }
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::~Chunk() {
    for (size_t i = 0; i < child.size(); ++i) {
        delete child[i];
    }
}


template <typename key_t, size_t CHUNK_DEGREE, bool debug>
int Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::search(const key_t& key) {

    //TODO: fix if needed

    //printf("Search for %d\n", key);

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

    //printf("found\n");

    return l_idx;
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
void Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::paste(const key_t& key, const int& pos) {

    if (data.size() == 2 * CHUNK_DEGREE - 1) {
        throw std::logic_error("Pasting to the full chunk!\n");
    }

    //printf("pasting %d to the pos %d\n", key, pos);

    //printf("data size = %d\nchild size = %d\n", data.size(), child.size());

    child.push_back(child[child.size() - 1]);

    if (data.size() == 0) {
        data.push_back(key);
        //printf("pasted %d\n", key);
        return;
    }

    data.push_back(data[data.size() - 1]);

    for (size_t i = data.size() - 1; i > pos; --i) {
        data[i] = data[i - 1];
        child[i + 1] = child[i];
    }
    data[pos] = key;

    //printf("pasted %d\n", key);
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
bool Custom_BTree<key_t, CHUNK_DEGREE, debug>::count(const key_t& key) {

    Chunk* curr_chunk = root;

    int search_idx = curr_chunk->search(key);

    while (!curr_chunk->is_leaf) {

        if (search_idx != curr_chunk->data.size() && curr_chunk->data[search_idx] == key) {
            return true;
        }

        curr_chunk = curr_chunk->child[search_idx];
        search_idx = curr_chunk->search(key);
    }

    return search_idx != curr_chunk->data.size() && curr_chunk->data[search_idx] == key;

}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
key_t Custom_BTree<key_t, CHUNK_DEGREE, debug>::lower_bound(const key_t& key) {

    Chunk* curr_chunk = root;

    int search_idx = curr_chunk->search(key);

    key_t answer = -1;

    while (!curr_chunk->is_leaf) {

        if (search_idx != curr_chunk->data.size() && curr_chunk->data[search_idx] >= key) {
            answer = curr_chunk->data[search_idx];
        }

        curr_chunk = curr_chunk->child[search_idx];
        search_idx = curr_chunk->search(key);
    }

    if (search_idx != curr_chunk->data.size()) {
        answer = curr_chunk->data[search_idx];
    }

    return answer;
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
void Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::insert(const key_t& key) {

    //TODO: fix if needed

    if (data.size() == 2 * CHUNK_DEGREE - 1) {
        throw std::logic_error("Inserting to the full node!\n");
    }

    int search_idx = search(key);

    if (is_leaf) {

        paste(key, search_idx);

    } else {

        if (child[search_idx]->data.size() == 2 * CHUNK_DEGREE - 1) {

            split_child(search_idx);
            if(key > data[search_idx]) {
                ++search_idx;
            }
        }

        child[search_idx]->insert(key);

    }
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
void Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::split_child(const int& idx) {

    if (child[idx]->data.size() != 2 * CHUNK_DEGREE - 1) {
        throw std::logic_error("Splitting non-full child!\n");
    } else if (data.size() == 2 * CHUNK_DEGREE - 1) {
        throw std::logic_error("Splitting child of full node!\n");
    }

    //printf("Splitting child %d\n", idx);

    Chunk* suffix = new Chunk(CHUNK_DEGREE - 1);

    suffix->is_leaf = child[idx]->is_leaf;

    key_t sep = child[idx]->data[CHUNK_DEGREE - 1];

    for (size_t i = CHUNK_DEGREE; i < 2 * CHUNK_DEGREE - 1; ++i) {
        suffix->data[i - CHUNK_DEGREE]  = child[idx]->data[i];
        suffix->child[i - CHUNK_DEGREE] = child[idx]->child[i];
    }
    suffix->child[CHUNK_DEGREE - 1] = child[idx]->child[2 * CHUNK_DEGREE - 1];

    paste(sep, idx);

    child[idx + 1] = suffix;

    child[idx]->data.resize(CHUNK_DEGREE - 1);
    child[idx]->child.resize(CHUNK_DEGREE);
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
void Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::traverse() {

    printf("{");
    for (size_t i = 0; i < data.size(); ++i) {
        if (!is_leaf) {
            child[i]->traverse();
        }
        printf("%d ", data[i]);
    }

    if (!is_leaf) {
        child[data.size()]->traverse();
    }
    printf("}");
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
void Custom_BTree<key_t, CHUNK_DEGREE, debug>::traverse() {

    root->traverse();
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
void Custom_BTree<key_t, CHUNK_DEGREE, debug>::insert(const key_t& key) {

    //printf("INSERTING %d\n", key);

    if (!root) {

        //printf("init root!\n");
        root = new Chunk(0);
        root->data.push_back(key);

    } else {

        if (root->data.size() == 2 * CHUNK_DEGREE - 1) {

            //printf("full root!\n");

            Chunk* new_root = new Chunk(0);
            new_root->is_leaf = false;

            new_root->child[0] = root;
            new_root->split_child(0);

            if (key < new_root->data[0]) {
                new_root->child[0]->insert(key);
            } else {
                new_root->child[1]->insert(key);
            }

            root = new_root;
        } else {
            //printf("non-full root!\n");

            root->insert(key);
        }

    }

}
