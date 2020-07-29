#include <iostream>
#include <vector>
#include <queue>
#include <utility>

template <typename T>
using vector = std::vector<T>;

template <typename T>
using matrix = vector<vector<T>>;

template <typename T>
using queue = std::queue<T>;

template <typename T1, typename T2>
using pair = std::pair<T1, T2>;

typedef pair<int, int> dot_t;
typedef vector<dot_t> dot_arr_t;

#define y first  // bad style but ya
#define x second

matrix<int> get_map(size_t& map_height, size_t& map_width,
                    dot_t& start, dot_t& target);

matrix<vector<pair<int, int>>> get_nearest_walls(const matrix<int>& map);

int main() {

    size_t map_height = 0,
           map_width  = 0;

    dot_t start  = {},
          target = {};

    matrix<int> map = get_map(map_height, map_width, start, target);

    //===========================================================================

    matrix<dot_arr_t> walls = get_nearest_walls(map);

    //===========================================================================

    queue<dot_t> to_visit;
    to_visit.push({start.y, start.x});

    const size_t INF = UINT32_MAX;
    matrix<size_t> path_len(map_height, vector<size_t>(map_height, INF));
    path_len[start.y][start.x] = 0;

    const pair<int, int> delta[4] = {
            {1,  0}, // UP
            {-1, 0}, // DOWN
            {0,  1}, // RIGHT
            {0, -1}  // LEFT
    };

    dot_t curr_pos;
    dot_t curr_dest;
    bool near_wall = false;

    while (!to_visit.empty()) {

        curr_pos = to_visit.front();
        to_visit.pop();

        near_wall = false;

        for (auto d : delta) {

            curr_dest = {curr_pos.y + d.y, curr_pos.x + d.x};

            if (path_len[curr_dest.y][curr_dest.x] == INF &&
                map[curr_dest.y][curr_dest.x] != -1) {

                path_len[curr_dest.y][curr_dest.x] = path_len[curr_pos.y][curr_pos.x] + 1;
                to_visit.push(curr_dest);

            } else if (map[curr_dest.y][curr_dest.x] == -1) {
                near_wall = true;
            }
        }

        if (near_wall) {

        }
    }

    return 0;
}

matrix<int> get_map(size_t& map_height, size_t& map_width,
                    dot_t& start, dot_t& target) {

    const char WALL   = '#',
               EMPTY  = '.',
               START  = 'S',
               TARGET = 'T';

    std::cin >> map_height >> map_width;

    matrix<int>&& map = matrix<int>(map_height, vector<int>(map_width));

    char tmp = 0;
    for (size_t i = 0; i < map_height; ++i) {
        for (size_t j = 0; j < map_width; ++j) {

            std::cin >> tmp;
            switch (tmp) {
                case WALL:
                    map[i][j] = -1;
                    break;
                case START:
                    start.y  = i;
                    start.x  = j;
                    break;
                case TARGET:
                    target.y = i;
                    target.x = j;
                    break;
                default:
                    break;
            }
        }
    }

    return map;
}

matrix<dot_arr_t> get_nearest_walls(const matrix<int>& map) {

    size_t map_height = map.size(),
           map_width  = map[0].size();

    matrix<dot_arr_t>&& wall_deltas = matrix<dot_arr_t>(map_height, vector<dot_arr_t>(map_width, dot_arr_t(4)));

    for (size_t i = 0; i < map_height; ++i) {
        for (size_t j = 0; j < map_width; ++j) {

            if (map[i][j] == -1) {
                wall_deltas[i][j][0] = {0,0}; // LEFT
                wall_deltas[i][j][1] = {0,0}; // UP
                wall_deltas[i][j][2] = {0,0}; // RIGHT
                wall_deltas[i][j][3] = {0,0}; // DOWN
            } else {
                wall_deltas[i][j][0] = wall_deltas[i][j - 1][0];
                wall_deltas[i][j][0].x -= 1;

                wall_deltas[i][j][1] = wall_deltas[i - 1][j][1];
                wall_deltas[i][j][1].y -= 1;
            }
        }
    }

    for (int64_t i = map_height - 1; i >= 0; --i) {
        for (int64_t j = map_width - 1; j >= 0; --j) {

            if (map[i][j] != -1) {
                wall_deltas[i][j][2] = wall_deltas[i][j + 1][2];
                wall_deltas[i][j][2].x += 1;

                wall_deltas[i][j][3] = wall_deltas[i + 1][j][3];
                wall_deltas[i][j][3].y += 1;
            }
        }
    }

    return wall_deltas;
}