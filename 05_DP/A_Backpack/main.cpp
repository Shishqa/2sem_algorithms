#include <iostream>
#include <vector>
#include <stack>

template <typename T>
using vector = std::vector<T>;

template <typename T>
using matrix = vector<vector<T>>;

int main() {

    size_t num_of_items = 0;
    std::cin >> num_of_items;

    size_t backpack_capacity = 0;
    std::cin >> backpack_capacity;

    vector<uint32_t> item_weight(num_of_items + 1);
    for (size_t i = 1; i <= num_of_items; ++i) {
        std::cin >> item_weight[i];
    }

    vector<uint32_t> item_cost(num_of_items + 1);
    for (size_t i = 1; i <= num_of_items; ++i) {
        std::cin >> item_cost[i];
    }

    matrix<uint32_t> tmp_set(num_of_items + 1, vector<uint32_t>(backpack_capacity + 1, 0));

    for (size_t curr_item = 1; curr_item <= num_of_items; ++curr_item) {
        for (size_t curr_cap = 1; curr_cap <= backpack_capacity; ++curr_cap) {

            if (curr_cap >= item_weight[curr_item]) {

                tmp_set[curr_item][curr_cap] = std::max(tmp_set[curr_item - 1][curr_cap],
                                                        tmp_set[curr_item - 1][curr_cap - item_weight[curr_item]] +
                                                        item_cost[curr_item]);

            } else {

                tmp_set[curr_item][curr_cap] = tmp_set[curr_item - 1][curr_cap];

            }
        }
    }

    size_t curr_cap = backpack_capacity;
    size_t curr_item = num_of_items;

    std::stack<uint32_t> taken_items;

    while (tmp_set[curr_item][curr_cap] != 0) {

        if (tmp_set[curr_item][curr_cap] > tmp_set[curr_item - 1][curr_cap]) {

            taken_items.push(curr_item);
            curr_cap -= item_weight[curr_item];

        }
        --curr_item;
    }

    std::cout << taken_items.size() << std::endl;

    while (!taken_items.empty()) {

        std::cout << taken_items.top() << " ";
        taken_items.pop();

    }

    return 0;
}
