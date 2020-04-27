#include <iostream>
#include <vector>

template <typename T>
using vector = std::vector<T>;

template <typename T>
using matrix = vector<vector<T>>;

int walk_to(const size_t& x, const size_t& y, const size_t left_stamina, const size_t right_stamina, matrix<int>& map) {

    if (map[y][x] == -1 || left_stamina + right_stamina <= map[y][x]) {
        return 0;
    }

    map[y][x] = left_stamina + right_stamina; // stepped

    int neighbour_cnt = 1;

    if (left_stamina) {
        neighbour_cnt += walk_to(x - 1, y, left_stamina - 1, right_stamina, map);
    }

    if (right_stamina) {
        neighbour_cnt += walk_to(x + 1, y, left_stamina, right_stamina - 1, map);
    }

    neighbour_cnt += walk_to(x, y + 1, left_stamina, right_stamina, map);
    neighbour_cnt += walk_to(x, y - 1, left_stamina, right_stamina, map);

    return neighbour_cnt;
}

int main() {

    size_t height = 0;
    size_t width  = 0;
    std::cin >> height >> width;

    matrix<int> maze_map(height + 2, vector<int>(width + 2, -1));

    size_t x_start = 0;
    size_t y_start = 0;
    std::cin >> y_start >> x_start;

    size_t left_stamina  = 0;
    size_t right_stamina = 0;
    std::cin >> left_stamina >> right_stamina;

    char point = 0;

    for (size_t i = 1; i <= height; ++i) {
        for (size_t j = 1; j <= width; ++j) {

            std::cin >> point;

            if (point == '.') {
                maze_map[i][j] = 0;
            }
        }
    }

    std::cout << walk_to(x_start, y_start, left_stamina, right_stamina, maze_map) << std::endl;

//    for (size_t i = 0; i <= height + 1; ++i) {
//        for (size_t j = 0; j <= width + 1; ++j) {
//            std::cout << maze_map[i][j] << "\t ";
//        }
//        std::cout << std::endl;
//    }


    return 0;
}