#include <cstdio>
#include <vector>

template <class Key>
class SparseTable {

    typedef Key key_t;

public:

    key_t get_max(const size_t& l_idx, const size_t& r_idx);

    explicit SparseTable(const std::vector<key_t>& init_data);

    SparseTable() = delete;

    SparseTable(const SparseTable& other) = delete;

    ~SparseTable();

private:

    void fill_table(const std::vector<key_t>& init_data);

    key_t** table;

    const size_t size;

    size_t height;
    size_t* log2;
    size_t* pow2;
};

struct Key {

    size_t idx;
    unsigned int value;

    Key() = default;

    Key(const Key& other) = default;

    ~Key() = default;
};

bool operator<(const Key& key1, const Key& key2);

int main() {

    FILE* in_fd = fopen("index-max.in", "r");

    size_t data_size = 0;
    fscanf(in_fd, "%lu", &data_size);

    std::vector<Key> input_data(data_size);

    for (size_t i = 1; i <= data_size; ++i) {
        fscanf(in_fd, "%u", &input_data[i - 1].value);
        input_data[i - 1].idx = i;
    }

    SparseTable<Key> rmq_container(input_data);

    size_t request_count = 0;
    fscanf(in_fd, "%lu", &request_count);

    size_t l_idx = 0;
    size_t r_idx = 0;

    FILE* out_fd = fopen("index-max.out", "w");

    Key res = {};

    for (size_t i = 0; i < request_count; ++i) {

        fscanf(in_fd, "%lu %lu", &l_idx, &r_idx);

        res = rmq_container.get_max(l_idx - 1, r_idx - 1);

        fprintf(out_fd, "%lu\n", res.idx);

    }

    fclose(in_fd);
    fclose(out_fd);

    return 0;
}

bool operator<(const Key& key1, const Key& key2) {

    if (key1.value == key2.value) {

        return key1.idx < key2.idx;

    }

    return key1.value < key2.value;
}

template <class Key>
SparseTable<Key>::SparseTable(const std::vector<key_t>& init_data) :
        size(init_data.size()),
        height(0) {

    log2 = new size_t[size + 1];

    for (size_t i = 1, pow = 1; i <= size; ++i) {

        if (i == pow) {
            pow <<= 1;
            ++height;
        }

        log2[i] = height - 1;
    }

    pow2 = new size_t[height];

    for (size_t i = 0, pow = 1; i < height; ++i, pow <<= 1) {
        pow2[i] = pow;
    }

    table = new key_t* [height];

    for (size_t i = 0; i < height; ++i) {
        table[i] = new key_t[size];
    }

    fill_table(init_data);
}

template <class Key>
void SparseTable<Key>::fill_table(const std::vector<key_t>& init_data) {

    for (size_t j = 0; j < size; ++j) {
        table[0][j] = init_data[j];
    }

    for (size_t step = 1, i = 1; i < height; ++i, step <<= 1) {
        for (size_t j = 0; j + 2 * step <= size; ++j) {

            table[i][j] = std::max(table[i - 1][j], table[i - 1][j + step]);

        }
    }
}

template <class Key>
Key SparseTable<Key>::get_max(const size_t& l_idx, const size_t& r_idx) {

    auto degree = log2[r_idx - l_idx + 1];
    return std::max(table[degree][l_idx], table[degree][r_idx - pow2[degree] + 1]);
}

template <class Key>
SparseTable<Key>::~SparseTable() {

    for (size_t i = 0; i < height; ++i) {
        delete[] table[i];
    }

    delete[] table;
    delete[] log2;
    delete[] pow2;
}