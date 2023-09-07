#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <unistd.h>

// RAII synchronized message queue
template <typename T>
class MessageQueue {
private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void push(T value) {
        std::unique_lock<std::mutex> lock(mtx);
        queue.push(value);
        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !queue.empty(); });
        T value = queue.front();
        queue.pop();
        return value;
    }
};

void customer(MessageQueue<std::string>& orders, int id) {
    std::string order = "Food from customer " + std::to_string(id);
    std::cout << "Customer " << id << " placed an order.\n";
    orders.push(order);
}

void cook(MessageQueue<std::string>& orders, MessageQueue<std::string>& deliveries, int id) {
    for (;;) {
        std::string order = orders.pop();
        std::cout << "Cook " << id << " is preparing " << order << ".\n";
        std::string delivery = "Prepared " + order;
        sleep(1);
        deliveries.push(delivery);
    }
}

void waiter(MessageQueue<std::string>& deliveries, int id) {
    for (;;) {
      std::string delivery = deliveries.pop();
      std::cout << "Waiter " << id << " is delivering " << delivery << ".\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <num_customers> <num_cooks> <num_waiters>\n";
        return 1;
    }

    int num_customers = std::atoi(argv[1]);
    int num_cooks = std::atoi(argv[2]);
    int num_waiters = std::atoi(argv[3]);


    std::thread customers[num_customers];
    std::thread cooks[num_cooks];
    std::thread waiters[num_waiters];

    // Create customers, cooks, and waiters
    for (int i = 0; i < num_customers; ++i) {
        customers[i] = std::thread(customer, std::ref(orders), i);
    }
    for (int i = 0; i < num_cooks; ++i) {
        cooks[i] = std::thread(cook, std::ref(orders), std::ref(deliveries), i);
    }
    for (int i = 0; i < num_waiters; ++i) {
        waiters[i] = std::thread(waiter, std::ref(deliveries), i);
    }

    // Wait for all threads to complete
    for (int i = 0; i < num_customers; ++i) {
        customers[i].join();
    }
    for (int i = 0; i < num_cooks; ++i) {
        cooks[i].join();
    }
    for (int i = 0; i < num_waiters; ++i) {
        waiters[i].join();
    }

    return 0;
}
