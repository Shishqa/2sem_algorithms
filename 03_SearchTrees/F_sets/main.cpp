#include <iostream>
#include <set>
#include <map>
#include <vector>

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

    MegaSet<unsigned long long> mega_set;

    unsigned long long max_number = 0;
    std::cin >> max_number;

    size_t set_count = 0;
    std::cin >> set_count;

    size_t request_num = 0;
    std::cin >> request_num;

    std::string curr_cmd = "";
    size_t set_arg = 0;
    unsigned long long elem_arg = 0;

    for (size_t i = 0; i < request_num; ++i) {

        std::cin >> curr_cmd;

        if (curr_cmd == "ADD") {

            std::cin >> elem_arg >> set_arg;

            mega_set.add(elem_arg, set_arg);

        } else if (curr_cmd == "DELETE") {

            std::cin >> elem_arg >> set_arg;

            mega_set.del(elem_arg, set_arg);

        } else if (curr_cmd == "CLEAR") {

            std::cin >> set_arg;

            mega_set.clr(set_arg);

        } else if (curr_cmd == "LISTSET") {

            std::cin >> set_arg;

            mega_set.list_set(set_arg);

        } else {

            std::cin >> elem_arg;

            mega_set.list_set_of(elem_arg);

        }

    }
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

    if (elem_by_set[set_number].empty()) {

        std::cout << -1 << std::endl;
        return;

    }

    for (auto elem : elem_by_set[set_number]) {

        std::cout << elem << " ";

    }
    std::cout << std::endl;

}

template <typename elem_t>
void MegaSet<elem_t>::list_set_of(const elem_t &element) {

    if (set_by_elem[element].empty()) {

        std::cout << -1 << std::endl;
        return;

    }

    bool printed_smth = false;

    for (auto set : set_by_elem[element]) {

        if (elem_by_set[set].count(element)) {

            std::cout << set << " ";
            printed_smth = true;

        }

    }

    std::cout << (printed_smth ? "" : "-1") << std::endl;

}
