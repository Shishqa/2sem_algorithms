#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <queue>

int main() {

    size_t num_of_cars = 0;
    std::cin >> num_of_cars;

    size_t floor_size = 0;
    std::cin >> floor_size;

    size_t num_of_requests = 0;
    std::cin >> num_of_requests;

    std::vector<size_t> requests(num_of_requests);
    std::vector<std::queue<size_t>> nearest_request(num_of_cars);

    for (size_t i = 0; i < num_of_requests; ++i) {

        std::cin >> requests[i];
        nearest_request[requests[i]].push(i);
    }

    std::set<std::pair<size_t, size_t>> floor;
    std::vector<size_t> last_request_time(num_of_cars);

    size_t num_of_operations = 0;

    for (size_t i = 0; i < num_of_requests; ++i) {

        if (!floor.count({last_request_time[requests[i]], requests[i]})) {





        }

        floor.erase({last_request_time[requests[i]], requests[i]});

        floor.insert({i, requests[i]});

        nearest_request[requests[i]].pop();

    }

    std::cout << num_of_operations << std::endl;

    return 0;
}






































