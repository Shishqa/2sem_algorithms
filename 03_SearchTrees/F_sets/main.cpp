#include <iostream>
#include <set>
#include <map>

template <typename elem_t>
class MegaSet {

public:

    void add(const elem_t& element, const int& set_number);
    void del(const elem_t& element, const int& set_number);
    void clr(const int& set_number);
    void list_set(const int& set_number);
    void list_set_of(const elem_t& element);

private:

    std::map<int, std::set<elem_t>> elem_by_set;
    std::map<elem_t, std::set<int>> set_by_elem;
};

int main() {



}

template <typename elem_t>
void MegaSet<elem_t>::add(const elem_t &element, const int &set_number) {

    elem_by_set[set_number].insert(element);
    set_by_elem[element].insert(set_number);
}

template <typename elem_t>
void MegaSet<elem_t>::del(const elem_t &element, const int &set_number) {

    elem_by_set[set_number].erase(element);
    set_by_elem[element].erase(set_number);
}

template <typename elem_t>
void MegaSet<elem_t>::clr(const int &set_number) {

    elem_by_set[set_number].clear();
}

template <typename elem_t>
void MegaSet<elem_t>::list_set(const int &set_number) {

    set[set_number].erase(element);
}
