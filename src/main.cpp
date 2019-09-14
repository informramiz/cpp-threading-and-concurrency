#include <iostream>
#include <thread>

int main() {
    std::cout << "Hello concurrent world from main: Thread id = " << std::this_thread::get_id() << std::endl;
    unsigned int coresInThisMachine = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << coresInThisMachine << " cores." << std::endl;
    return 0;
}