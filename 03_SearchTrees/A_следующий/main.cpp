#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>

template <typename key_t>
class Custom_BTree {
/*
 * B-tree https://en.wikipedia.org/wiki/B-tree
 */
public:

    void insert(key_t key);
    void erase(key_t key);
    bool count(key_t key);

    explicit Custom_BTree(const size_t& chunk_degree);
    Custom_BTree(const Custom_BTree<key_t>& tree);
    ~Custom_BTree();

private:

    static const size_t ROOT_INIT_SIZE = 0;

    struct Chunk {
        static const bool IS_LIST_DEFAULT = false;
        static const size_t CHUNK_DEGREE;

        bool is_list;
        std::vector<key_t> data;
        std::vector<Chunk*> child;

        void insert(key_t key);
        void erase(key_t key);
        int search(key_t key);

        std::pair<Chunk*, Chunk*> split();

        explicit Chunk(const size_t& size = ROOT_INIT_SIZE);
        Chunk(const Chunk& chunk);
        Chunk(const Chunk& chunk_1, const key_t& x_val, const Chunk& chunk_2);
        ~Chunk();
    };

    Chunk* root;

    std::pair<const Chunk*, const size_t> search(key_t key);

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

template <typename key_t>
Custom_BTree<key_t>::Custom_BTree(const size_t &chunk_degree)
    : Chunk::CHUNK_DEGREE(chunk_degree) {
    root = new Chunk();
}

template <typename key_t>
Custom_BTree<key_t>::Custom_BTree(const Custom_BTree<key_t>& tree)
    : Chunk::CHUNK_DEGREE(tree.CHUNK_DEGREE) {
    root = new Chunk(tree.root);
}

template <typename key_t>
Custom_BTree<key_t>::~Custom_BTree() {
    delete root;
}

template <typename key_t>
Custom_BTree<key_t>::Chunk::Chunk(const size_t& size)
    : is_list(IS_LIST_DEFAULT), data(std::vector<key_t>(size)),
    child(std::vector<Chunk*>(size + 1)) {}

template <typename key_t>
Custom_BTree<key_t>::Chunk::Chunk(const Custom_BTree<key_t>::Chunk& chunk)
    : is_list(chunk.is_list), data(chunk.data), child(chunk.data.size() + 1) {
    if (!is_list) {
        for (size_t i = 0; i < child.size(); ++i) {
            child[i] = new Chunk(*chunk.child[i]);
        }
    }
}

template <typename key_t>
Custom_BTree<key_t>::Chunk::Chunk(const Custom_BTree<key_t>::Chunk &chunk_1, const key_t &x_val,
                                  const Custom_BTree<key_t>::Chunk &chunk_2)
                                  : is_list(chunk_1.is_list & chunk_2.is_list) {

    // TODO: continue

    if (chunk_1.data.size() != CHUNK_DEGREE - 1)

}
