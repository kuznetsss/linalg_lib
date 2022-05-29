#include <iostream>

void testData();

int main()
{
    std::cout << "Tests started" << std::endl;
    try {
        testData();
    } catch(std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    std::cout << "Tests done" << std::endl;
    return 0;
}
