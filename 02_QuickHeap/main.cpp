#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <algorithm>

template <typename key_t, typename val_t>
class Custom_QuickHeap {
/*
 * @brief An implementation of QuickHeap data structure
 * see Gonzalo Navarro and Rodrigo Paredes - "Quickheaps: Simple, Efficient, and Cache-Oblivious"
 */
public:
    Custom_QuickHeap(const size_t max_capacity);
    Custom_QuickHeap(const std::vector<std::pair<key_t, val_t>>& array, const size_t max_capacity);
    ~Custom_QuickHeap();

    void insert(const key_t& key, const val_t& value);
    std::pair<key_t, val_t> peakMin();
    std::pair<key_t, val_t> extractMin();

    void size();
    void dump();

private:
    std::vector<std::pair<key_t, val_t>>* heap;
    std::stack<size_t>* pivots;

    size_t heap_begin;
    size_t capacity;
    size_t current_size;
};

template <typename key_t, typename val_t>
Custom_QuickHeap<key_t, val_t>::Custom_QuickHeap(const size_t max_capacity) {
    /*
     * @brief constructor of an empty QuickHeap
     * @param max_capacity - maximal amount of elements in heap
     */
    capacity = max_capacity + 1;  // + 1 is for artificial "+inf" pivot
    current_size = 0;

    heap   = new std::vector<std::pair<key_t, val_t>>(capacity);
    pivots = new std::stack<size_t>;

    pivots->push(0);
    heap_begin = 0;
}

template <typename key_t, typename val_t>
Custom_QuickHeap<key_t, val_t>::Custom_QuickHeap(const std::vector<std::pair<key_t, val_t>>& array,
        const size_t max_capacity) {
    /*
     * @brief constructor of a QuickHeap from an array;
     * @param array        - array from which heap will be built
     * @param max_capacity - maximal amount of elements in heap
     */
    capacity = std::max(max_capacity, array.size()) + 1; // + 1 is for artificial "+inf" pivot
    current_size = array.size();

    heap   = new std::vector<std::pair<key_t, val_t>>(capacity);
    pivots = new std::stack<size_t>;

    pivots->push(array.size());
    heap_begin = 0;

    for (size_t i = 0; i < array.size(); ++i) {
        heap->at(i) = array[i];
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}































