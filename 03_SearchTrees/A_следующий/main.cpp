#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>

template <typename key_t, size_t CHUNK_DEGREE, bool debug = false>
class Custom_BTree {
/*
 * B-tree https://en.wikipedia.org/wiki/B-tree
 */
public:

    void insert(const key_t& key);
    void erase(const key_t& key);
    bool count(const key_t& key);

    explicit Custom_BTree();
    Custom_BTree(const Custom_BTree<key_t, CHUNK_DEGREE, debug>& tree);
    ~Custom_BTree();

private:

    static const size_t ROOT_INIT_SIZE = 0;

    struct Chunk {
        static const bool IS_LIST_DEFAULT = false;

        bool is_list;
        std::vector<key_t> data;
        std::vector<Chunk*> child;

        void insert(const int& pos, const key_t& key);
        void erase(const int& pos);
        int search(const key_t& key);

        //std::pair<Chunk*, Chunk*> split();

        explicit Chunk(const size_t& size = ROOT_INIT_SIZE);
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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::Custom_BTree() {
    root = new Chunk();
}

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
    : is_list(IS_LIST_DEFAULT), data(std::vector<key_t>(size)),
      child(std::vector<Chunk*>(size + 1)) {}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::Chunk(const Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk& chunk)
    : is_list(chunk.is_list), data(chunk.data), child(std::vector<Chunk*>(chunk.child.size())) {

    if (!is_list)
    {
        for (size_t i = 0; i < child.size(); ++i) {
            child[i] = new Chunk(chunk.child[i]);
        }
    }
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::Chunk(const Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk &chunk_1,
                                                       const key_t &x_val, const Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk &chunk_2)
                                                       : is_list(chunk_1.is_list & chunk_2.is_list),
                                                         data(std::vector<key_t>(2 * CHUNK_DEGREE - 1)),
                                                         child(std::vector<Chunk*>(2 * CHUNK_DEGREE)) {

    if (chunk_1.data.size() != CHUNK_DEGREE - 1 ||
        chunk_2.data.size() != CHUNK_DEGREE - 1) {
        throw std::out_of_range("Trying to build chunk of chunks with wrong size!\n");
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

    int res_idx = std::lower_bound(data.begin(), data.end(), key);
    return res_idx;
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
void Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::insert(const int& pos, const key_t& key) {

    //TODO: fix if needed

    data.push_back(data[data.size() - 1]);
    for (size_t i = data.size() - 1; i > pos; ++i) {
        data[i] = data[i - 1];
    }
    data[pos] = key;
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
void Custom_BTree<key_t, CHUNK_DEGREE, debug>::Chunk::erase(const int &pos) {

    //TODO: fix if needed

    for (size_t i = pos; i < data.size() - 1; ++i) {
        data[i] = data[i + 1];
    }
    data.pop_back();
}

template <typename key_t, size_t CHUNK_DEGREE, bool debug>
void Custom_BTree<key_t, CHUNK_DEGREE, debug>::insert(const key_t& key) {

    Chunk* curr_chunk = root;
    int search_idx = 0;

    while (!curr_chunk->is_list) {
        search_idx = curr_chunk->search(key);
        curr_chunk = curr_chunk->child[search_idx];
    }

    if (curr_chunk->data.size() < 2 * Chunk::CHUNK_DEGREE - 1) {

    }

}

//template <typename key_t>
//typename Custom_BTree<key_t>::SearchResult Custom_BTree<key_t>::search(key_t key, Chunk* chunk) {
//
//    int search_idx = chunk->search(key);
//
//    if (chunk->data.size() == Chunk::CHUNK_DEGREE) {
//
//    }
//
//    if (chunk->is_list) {
//        SearchResult result = {chunk, search_idx};
//        return result;
//    }
//
//    return search(key, chunk->child[search_idx]);
//}
