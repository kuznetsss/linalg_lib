#include <iostream>

void testData();
void testMatrix();

int main()
{
    std::cout << "Tests started" << std::endl;
    try {
        testData();
        testMatrix();
    } catch(std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    std::cout << "Tests done" << std::endl;
    return 0;
}
