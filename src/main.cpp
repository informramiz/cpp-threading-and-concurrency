#include <iostream>
#include <thread>

void threadFunction() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Finished work in thread" << std::endl;
}

class Vehicle {
public:
    Vehicle(int id): id(id) {

    }
    //this function will be executed in thread and this is how you can access data inside a thread
    void operator()() {
        std::cout << "Vehicle #" << id << " object has been created" << std::endl;
    }

private:
    int id;
};

void testCallbackObject() {
    std::cout << "Hello concurrent world from main: Thread id = " << std::this_thread::get_id() << std::endl;
    unsigned int coresInThisMachine = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << coresInThisMachine << " cores." << std::endl;

    //create thread
    std::thread thread{ Vehicle(1) };
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished worked in main" << std::endl;

    //wait for thread to finish
    // thread.detach();
    thread.join();
}

int main() {
    
    testCallbackObject();
    return 0;
}