#include <iostream>
#include <vector>
#include <climits>

template <typename T>
using vector = std::vector<T>;

template <typename T>
using matrix = vector<vector<T>>;

const int INF = INT_MAX;

int BellmanFord(const matrix<int>& cost, const size_t& start, const size_t& finish, const size_t& max_len) {

    size_t v_cnt = cost.size();

    vector<int> dist(v_cnt, INF);
    vector<int> len(v_cnt, INF);

    dist[start] = 0;
    len[start] = 0;

    for (size_t phase = 0; phase < v_cnt; ++phase) {
        for (size_t v = 0; v < v_cnt; ++v) {
            for (size_t u = 0; u < v_cnt; ++u) {

                if (cost[v][u] != INF && dist[v] + cost[v][u] < dist[u]) {
                    if ((u == finish && len[v] + 1 <= max_len) || (len[v] + 1 < max_len)) {
                        dist[u] = dist[v] + cost[v][u];
                        len[u] = len[v] + 1;
                    }
                }

            }
        }
    }

    return (dist[finish] == INF ? -1 : dist[finish]);
}

int main() {

    // (▀̿Ĺ̯▀̿ ) ( ͡º◞ل͟◟ ͡º)
    //   Fort      Beltman

    size_t city_cnt = 0;
    std::cin >> city_cnt;

    size_t flight_cnt = 0;
    std::cin >> flight_cnt;

    size_t nights_left = 0;
    std::cin >> nights_left;

    size_t departure_city = 0;
    std::cin >> departure_city;

    size_t arrival_city = 0;
    std::cin >> arrival_city;

    matrix<int> cost(city_cnt, vector<int>(city_cnt, INF));

    size_t dep = 0;
    size_t arr = 0;
    int pay = 0;

    for (size_t i = 0; i < flight_cnt; ++i) {
        std::cin >> dep >> arr >> pay;
        cost[dep - 1][arr - 1] = std::min(cost[dep - 1][arr - 1], pay);
    }

    std::cout << BellmanFord(cost, departure_city - 1, arrival_city - 1, nights_left) << std::endl;

    return 0;
}
