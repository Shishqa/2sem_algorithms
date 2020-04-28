#include <iostream>
#include <vector>
#include <algorithm>

class FenwickTree {
public:

    explicit FenwickTree(const uint32_t& size_x, const uint32_t& size_y);

    ~FenwickTree();

    unsigned long long prefix_sum(const uint32_t& idx);

    void set_hor(const uint32_t& y, const uint32_t& x_l, const uint32_t& x_r);
    void set_ver(const uint32_t& x, const uint32_t& y_d, const uint32_t& y_u);

private:

    const uint32_t size_x;
    const uint32_t size_y;

    uint8_t** tree;
};

int main() {

    std::ios_base::sync_with_stdio(false);

    uint32_t soldiers_count = 0;
    std::cin >> soldiers_count;

    std::vector<SoldierStat> soldiers_stats(soldiers_count);



    return 0;
}

void FenwickTree::inc(const uint32_t& idx) {

    for (int32_t i = idx; i < size; i |= i + 1) {
        ++tree[i];
    }
}

unsigned long long FenwickTree::prefix_sum(const uint32_t& idx) {

    uint32_t sum = 0;

    for (int32_t i = idx; i >= 0; i = (i & (i + 1)) - 1) {
        sum += tree[i];
    }

    return sum;
}

FenwickTree::FenwickTree(const uint32_t& size_x, const uint32_t& size_y) :
        size_x(size_x),
        size_y(size_y) {

    tree = new uint8_t*[size_y];

    for (uint32_t i = 0; i < size_y; ++i) {
        tree[i] = new uint8_t[size_x];

        for ()
    }
}

FenwickTree::~FenwickTree() {

    delete tree;
}