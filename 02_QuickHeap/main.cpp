#include <vector>
#include <stack>
#include <utility>
#include <deque>
#include <cstring>
#include <stdexcept>

template <typename elem_type>
class Custom_QuickHeap {
/*
 * @brief An implementation of QuickHeap data structure
 * see Gonzalo Navarro and Rodrigo Paredes - "Quickheaps: Simple, Efficient, and Cache-Oblivious"
 */
public:
    explicit Custom_QuickHeap(size_t max_capacity, elem_type MAX_BORDER,
                              int (*cmp)(elem_type a, elem_type b) = default_comparator);
    ~Custom_QuickHeap();

    void insert(const elem_type& element);
    elem_type peakMin();
    elem_type extractMin();

    size_t size();
    void dump();

private:
    elem_type INF;

    std::vector<elem_type>* heap;
    std::stack<size_t>* pivots;

    size_t heap_begin;
    size_t capacity;
    size_t current_size;

    /*
     * cmp_elem(a, b) = 0 if a == b
     *                  positive int if a > b
     *                  negative int if a < b
     */
    int (*cmp_elem)(elem_type a, elem_type b);

    static int default_comparator(elem_type a, elem_type b);

    elem_type incremental_Qsort(std::vector<elem_type>& arr, size_t arr_begin,
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

class Memory_manager {

public:
    explicit Memory_manager(size_t memory_size);
    ~Memory_manager();

    struct Block {
        Block(bool full_or_empty, size_t block_size, size_t block_begin,
              Block* next = nullptr, Block* prev = nullptr);
        ~Block();

        bool is_valid;
        bool is_empty;

        size_t size;
        size_t begin;

        Block* next_block;
        Block* prev_block;
    };

    Block* allocate(size_t block_size);
    void free(Block* block);

    static int cmp_blocks(Block * a, Block * b);

private:
    const size_t MAX_BLOCK_CNT = 600000;

    enum {
        FULL = 0,
        EMPTY = 1
    };

    enum {
        NOT_VALID = 0,
        VALID = 1
    };

    Custom_QuickHeap<Block*>* empty_blocks;

    Block* memory_begin;
    Block* memory_end;

    void remove_rubbish();
};

int main() {

    size_t memory_size = 0;
    scanf("%lu", &memory_size);

    Memory_manager RAM_director(memory_size);

    size_t num_requests = 0;
    scanf("%lu", &num_requests);

    enum {
        ALLOC = 0,
        FREE = 1
    };

    std::vector<Memory_manager::Block*> request_results(num_requests + 1, nullptr);
    std::vector<bool> request_type(num_requests + 1);

    long request = 0;

    for (size_t i = 1; i <= num_requests; ++i) {

        scanf("%ld", &request);

        if (request > 0) {
            request_results[i] = RAM_director.allocate(static_cast<size_t>(request));

            if (!request_results[i]) {
                printf("-1\n");
            } else {
                printf("%u\n", request_results[i]->begin);
            }
            request_type[i] = ALLOC;

<<<<<<< HEAD
        } else  {
            RAM_director.free(request_results[-request]);
=======
        } else if (request_type[-request] == ALLOC) {
            if (request_results[-request]) {
                RAM_director.free(request_results[-request]);
            }
            request_type[i] = FREE;
            request_type[-request] = FREE;
>>>>>>> 43fbed1c50a1f6b132287e6587385d2664da5b8d
        }
    }

    return 0;
}

Memory_manager::Memory_manager(const size_t memory_size) {

    empty_blocks = new Custom_QuickHeap<Block*>(MAX_BLOCK_CNT, nullptr, cmp_blocks);

    Block* available_memory = new Block(EMPTY, memory_size, 1);

    memory_begin = new Block(FULL, 0, 0, available_memory, nullptr);
    memory_end   = new Block(FULL, 0, 0, nullptr, available_memory);

    available_memory->next_block = memory_end;
    available_memory->prev_block = memory_begin;

    empty_blocks->insert(available_memory);
}

Memory_manager::~Memory_manager() {

    Block* garbage = nullptr;
    Block* memory_list_it = memory_begin;

    do {
        garbage = memory_list_it;
        memory_list_it = memory_list_it->next_block;
        delete garbage;
    } while (memory_list_it);

    delete empty_blocks;
}

Memory_manager::Block::Block(const bool full_or_empty, const size_t block_size, const size_t block_begin,
                             Block *const next, Block *const prev) {

    is_empty = full_or_empty;
    is_valid = VALID;
    size = block_size;

    next_block = next;
    prev_block = prev;

    begin = block_begin;
}

Memory_manager::Block::~Block() {
    next_block = nullptr;
    prev_block = nullptr;
}

int Memory_manager::cmp_blocks(Block *const a, Block *const b) {

    enum {
        LESS    = -1,
        EQUAL   = 0,
        GREATER = 1
    };

    if (!a) {
        return (GREATER);
    } else if (!b) {
        return (LESS);
    }

    if (a->size > b->size) {
        return (LESS);
    } else if (a->size < b->size) {
        return (GREATER);
    }
    return (EQUAL);
}

void Memory_manager::remove_rubbish() {
    /*
     * @brief Removes not valid blocks from the top of heap
     */
    Block* rubbish = nullptr;

    while (empty_blocks->size() && empty_blocks->peakMin()->is_valid == NOT_VALID) {
        rubbish = empty_blocks->extractMin();
        delete rubbish;
    }
}

Memory_manager::Block* Memory_manager::allocate(size_t block_size) {
    /*
     * @brief Allocates a block of memory
     */
    remove_rubbish();

    if (!empty_blocks->size() || empty_blocks->peakMin()->size < block_size) {
        return (nullptr); // reject
    }

    Block* place_to_alloc = empty_blocks->extractMin();

    Block* allocated_block = new Block(FULL, block_size, place_to_alloc->begin,
                                       place_to_alloc->next_block, place_to_alloc->prev_block);

    Block* remainder = nullptr;

    if (place_to_alloc->size > block_size) {
        remainder = new Block(EMPTY, place_to_alloc->size - block_size, allocated_block->begin + allocated_block->size,
                              place_to_alloc->next_block, allocated_block);

        allocated_block->next_block = remainder;

        empty_blocks->insert(remainder);

    } else {
        remainder = allocated_block;
    }

    place_to_alloc->next_block->prev_block = remainder;
    place_to_alloc->prev_block->next_block = allocated_block;

    delete place_to_alloc;

    return (allocated_block);
}

void Memory_manager::free(Block *const block) {
    /*
     * @brief Clears the block of memory
     */

    if (!block) {
        return;
    }

    if (!block) {
        return;
    }

    size_t new_begin = block->begin;
    size_t new_size = block->size;

    Block* right_neighbour = block->next_block;
    Block* left_neighbour  = block->prev_block;

    if (right_neighbour->is_empty) {
        right_neighbour->is_valid = NOT_VALID;
        new_size += right_neighbour->size;
        right_neighbour = right_neighbour->next_block;
    }
    if (left_neighbour->is_empty) {
        left_neighbour->is_valid = NOT_VALID;
        new_size += left_neighbour->size;
        new_begin = left_neighbour->begin;
        left_neighbour = left_neighbour->prev_block;
    }

    delete block;

    Block* new_block = new Block(EMPTY, new_size, new_begin, right_neighbour, left_neighbour);

    right_neighbour->prev_block = new_block;
    left_neighbour->next_block = new_block;

    empty_blocks->insert(new_block);
}

template <typename elem_type>
Custom_QuickHeap<elem_type>::Custom_QuickHeap(const size_t max_capacity, const elem_type MAX_BORDER,
                                              int (*cmp)(const elem_type a, const elem_type b)) {
    /*
     * @brief constructor of an empty QuickHeap
     * @param max_capacity - maximal amount of elements in heap
     */
    capacity = max_capacity + 1;  // + 1 is for artificial "+inf" pivot
    current_size = 0;
    INF = MAX_BORDER;

    heap   = new std::vector<elem_type>(capacity);
    pivots = new std::stack<size_t>;

    pivots->push(0);
    heap_begin = 0;

    heap->at(0) = INF;

    cmp_elem = cmp;
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
void Custom_QuickHeap<elem_type>::dump() {
    /*
     * @brief dump heap information to console
     */
    printf("current size = %lu\n", current_size);
    printf("capacity = %lu\n", capacity);
    printf("heap:");
    for (size_t i = 0; i < capacity; ++i) {
        if (i == heap_begin) {
            printf("{");
        }
        printf(" %d", heap->at(i));
        if (i == (heap_begin + current_size) % capacity) {
            printf("}");
        }
    }
    printf("\n");

    std::stack<size_t> pivot_buffer;

    printf("stack:");
    while (!pivots->empty()) {
        printf(" %lu", pivots->top());
        pivot_buffer.push(pivots->top());
        pivots->pop();
    }
    while (!pivot_buffer.empty()) {
        pivots->push(pivot_buffer.top());
        pivot_buffer.pop();
    }
    printf("\n");
}

template <typename elem_type>
size_t Custom_QuickHeap<elem_type>::size() {
    /*
     * @brief a wrap for current_size variable
     * @return current size
     */
    return (current_size);
}

template <typename elem_type>
void Custom_QuickHeap<elem_type>::insert(const elem_type& element) {
    /*
     * @brief inserts element to the QuickHeap
     */
    if (current_size == capacity - 1) {
        throw std::overflow_error("QuickHeap overflow");
    } else if (cmp_elem(element, INF) > 0) {
        throw std::invalid_argument("Inserting element bigger than +inf for current QuickHeap");
    }

    std::stack<size_t> pivot_buffer;
    size_t pivot_index = pivots->top();

    while (cmp_elem(element, heap->at(pivot_index)) > 0) {
        pivot_buffer.push(pivot_index);
        pivots->pop();
        pivot_index = pivots->top();
    }

    elem_type moving_element = element;

    do {
        pivots->pop();

        std::swap(moving_element, heap->at((pivot_index + 1) % capacity));
        std::swap(heap->at((pivot_index + 1) % capacity), heap->at(pivot_index));

        if (!pivots->empty() && pivots->top() == (pivot_index + 1) % capacity) {
            std::swap(moving_element, heap->at((pivot_index + 1) % capacity));
        }

        pivot_buffer.push((pivot_index + 1) % capacity);
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
     * @return min heap element
     */
    if (current_size == 0) {
        throw std::out_of_range("getting Min in empty QuickHeap");
    }

    incremental_Qsort(*heap, heap_begin, *pivots);

    return (heap->at(heap_begin));
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::extractMin() {
    /*
     * @brief gets minimum in heap and erases it
     * @return min heap element
     */
    if (current_size == 0) {
        throw std::out_of_range("extracting Min in empty QuickHeap");
    }

    elem_type min_elem = incremental_Qsort(*heap, heap_begin, *pivots);

    heap_begin = (heap_begin + 1) % capacity;
    pivots->pop();

    --current_size;

    return (min_elem);
}

template <typename elem_type>
int Custom_QuickHeap<elem_type>::default_comparator(const elem_type a, const elem_type b) {
    enum {
        LESS    = -1,
        EQUAL   = 0,
        GREATER = 1
    };

    if (a < b) {
        return (LESS);
    } else if (a == b) {
        return (EQUAL);
    }
    return (GREATER);
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::incremental_Qsort(std::vector<elem_type>& arr, const size_t arr_begin,
                                                         std::stack<size_t>& pivot_stack) {
    /*
     * @brief an implementation of IncrementalQuickSort
     * @return min element in array
     */
    if (arr_begin == pivot_stack.top()) {
        return (arr[arr_begin]);
    }

    elem_type pivot = pick_pivot(arr, arr_begin, pivot_stack.top());
    size_t pivot_pos = do_partition(arr, pivot, arr_begin, pivot_stack.top());

    pivot_stack.push(pivot_pos);

    return (incremental_Qsort(arr, arr_begin, pivot_stack));
}

template <typename elem_type>
size_t Custom_QuickHeap<elem_type>::do_partition(std::vector<elem_type>& arr, const elem_type pivot,
                                                 const size_t arr_begin, const size_t arr_end) {
    /*
     * @brief classical partition on circular array
     * divides array into 3 groups: "less than pivot", "equal to pivot", "greater than pivot"
     * @return index of the first pivot occurrence
     */
    size_t less_idx    = arr_begin;
    size_t equal_idx   = arr_begin;
    size_t greater_idx = arr_begin;

    elem_type temp_elem = 0;

    for (; greater_idx != arr_end; greater_idx = (greater_idx + 1) % arr.size()) {

        if (cmp_elem(arr[greater_idx], pivot) == 0) {

            std::swap(arr[equal_idx], arr[greater_idx]);
            equal_idx = (equal_idx + 1) % arr.size();

        } else if (cmp_elem(arr[greater_idx], pivot) < 0) {

            temp_elem = arr[greater_idx];
            arr[greater_idx] = arr[(equal_idx + 1) % arr.size()];
            arr[(equal_idx + 1) % arr.size()] = arr[equal_idx];
            arr[equal_idx] = arr[(less_idx + 1) % arr.size()];
            arr[(less_idx + 1) % arr.size()] = arr[less_idx];
            arr[less_idx] = temp_elem;

            equal_idx = (equal_idx + 1) % arr.size();
            less_idx = (less_idx + 1) % arr.size();
        }
    }

    return (less_idx);
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::pick_pivot(const std::vector<elem_type>& arr,
                                                  const size_t arr_begin, const size_t arr_end) {
    /*
     * @brief Median of medians algorithm in circular array
     * @return selected median of medians (optimal pivot)
     */
    const size_t CHUNK_SIZE = 5;
    std::vector<elem_type> chunk(CHUNK_SIZE);

    size_t section_size = (arr_end + arr.size() - arr_begin) % arr.size();

    if (section_size <= CHUNK_SIZE) {
        chunk.resize(section_size);

        for (size_t i = 0; i < chunk.size(); ++i) {
            chunk[i] = arr[(arr_begin + i) % arr.size()];
        }

        return (insertion_stat(chunk, chunk.size() / 2, 0, 0));
    }

    std::vector<elem_type> medians((section_size + CHUNK_SIZE - 1) / CHUNK_SIZE);
    size_t chunk_it = 0;

    for (size_t i = 0; i < medians.size(); ++i) {

        chunk_it = 0;

        for (size_t j = (arr_begin + i * CHUNK_SIZE) % arr.size();
             j != (arr_begin + i * CHUNK_SIZE + CHUNK_SIZE) % arr.size() && j != arr_end;
             j = (j + 1) % arr.size(), ++chunk_it) {

            chunk[chunk_it] = arr[j];
        }
        if (chunk_it != CHUNK_SIZE) {
            chunk.resize(chunk_it);
        }
        medians[i] = insertion_stat(chunk, chunk.size() / 2, 0, 0);
    }

    elem_type median_of_medians = quickselect_stat(medians, medians.size() / 2, 0, 0);

    return (median_of_medians);
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::quickselect_stat(std::vector<elem_type> &arr, const size_t k,
                                                        const size_t arr_begin, const size_t arr_end) {
    /*
     * @brief quickselect algorithm in circular array
     * @return array k-th statistics
     */
    const size_t SIZE_FOR_INSERTION_SORT = 20;

    if ((arr_end + arr.size() - arr_begin) % arr.size() <= SIZE_FOR_INSERTION_SORT) {
        return (insertion_stat(arr, k, arr_begin, arr_end));
    }

    elem_type pivot  = pick_pivot(arr, arr_begin, arr_end);
    size_t pivot_pos = do_partition(arr, pivot, arr_begin, arr_end);

    if (pivot_pos == (arr_begin + k) % arr.size()) {
        return (arr[pivot_pos]);
    } else if (pivot_pos < k) {
        return (quickselect_stat(arr, k - pivot_pos, (pivot_pos + 1) % arr.size(), arr_end));
    }
    return (quickselect_stat(arr, k, arr_begin, pivot_pos));
}

template <typename elem_type>
elem_type Custom_QuickHeap<elem_type>::insertion_stat(std::vector<elem_type>& arr, const size_t k,
                                                      const size_t arr_begin, const size_t arr_end) {
    /*
     * @brief insertion sort in circular array
     * @return array k-th statistics
     */
    for (size_t i = (arr_begin + 1) % arr.size(); i != arr_end; i = (i + 1) % arr.size()) {
        for (size_t j = i; j != arr_begin && cmp_elem(arr[(j == 0 ? arr.size() - 1 : j - 1)], arr[j]) > 0; j = (j == 0 ? arr.size() - 1 : j - 1)) {
            std::swap(arr[(j == 0 ? arr.size() - 1 : j - 1)], arr[j]);
        }
    }

    return (arr[(arr_begin + k) % arr.size()]);
}




























