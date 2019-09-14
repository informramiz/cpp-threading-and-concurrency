#include <iostream>
#include <thread>

void threadFunction() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Finished work in thread" << std::endl;
}

class Vehicle {
public:
    void operator()() {
        std::cout << "Vehicle object has been created" << std::endl;
    }
};

int main() {
    std::cout << "Hello concurrent world from main: Thread id = " << std::this_thread::get_id() << std::endl;
    unsigned int coresInThisMachine = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << coresInThisMachine << " cores." << std::endl;

    //create thread
    Vehicle vehicle;
    std::thread thread(vehicle);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished worked in main" << std::endl;

    //wait for thread to finish
    // thread.detach();
    thread.join();
    return 0;
}