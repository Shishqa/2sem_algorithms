#include <iostream>

int main() {

    // (੭ ͡° ͜ʖ ͡°)੭̸*✩⁺˚ mafth

    size_t height = 0;
    std::cin >> height;

    size_t width = 0;
    std::cin >> width;

    size_t longest_side = std::max(width, height);

    if (width < 2 || height < 2) {
        std::cout << width * height << std::endl;
    } else if (width == 2 || height == 2 ) {
        std::cout << (longest_side / 4 * 2 + std::min(longest_side % 4, static_cast<size_t>(2))) * 2 << std::endl;
    } else {
        std::cout << (width * height + 1) / 2 << std::endl;
    }

    return 0;
}
