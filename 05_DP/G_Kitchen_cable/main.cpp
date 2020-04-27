#include <iostream>
#include <vector>

int main() {

    size_t cable_cnt = 0;
    std::cin >> cable_cnt;

    std::vector<double> cable_len(cable_cnt);
    for (auto& gap : cable_len) {
        std::cin >> gap;
    }

    std::vector<double> best_len(cable_cnt, -1);

    for (size_t curr_cable = 0; curr_cable < cable_cnt; ++curr_cable) {



    }

    return 0;
}
