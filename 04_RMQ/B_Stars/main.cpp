#include <iostream>

class FenwickTree_3D {

public:

    FenwickTree_3D() = delete;

    explicit FenwickTree_3D(const uint16_t& size);

    ~FenwickTree_3D();

    int64_t sum(const uint16_t& x_low, const uint16_t& x_high,
                const uint16_t& y_low, const uint16_t& y_high,
                const uint16_t& z_low, const uint16_t& z_high);

    int64_t prefix_sum(const uint16_t& x,
                       const uint16_t& y,
                       const uint16_t& z);

    void add(const int64_t& val,
             const uint16_t& x,
             const uint16_t& y,
             const uint16_t& z);

private:

    const uint16_t size;
    int64_t*** tree;

};



int main() {

    uint16_t sky_size = 0;
    std::cin >> sky_size;

    FenwickTree_3D sky(sky_size);

    uint16_t x_low  = 0;
    uint16_t x_high = 0;
    uint16_t y_low  = 0;
    uint16_t y_high = 0;
    uint16_t z_low  = 0;
    uint16_t z_high = 0;
    int64_t  star_count_delta = 0;

    enum {
        UPDATE = 1,
        ASK    = 2,
        STOP   = 3
    };

    uint16_t query_code = 0;

    while (query_code != STOP) {

        std::cin >> query_code;

        if (query_code == UPDATE) {

            std::cin >> x_low >> y_low >> z_low >> star_count_delta;
            sky.add(star_count_delta, x_low, y_low, z_low);

        } else if (query_code == ASK) {

            std::cin >> x_low >> y_low >> z_low >> x_high >> y_high >> z_high;
            std::cout << sky.sum(x_low, x_high, y_low, y_high, z_low, z_high) << std::endl;

        }
    }

    return 0;
}

void FenwickTree_3D::add(const int64_t& val, const uint16_t& x, const uint16_t& y, const uint16_t& z) {

    for (int16_t x_i = x; x_i < size; x_i |= x_i + 1) {
        for (int16_t y_i = y; y_i < size; y_i |= y_i + 1) {
            for (int16_t z_i = z; z_i < size; z_i |= z_i + 1) {

                tree[x_i][y_i][z_i] += val;

            }
        }
    }
}

int64_t FenwickTree_3D::sum(const uint16_t& x_low, const uint16_t& x_high,
                            const uint16_t& y_low, const uint16_t& y_high,
                            const uint16_t& z_low, const uint16_t& z_high) {

    return prefix_sum(x_high, y_high, z_high) +
           - (x_low ? prefix_sum(x_low - 1, y_high, z_high) : 0) +
           - (y_low ? prefix_sum(x_high, y_low - 1, z_high) : 0) +
           - (z_low ? prefix_sum(x_high, y_high, z_low - 1) : 0) +
           + (x_low && y_low ? prefix_sum(x_low - 1, y_low - 1, z_high) : 0) +
           + (x_low && z_low ? prefix_sum(x_low - 1, y_high, z_low - 1) : 0) +
           + (y_low && z_low ? prefix_sum(x_high, y_low - 1, z_low - 1) : 0) +
           - (x_low && y_low && z_low ? prefix_sum(x_low - 1, y_low - 1, z_low - 1) : 0);
}

int64_t FenwickTree_3D::prefix_sum(const uint16_t& x, const uint16_t& y, const uint16_t& z) {

    int64_t sum = 0;

    for (int16_t x_i = x; x_i >= 0; x_i = (x_i & (x_i + 1)) - 1) {
        for (int16_t y_i = y; y_i >= 0; y_i = (y_i & (y_i + 1)) - 1) {
            for (int16_t z_i = z; z_i >= 0; z_i = (z_i & (z_i + 1)) - 1) {

                sum += tree[x_i][y_i][z_i];

            }
        }
    }

    return sum;
}

FenwickTree_3D::FenwickTree_3D(const uint16_t& size) :
        size(size) {

    tree = new int64_t** [size];

    for (size_t x_i = 0; x_i < size; ++x_i) {

        tree[x_i] = new int64_t* [size];

        for (size_t y_i = 0; y_i < size; ++y_i) {

            tree[x_i][y_i] = new int64_t[size];

            for (size_t z_i = 0; z_i < size; ++z_i) {

                tree[x_i][y_i][z_i] = 0;

            }
        }
    }
}

FenwickTree_3D::~FenwickTree_3D() {

    for (size_t x_i = 0; x_i < size; ++x_i) {

        for (size_t y_i = 0; y_i < size; ++y_i) {

            delete[] tree[x_i][y_i];
        }

        delete[] tree[x_i];
    }

    delete[] tree;
}