#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>
#include <utility>
#include <deque>

template <typename elem_type>
class Custom_QuickHeap {
/*
 * @brief An implementation of QuickHeap data structure
 * see Gonzalo Navarro and Rodrigo Paredes - "Quickheaps: Simple, Efficient, and Cache-Oblivious"
 */
public:
    explicit Custom_QuickHeap(size_t max_capacity);
    ~Custom_QuickHeap();

    void insert(const elem_type& element);
    elem_type peakMin();
    elem_type extractMin();

    void size();
    void dump();

private:
    FILE* log;

    std::vector<elem_type>* heap;
    std::stack<size_t>* pivots;

    size_t heap_begin;
    size_t capacity;
    size_t current_size;

    size_t incremental_Qsort(std::vector<elem_type>& arr, size_t arr_begin,
                             std::stack<size_t>& pivot_stack);

    size_t do_partition(std::vector<elem_type>& arr, elem_type pivot,
                        size_t arr_begin, size_t arr_end);

    elem_type pick_pivot(const std::vector<elem_type>& arr,
                         size_t arr_begin, size_t arr_end);

    elem_type quickselect_stat(std::vector<elem_type> &arr, size_t k,
                               size_t arr_begin, size_t arr_end);

    elem_type insertion_stat(std::vector<elem_type>& arr, size_t k,
                             size_t arr_begin, size_t arr_end);
};

int main() {

    Custom_QuickHeap<int> test_heap(100);

    for (int i = 100; i < 120; ++i) {
        test_heap.insert((12999 * i + 21121) % 68311);
        printf("%d ", (12999 * i + 21121) % 68311);
    }
    printf("\n");

    test_heap.dump();

    printf("min: %d\n", test_heap.peakMin());

    test_heap.dump();

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

    heap->at(0) = static_cast<int>(1e9) + 1;

    log = fopen("log.out", "w");
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

    fclose(log);
}

template <typename elem_type>
void Custom_QuickHeap<elem_type>::dump() {
    printf("current size = %lu\n", current_size);
    printf("capacity = %lu\n", capacity);
    printf("heap:");
    for (size_t i = 0; i < current_size + 1; ++i) {
        printf(" %d", heap->at((heap_begin + i) % capacity));
    }
    printf("\n");
}

