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

void testLambdas() {
    int id = 0;

    id++;
    //lambda which can't access anything outside it, for example it can't access `id` variable
    auto f1 = []() {
        std::cout << "Lambda f1 called" << std::endl;
    };

    ++id;
    //lambda which does capture `id` variable but can't mutate/update it
    auto f2 = [id]() { std::cout << "Lambda f2 called with id: " << id << std::endl; };

    //lambda which not only capture `id` but can also mutate a COPY of it.
    auto f3 = [id]() mutable { std::cout << "Lambda f3 called with id: " << ++id << std::endl; };

    //lambda which not only capture `id` by reference but can also mutate it directly.
    auto f4 = [&id]() mutable { std::cout << "Lambda f4 called with id: " << ++id << std::endl; };

    //as lambdas are functions so we can call them
    f1();
    f2();
    f3();
    std::cout << "Final value of id is before f4(): " << id << std::endl;
    f4();
    std::cout << "Final value of id is after f4(): " << id << std::endl;
}

int main() {
    
    testLambdas();
    // testCallbackObject();
    return 0;
}