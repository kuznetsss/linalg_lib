#include <iostream>

void testData();
void testMatrix();
void testInversed();

int main()
{
    std::cout << "Tests started" << std::endl;
    try {
        testData();
        testMatrix();
        testInversed();
    } catch(std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    std::cout << "Tests done" << std::endl;
    return 0;
}