template <typename elem_type>
void Custom_QuickHeap<elem_type>::insert(const elem_type& element) {
    /*
     * @brief inserts element to the QuickHeap
     */
    if (current_size == capacity - 1) {
        return;
    }

    std::stack<size_t> pivot_buffer;
    size_t pivot_index = pivots->top();

    while (element > heap->at(pivot_index)) {
        pivot_buffer.push(pivot_index);
        pivots->pop();
        pivot_index = pivots->top();
    }

    elem_type moving_element = element;

    do {
        std::swap(moving_element, heap->at(pivot_index + 1));
        std::swap(heap->at((pivot_index + 1) % capacity), heap->at(pivot_index));

        pivot_buffer.push((pivot_index + 1) % capacity);
        pivots->pop();
        pivot_index = (!pivots->empty() ? pivots->top() : 0);
    } while (!pivots->empty());

    while (!pivot_buffer.empty()) {
        pivots->push(pivot_buffer.top());
        pivot_buffer.pop();
    }

    ++current_size;
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::peakMin() {
    /*
     * @brief gets minimum in heap
     * @return minimum
     */
    incremental_Qsort(*heap, heap_begin, *pivots);
    return (heap->at(heap_begin));
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::extractMin() {
    /*
     * @brief gets minimum in heap and erases it
     * @return minimum
     */
    incremental_Qsort(*heap, heap_begin, *pivots);
    elem_type minimum = heap->at(heap_begin);
    heap_begin = (heap_begin + 1) % capacity;
    pivots->pop();
    return (minimum);
}

template <typename elem_type>
size_t Custom_QuickHeap<elem_type>::incremental_Qsort(std::vector<elem_type>& arr, const size_t arr_begin,
                                                      std::stack<size_t>& pivot_stack) {
    /*
     * @brief an implementation of IncrementalQuickSort
     */

    fprintf(log, "IQS::->\n");

    if (arr_begin == pivot_stack.top()) {
        pivot_stack.pop();
        fprintf(log, "IQS::<------------\n");
        return (arr[arr_begin]);
    }

    fprintf(log, "IQS::picking pivot on [%lu, %lu)\n", arr_begin, pivot_stack.top());
    elem_type pivot = pick_pivot(arr, arr_begin, pivot_stack.top());

    fprintf(log, "IQS::pivot = %d\n", pivot);

    size_t pivot_pos = do_partition(arr, pivot, arr_begin, pivot_stack.top());

    fprintf(log, "IQS::pivot pos = %lu\n", pivot_pos);

    pivot_stack.push(pivot_pos);

    return (incremental_Qsort(arr, arr_begin, pivot_stack));
}

template <typename elem_type>
size_t Custom_QuickHeap<elem_type>::do_partition(std::vector<elem_type>& arr, const elem_type pivot,
                                                 const size_t arr_begin, const size_t arr_end) {
    /*
     * @brief classical partition
     */

    fprintf(log, "partition::->%d [%lu, %lu)\n", pivot, arr_begin, arr_end);

    size_t less_idx    = arr_begin;
    size_t equal_idx   = arr_begin;
    size_t greater_idx = arr_begin;

    for (; greater_idx < arr_end - 1; ++greater_idx) {
        if (arr[greater_idx] == pivot) {
            std::swap(arr[equal_idx++], arr[greater_idx]);
        } else if (arr[greater_idx] < pivot) {
            elem_type temp_elem = arr[greater_idx];
            arr[greater_idx] = arr[equal_idx + 1];
            arr[equal_idx + 1] = arr[equal_idx];
            arr[equal_idx++] = arr[less_idx + 1];
            arr[less_idx + 1] = arr[less_idx];
            arr[less_idx++] = temp_elem;
        }
    }

    fprintf(log, "partition::<-");
    for (size_t i = arr_begin; i < arr_end; ++i) {
        fprintf(log, "%d ", arr[i]);
    }
    fprintf(log, "[%lu, %lu, %lu]\n", less_idx, equal_idx, greater_idx);

    return (less_idx);
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::pick_pivot(const std::vector<elem_type>& arr,
                                                  const size_t arr_begin, const size_t arr_end) {
    /*
     * @brief Median of medians algorithm
     */
    fprintf(log, "pivot::->median of medians\n");
    const size_t CHUNK_SIZE = 5;
    std::vector<elem_type> chunk(CHUNK_SIZE);

    if (arr_end - arr_begin <= CHUNK_SIZE) {
        chunk.resize(arr_end - arr_begin);

        for (size_t i = 0; i < chunk.size(); ++i) {
            chunk[i] = arr[arr_begin + i];
        }

        return (insertion_stat(chunk, chunk.size() / 2, 0, chunk.size()));
    }

    std::vector<elem_type> medians((arr_end - arr_begin + CHUNK_SIZE + 1) / CHUNK_SIZE);

    for (size_t i = arr_begin; i < arr_end; i += CHUNK_SIZE) {
        for (size_t j = i; j - i < chunk.size() && j < arr_end; ++j) {
            chunk[j - i] = arr[j];
        }
        if (i + CHUNK_SIZE > arr_end) {
            chunk.resize(arr_end - i);
        }
        medians[i / 5] = insertion_stat(chunk, chunk.size() / 2, 0, chunk.size());
        fprintf(log, "%lu median is %d\n", i / 5, medians[i / 5]);
    }

    fprintf(log, "pivot::<-big\n");
    elem_type median_of_medians = quickselect_stat(medians, medians.size() / 2, 0, medians.size());

    return (median_of_medians);
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::quickselect_stat(std::vector<elem_type> &arr, const size_t k,
                                                        const size_t arr_begin, const size_t arr_end) {
    /*
     * @brief quickselect algorithm
     * @return arr k_th statistics
     */
    fprintf(log, "quickselect::->\n");
    const size_t SIZE_FOR_INSERTION = 20;

    if (arr_end - arr_begin <= SIZE_FOR_INSERTION) {
        fprintf(log, "quickselect::<----insertion\n");
        return (insertion_stat(arr, k, arr_begin, arr_end));
    }

    elem_type pivot  = pick_pivot(arr, arr_begin, arr_end);
    size_t pivot_pos = do_partition(arr, pivot, arr_begin, arr_end);

    if (pivot_pos == k) {
        fprintf(log, "quickselect::<----\n");
        return (arr[pivot_pos]);
    } else if (pivot_pos < k) {
        return (quickselect_stat(arr, k - pivot_pos, pivot_pos + 1, arr_end));
    } else {
        return (quickselect_stat(arr, k, arr_begin, pivot_pos));
    }
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::insertion_stat(std::vector<elem_type>& arr, const size_t k,
                                                      const size_t arr_begin, const size_t arr_end) {
    /*
     * @brief insertion sort
     * @return k_th statistics
     */
    fprintf(log, "insertion::->\n");

    for (size_t i = arr_begin + 1; i < arr_end; ++i) {
        for (size_t j = i; j > arr_begin && arr[j - 1] > arr[j]; --j) {
            std::swap(arr[j - 1], arr[j]);
        }
    }
    fprintf(log, "insertion::<-%d\n", arr[k]);
    return (arr[k]);
}




























