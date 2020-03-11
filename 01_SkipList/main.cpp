#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#undef DEBUG

#ifdef DEBUG
#define LOG( code )  code
#else
#define LOG( code )  0;
#endif

class Custom_SkipList {

public:
    Custom_SkipList();
    ~Custom_SkipList();

    void insert(const int& key, const int& value);
    void remove(const int& key);
    int  extract_min();

    void dump();

    size_t get_size();

private:

    const size_t MAX_HEIGHT = 30;
    const size_t MAX_SIZE   = 1 << MAX_HEIGHT;

    size_t size;
    size_t level;

    struct Tower {

        const int NIL_KEY   = __INT_MAX__;
        const int NIL_VALUE = -1;

        int key;
        int value;
        std::vector<Tower*> next;

        explicit Tower(size_t t_height, Tower* arr_fill = nullptr);
        ~Tower();
    };

    Tower* head_sentinel;
    Tower* tail_sentinel;

    std::vector<Custom_SkipList::Tower*>* lookup(const int& search_key);

    size_t rand_height();
};

int main() {

    std::srand(std::time(nullptr));

    const size_t n_colors = 3;
    const size_t n_it_colors = 2;

    size_t shirt_count = 0;
    scanf("%lu", &shirt_count);

    std::vector<int> shirt_cost(shirt_count);
    for (size_t i = 0; i < shirt_count; ++i) {
        scanf("%d", &shirt_cost[i]);
    }

    std::vector<std::vector<bool>> already_added(n_colors, std::vector(shirt_count, false));
    size_t curr_color = 0;

    std::vector<Custom_SkipList> shirts(n_colors);

    LOG( printf("created lists\n") );
    LOG( printf("adding shirts\n"));

    for (size_t k = 0; k < n_it_colors; ++k) {
        for (size_t i = 0; i < shirt_count; ++i) {

            scanf("%lu", &curr_color);

            if(!already_added[curr_color - 1][i]) {
                already_added[curr_color - 1][i] = true;
                shirts[curr_color - 1].insert(shirt_cost[i], shirt_cost[i]);
            }
        }
    }
    LOG( printf("added shirts\n") );

    size_t customers_count = 0;
    scanf("%lu", &customers_count);

    std::vector<int> answer(customers_count);

    size_t favourite_color = 0;

    LOG( printf("customers came\n") );

    int reasonable_price = 0;

    for (size_t i = 0; i < customers_count; ++i) {

        scanf("%lu", &favourite_color);

        if (!shirts[favourite_color - 1].get_size()) {
            reasonable_price = -1;
        } else {
            reasonable_price = shirts[favourite_color - 1].extract_min();
            for (size_t j = 0; j < n_colors; ++j) {
                shirts[j].remove(reasonable_price);
            }
        }

        answer[i] = reasonable_price;
    }

    for (size_t i = 0; i < customers_count; ++i) {
        printf("%d ", answer[i]);
    }

    printf("\n");

    return 0;
}

Custom_SkipList::Custom_SkipList() {

    LOG( printf("list%p::constructor::->\n", this) );

    size  = 0;
    level = 1;

    tail_sentinel = new Tower(MAX_HEIGHT, nullptr);
    head_sentinel = new Tower(MAX_HEIGHT, tail_sentinel);

    LOG( printf("list%p::constructor::done\n", this) );
}

Custom_SkipList::~Custom_SkipList() {

    LOG( printf("list%p::destructor::->\n", this) );

    Tower* next = nullptr;

    for (Tower* garbage = head_sentinel; garbage != nullptr; garbage = next) {
        next = garbage->next[1];
        garbage->next.clear();
        delete garbage;
    }

    LOG( printf("list%p::destructor::done\n", this) );
}

Custom_SkipList::Tower::Tower(const size_t t_height, Tower* arr_fill) {

    LOG( printf("tower%p::constructor::->\n", this) );

    key   = Tower::NIL_KEY;
    value = Tower::NIL_VALUE;
    next.assign(t_height, arr_fill);

    LOG( printf("tower%p::constructor::done size = %d\n", this, next.size()) );
}

