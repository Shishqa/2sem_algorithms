#include <iostream>
#include <vector>

template <typename T>
using vector = std::vector<T>;

template <typename T>
using matrix = vector<vector<T>>;

typedef unsigned int uint_t;

int main() {

    int planet_cnt = 0;
    std::cin >> planet_cnt;

    matrix<uint_t> cost(planet_cnt, vector<uint_t>(planet_cnt, 0));

    const uint_t INF = UINT32_MAX;

    for (int i = 0; i < planet_cnt; ++i) {
        for (int j = 0; j < planet_cnt; ++j) {
            if (i == j) {
                cost[i][j] = INF;
            }
            std::cin >> cost[i][j];
        }
    }

    matrix<uint_t> dp(1 << planet_cnt, vector<uint_t>(planet_cnt, INF));

    dp[0][0] = 0;

    const uint_t ALL_MASK = (1 << planet_cnt) - 1;
    uint_t u_mask = 0;

    for (size_t mask = 0; mask <= ALL_MASK; ++mask) {
        for (size_t v = 0; v < planet_cnt; ++v) {
            if (dp[mask][v] == INF) {
                continue;
            }
            for (size_t u = 0; u < planet_cnt; ++u) {
                u_mask = 1 << u;
                if (!(mask & u_mask) && dp[mask | u_mask][u] > dp[mask][v] + cost[v][u]) {
                    dp[mask | u_mask][u] = dp[mask][v] + cost[v][u];
                }
            }
        }
    }

    uint_t best_cost = INF;
    uint_t last = 0;
    for (size_t v = 0; v < planet_cnt; ++v) {
        if (dp[ALL_MASK][v] < best_cost) {
            best_cost = dp[ALL_MASK][v];
            last = v;
        }
    }

    vector<uint_t> way(planet_cnt, -1);

    uint_t mask = ALL_MASK;
    while (mask > 0) {

        mask ^= (1 << last);

        for (size_t v = 0; v < planet_cnt; ++v) {
            if (dp[mask][v] == INF) {
                continue;
            }
            if (dp[mask | (1 << last)][last] == dp[mask][v] + cost[v][last]) {

                way[v] = last;
                last = v;
                break;
            }
        }
    }

    std::cout << best_cost << std::endl;

    for (size_t v = last, cnt = 0; cnt < planet_cnt; ++cnt, v = way[v]) {
        std::cout << v + 1 << " ";
    }

    return 0;
}
