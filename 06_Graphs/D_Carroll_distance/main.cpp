#include <cstring>
#include <cstdio>
#include <iostream>
#include <map>
#include <string_view>
#include <vector>

template <typename T>
using vector = std::vector<T>;

char* load_buffer(const size_t& num_words, size_t& buf_size, size_t& word_size);

int main() {

    const size_t INF = INT32_MAX;

    size_t dict_size = 0;
    std::cin >> dict_size;

    size_t buf_size  = 0;
    size_t word_size = 0;
    const char* buffer = load_buffer(dict_size, buf_size, word_size);

    vector<std::string_view> words(dict_size);
    for (size_t i = 0; i < dict_size; ++i) {
        words[i] = std::string_view(buffer + i * (word_size + 1));
    }

    vector<vector<int>> d(dict_size, vector<int>(dict_size, INF));
    for (size_t i = 0; i < dict_size; ++i) {
        d[i][i] = 0;
    }

    size_t diff_cnt = 0;
    for (size_t i = 0; i < dict_size; ++i) {
        for (size_t j = i + 1; j < dict_size; ++j) {

            diff_cnt = 0;
            for (size_t k = 0; k < word_size; ++k) {
                if (words[i][k] != words[j][k]) {
                    ++diff_cnt;
                }
            }

            if (diff_cnt == 1) {
                d[i][j] = 1;
                d[j][i] = 1;
            }
        }
    }

    for (size_t k = 0; k < dict_size; ++k) {
        for (size_t i = 0; i < dict_size; ++i) {
            for (size_t j = 0; j < dict_size; ++j) {

                if (d[i][k] != INF && d[k][j] != INF) {
                    d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
                }

            }
        }
    }



    for (size_t i = 0; i < dict_size; ++i) {
        for (size_t j = 0; j < dict_size; ++j) {
            std::cout << d[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

char* load_buffer(const size_t& num_words, size_t& buf_size, size_t& word_size) {

    std::string word;
    std::cin >> word;

    word_size = word.length();
    buf_size = (word_size + 1) * num_words;

    char* buffer = new char[buf_size];
    memcpy(buffer, word.c_str(), word_size);

    for (size_t i = word_size + 1; i < buf_size; i += word_size + 1) {
        std::cin >> (buffer + i);
    }

    return buffer;
}
