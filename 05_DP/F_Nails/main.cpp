#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    const int MAX_DIFF = 20000;

    size_t nail_cnt = 0;
    std::cin >> nail_cnt;

    std::vector<int> nail_pos(nail_cnt);

    for (auto& gap: nail_pos) {
        std::cin >> gap;
    }
    std::sort(nail_pos.begin(), nail_pos.end());

    std::vector<int> nail_dp(nail_cnt);
    nail_dp[0] = MAX_DIFF;
    nail_dp[1] = nail_pos[1] - nail_pos[0];

    for (size_t i = 2; i < nail_cnt; ++i) {
        nail_dp[i] = nail_pos[i] - nail_pos[i - 1] + std::min(nail_dp[i - 1], nail_dp[i - 2]);
    }

    std::cout << nail_dp[nail_cnt - 1] << std::endl;

    return 0;
}
