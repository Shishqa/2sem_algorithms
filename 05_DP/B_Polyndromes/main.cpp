#include <iostream>
#include <vector>
#include <string>

template <typename T>
using vector = std::vector<T>;

int main() {

    size_t str_len = 0;
    std::cin >> str_len;

    size_t poly_cutoff = 0;
    std::cin >> poly_cutoff;

    std::string str;
    std::cin >> str;

    vector<vector<uint16_t>> poly_diff(str_len, vector<uint16_t>(str_len, 0));

    uint32_t near_poly_cnt = 0;

    for (size_t i_len = 2; i_len <= str_len; ++i_len) {
        for (size_t i = 0; i <= str_len - i_len; ++i) {

            poly_diff[i][i + i_len - 1] = poly_diff[i + 1][i + i_len - 2] + (str[i] == str[i + i_len - 1] ? 0 : 1);

            if (poly_diff[i][i + i_len - 1] <= poly_cutoff) {
                ++near_poly_cnt;
            }
        }
    }

    near_poly_cnt += str_len;
    std::cout << near_poly_cnt << std::endl;

    return 0;
}
