#include <iostream>
#include <stack>
#include <vector>

int main() {

    uint32_t data_size = 0;
    std::cin >> data_size;

    std::vector<int> data(data_size);

    for (auto& gap : data) {
        std::cin >> gap;
    }

    std::vector<int32_t> left_nearest_less(data_size, -1);

    std::stack<uint32_t> unmatched_elems;

    for (int32_t i = data_size - 1; i >= 0; --i) {

        while (!unmatched_elems.empty() && data[unmatched_elems.top()] > data[i]) {

            left_nearest_less[unmatched_elems.top()] = i;
            unmatched_elems.pop();

        }

        unmatched_elems.push(i);
    }

    std::vector<uint32_t> max_seq(data_size);
    std::vector<uint32_t> res_len(data_size);

    for (uint32_t i = 0; i < data_size; ++i) {

        std::cout << left_nearest_less[i] << " ";

        if (left_nearest_less[i] == -1) {
            max_seq[i] = 1;
        } else {
            max_seq[i] = max_seq[left_nearest_less[i]] + 1;
        }

        if (i > 0) {
            res_len[i] = std::max(res_len[i - 1], max_seq[i]);
        } else {
            res_len[i] = max_seq[i];
        }
    }

    for (auto x : res_len) {
        std::cout << x << " ";
    }

    return 0;
}
