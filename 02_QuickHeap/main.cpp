#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>
#include <utility>

template <typename elem_type>
class Custom_QuickHeap {
/*
 * @brief An implementation of QuickHeap data structure
 * see Gonzalo Navarro and Rodrigo Paredes - "Quickheaps: Simple, Efficient, and Cache-Oblivious"
 */
public:
    explicit Custom_QuickHeap(const size_t max_capacity);
    Custom_QuickHeap(const std::vector<elem_type>& array, const size_t max_capacity);
    ~Custom_QuickHeap();

    void insert(const key_t& key, const elem_type& value);
    elem_type peakMin();
    elem_type extractMin();

    void size();
    void dump();

private:
    std::vector<elem_type>* heap;
    std::stack<size_t>* pivots;

    size_t heap_begin;
    size_t capacity;
    size_t current_size;

    size_t incremental_Qsort(std::vector<elem_type>& arr, const size_t arr_begin,
            std::stack<size_t>& pivot_stack);

    size_t do_partition(std::vector<elem_type>& arr, const elem_type pivot,
            const size_t arr_begin, const size_t arr_end);

    elem_type quickselect_median(std::vector<elem_type>& medians);

    elem_type pick_pivot(const std::vector<elem_type>& arr);

    elem_type insertion_median(std::vector<elem_type>& array);
};

int main() {

    Custom_QuickHeap<int> test_heap(100);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

template <typename elem_type>
Custom_QuickHeap<elem_type>::Custom_QuickHeap(const size_t max_capacity) {
    /*
     * @brief constructor of an empty QuickHeap
     * @param max_capacity - maximal amount of elements in heap
     */
    capacity = max_capacity + 1;  // + 1 is for artificial "+inf" pivot
    current_size = 0;

    heap   = new std::vector<elem_type>(capacity);
    pivots = new std::stack<size_t>;

    pivots->push(0);
    heap_begin = 0;
}

template <typename elem_type>
Custom_QuickHeap<elem_type>::Custom_QuickHeap(const std::vector<elem_type>& array,
        const size_t max_capacity) {
    /*
     * @brief constructor of a QuickHeap from an array;
     * @param array        - array from which heap will be built
     * @param max_capacity - maximal amount of elements in heap
     */
    capacity = std::max(max_capacity, array.size()) + 1; // + 1 is for artificial "+inf" pivot
    current_size = array.size();

    heap   = new std::vector<elem_type>(capacity);
    pivots = new std::stack<size_t>;

    pivots->push(array.size());
    heap_begin = 0;

    for (size_t i = 0; i < array.size(); ++i) {
        heap->at(i) = array[i];
    }
}

template <typename elem_type>
Custom_QuickHeap<elem_type>::~Custom_QuickHeap() {
    /*
     * @brief destructor of QuickHeap
     */
    while (!pivots->empty()) {
        pivots->pop();
    }
    delete pivots;

    heap->clear();
    delete heap;
}

template <typename elem_type>
size_t Custom_QuickHeap<elem_type>::incremental_Qsort(std::vector<elem_type>& arr, const size_t arr_begin,
                                                    std::stack<size_t>& pivot_stack) {
    /*
     * @brief an implementation of IncrementalQuickSort
     */
    if (arr_begin == pivot_stack.top()) {
        pivot_stack.pop();
        return (arr[arr_begin]);
    }

    size_t pivot_pos = do_partition(arr, pick_pivot(arr),
            arr_begin, pivot_stack.top() - 1);

    pivots->push(pivot_pos);

    return (incremental_Qsort(arr, arr_begin, pivot_stack));
}

template <typename elem_type>
size_t Custom_QuickHeap<elem_type>::do_partition(std::vector<elem_type>& arr, const elem_type pivot,
                                                 const size_t arr_begin, const size_t arr_end) {
    /*
     * @brief classical partition
     */
    size_t left_id  = arr_begin;
    size_t right_id = arr_end;

    while (left_id < right_id) {
        while (arr[left_id] <= pivot && left_id < right_id) {
            ++left_id;
        }
        while (arr[right_id] > pivot && left_id < right_id) {
            assert(right_id != 0);
            --right_id;
        }
        std::swap(arr[left_id++], arr[right_id--]);
    }
    return (left_id);
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::insertion_median(std::vector<elem_type>& array) {
    /*
     * @brief insertion sort
     * @return median
     */
    for (size_t i = 1; i < array.size(); ++i) {
        for (size_t j = i; j > 0 && array[j - 1] > array[j]; --j) {
            std::swap(array[j - 1], array[j]);
        }
    }
    return array[array.size() / 2];
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::pick_pivot(const std::vector<elem_type>& arr) {
    /*
     * @brief Median of medians algorithm
     */
    const size_t CHUNK_SIZE = 5;

    std::vector<elem_type> medians((arr.size() + CHUNK_SIZE - 1) / CHUNK_SIZE);
    std::vector<elem_type> chunk(CHUNK_SIZE);

    for (size_t i = 0; i < arr.size(); i += CHUNK_SIZE) {
        for (size_t j = i; j - i < chunk.size() && j < arr.size(); ++j) {
            chunk[j - i] = arr[j];
        }
        if (i + CHUNK_SIZE > arr.size()) {
            chunk.resize(arr.size() - i);
        }
        medians[i / 5] = insertion_median(chunk);
    }

    elem_type median_of_medians = quickselect_median(medians);

    return (median_of_medians);
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::quickselect_median(std::vector<elem_type> &medians) {

}



