Custom_SkipList::Tower::~Tower() {

    LOG( printf("tower%p::destructor::->\n", this) );
    next.clear();
    LOG( printf("tower%p::destructor::done\n", this) );
}

void Custom_SkipList::dump() {

    LOG( printf("list%p::dump:\n", this) );

    for (size_t lvl = 1; lvl <= level; ++lvl) {
        for (Tower* curr_tower = head_sentinel; curr_tower != nullptr; curr_tower = curr_tower->next[lvl]) {
            LOG( printf ("%p(%d)[h=%lu] %s", curr_tower, curr_tower->key, curr_tower->next.size(),
                         curr_tower->next[0] ? "->" : "\n") );
        }
    }
}

std::vector<Custom_SkipList::Tower*>* Custom_SkipList::lookup(const int& search_key) {

    LOG( printf("list%p::lookup::->\n", this) );

    std::vector<Tower*>* update = new std::vector<Tower*>(MAX_HEIGHT);

    Tower* curr_tower = head_sentinel;

    for (size_t curr_lvl = level; curr_lvl >= 1; --curr_lvl) {
        while (curr_tower->next[curr_lvl]->key < search_key) {

            curr_tower = curr_tower->next[curr_lvl];
        }
        update->at(curr_lvl) = curr_tower;
    }

    LOG( printf("list%p::lookup::done key = %d\n", this, curr_tower->next[0]->key) );

    return (update);
}

size_t Custom_SkipList::rand_height() {

    int rand_value = std::rand() % (MAX_SIZE >> 1) + 1;
    size_t height = 0;

    while (rand_value) {
        ++height;
        rand_value /= 2;
    }

    LOG( printf("list%p::rnd_height::-> %d\n", this,
            std::min(MAX_HEIGHT + 1 - height, MAX_HEIGHT)) );

    return (std::min(MAX_HEIGHT + 1 - height, MAX_HEIGHT));
}

void Custom_SkipList::insert(const int& key, const int& value) {

    LOG( printf("list%p::insert::->\n", this) );

    std::vector<Tower*>* update = lookup(key);

    if (update->at(1)->next[1]->key == key) {
        update->at(1)->next[1]->value = value;
        delete update;
        return;
    }

    int new_tower_height = rand_height();

    if (new_tower_height - 1 > level) {
        for (size_t i = level + 1; i < new_tower_height; ++i) {
            update->at(i) = head_sentinel;
        }
        level = new_tower_height - 1;
    }

    Tower* new_tower = new Tower(new_tower_height);
    new_tower->key   = key;
    new_tower->value = value;

    LOG( printf("list%p::insert::inserted k%d v%d with height %lu\n",
            this, key, value, new_tower_height) );

    ++size;

    for (size_t i = 1; i < new_tower_height; ++i) {
        new_tower->next[i] = update->at(i)->next[i];
        update->at(i)->next[i] = new_tower;
    }

    LOG( printf("list%p::insert::updated\n", this) );

    update->clear();
    delete update;

    LOG( printf("list%p::insert::done curr_level = %lu\n", this, level) );
    LOG( dump() );
}

void Custom_SkipList::remove(const int& key) {

    std::vector<Tower*>* update = lookup(key);

    Tower* garbage = update->at(1)->next[1];

    if (garbage->key != key || garbage == tail_sentinel) {
        delete update;
        return;
    }

    for (int i = 1; i <= level; ++i) {
        if (update->at(i)->next[i] != garbage) {
            break;
        }
        update->at(i)->next[i] = garbage->next[i];
    }

    LOG( printf("list::remove::deleting k%d v%d with height %lu\n",
            garbage->key, garbage->value, garbage->next.size()) );

    delete garbage;

    LOG( printf("list::remove::deleted\n") );

    --size;

    update->clear();
    delete update;

    while (level > 1 && head_sentinel->next[level] == tail_sentinel) {
        --level;
    }

    LOG( printf("list::remove::done and updated lvl to %lu\n", level) );
    LOG( dump() );
}

int Custom_SkipList::extract_min() {

    const int min_value = head_sentinel->next[1]->value;
    const int min_key   = head_sentinel->next[1]->key;

    remove(min_key);

    return (min_value);
}

size_t Custom_SkipList::get_size() {
    return (size);
}

