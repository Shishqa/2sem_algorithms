#include <iostream>
#include <vector>
#include <algorithm>

class FenwickTree {
public:

    explicit FenwickTree(const uint32_t& size);

    ~FenwickTree();

    unsigned long long sum(const uint32_t& idx);

    void inc(const uint32_t& idx);

private:

    const uint32_t size;

    uint32_t* tree;
};

struct SoldierStat {

    uint32_t power;
    uint32_t idx;

    SoldierStat() = default;
    SoldierStat(const SoldierStat& other) = default;
    ~SoldierStat() = default;
};

bool cmp_stat(const SoldierStat& stat_1, const SoldierStat& stat_2);

int main() {

    std::ios_base::sync_with_stdio(false);

    uint32_t soldiers_count = 0;
    std::cin >> soldiers_count;

    std::vector<SoldierStat> soldiers_stats(soldiers_count);

    for (uint32_t i = 0; i < soldiers_count; ++i) {
        std::cin >> soldiers_stats[i].power;
        soldiers_stats[i].idx = i;
    }

    std::sort(soldiers_stats.begin(), soldiers_stats.end(), cmp_stat);

    FenwickTree prefix_superiors(soldiers_count);

    unsigned long long left_superior_cnt  = 0;
    unsigned long long right_inferior_cnt = 0;
    unsigned long long weakness_index     = 0;

    for (uint32_t i = 0; i < soldiers_count; ++i) {
        left_superior_cnt = prefix_superiors.sum(soldiers_stats[i].idx);
        prefix_superiors.inc(soldiers_stats[i].idx);

        right_inferior_cnt = soldiers_count + left_superior_cnt - soldiers_stats[i].idx  - i - 1;

        weakness_index += left_superior_cnt * right_inferior_cnt;
    }

    std::cout << weakness_index << std::endl;

    return 0;
}

bool cmp_stat(const SoldierStat& stat_1, const SoldierStat& stat_2) {
    return stat_1.power > stat_2.power;
}

void FenwickTree::inc(const uint32_t& idx) {

    for (int32_t i = idx; i < size; i |= i + 1) {
        ++tree[i];
    }
}

unsigned long long FenwickTree::sum(const uint32_t& idx) {

    uint32_t sum = 0;

    for (int32_t i = idx; i >= 0; i = (i & (i + 1)) - 1) {
        sum += tree[i];
    }

    return sum;
}

FenwickTree::FenwickTree(const uint32_t& size) :
        size(size) {

    tree = new uint32_t[size];

    for (uint32_t i = 0; i < size; ++i) {
        tree[i] = 0;
    }
}

FenwickTree::~FenwickTree() {

    delete tree;
}