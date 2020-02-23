#include <iostream>
#include <utility>
#include <vector>

template <typename key_t, typename val_t>
class Custom_QuickHeap {

public:
    void insert(const key_t& key, const val_t& value);
    std::pair<key_t, val_t> getMin();
    std::pair<key_t, val_t> extractMin();

    void size();
    void dump();

private:

    std::vector<std::pair<key_t, val_t>>;


};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
