#include <cstdio>
#include <vector>
#include <iostream>
#include <stack>

struct Stat {

    size_t less_left;
    size_t greater_left;
    size_t less_right;
    size_t greater_right;

    size_t left_lower_bound;
    size_t left_upper_bound;
    size_t right_lower_bound;
    size_t right_upper_bound;

    Stat() = default;
    Stat(const Stat& other) = default;
    ~Stat() = default;
};

int main() {

    size_t data_size = 0;
    scanf("%lu", &data_size);

    std::vector<int> data(data_size);

    for (size_t i = 0; i < data_size; ++i) {
        scanf("%d", &data[i]);
    }

    std::vector<Stat> stats(data_size);

    stats[0].greater_left = 0;
    stats[0].less_left = 0;
    stats[data_size - 1].greater_right = 0;
    stats[data_size - 1].less_right = 0;

    std::stack<size_t> left_less;
    std::stack<size_t> left_greater;
    std::stack<size_t> right_less;
    std::stack<size_t> right_greater;

    for (size_t i = 1, j = data_size - 2; i < data_size - 1; ++i, --j) {

        if (data[i - 1] < data[i]) {
            stats[i].less_left = stats[i - 1].less_left + 1;
            stats[i].greater_left = stats[stats[i].left_lower_bound].greater_left + 1;
        } else {
            stats[i].greater_left = stats[i - 1].greater_left + 1;
            stats[i].less_left = stats[stats[i].left_upper_bound].less_left + 1;
        }

        if (data[j] < data[j + 1]) {
            stats[j].greater_right = stats[j + 1].greater_right + 1;
            stats[j].less_right = i - stats[j].greater_right;
        } else {
            stats[j].less_right = stats[j + 1].less_right + 1;
            stats[j].greater_right = i - stats[j].less_right;
        }

    }

    for (size_t i = 0; i < data_size; ++i) {

        std::cout << data[i] << "(" << i <<  ")\t| ";
        std::cout << " left:\t '<' " << stats[i].less_left << " '>' " << stats[i].greater_left;
        std::cout << " right:\t '<' " << stats[i].less_right << " '>' " << stats[i].greater_right;
        std::cout << std::endl;

    }

    return 0;
}
