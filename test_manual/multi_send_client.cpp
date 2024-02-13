#include <thread>

#include <multi_send_socket.hpp>

int main() {
    auto client = std::make_shared<ClientMessageSocket>(AF_INET, "127.0.0.1", 13330);
    client->connect();
    auto thread1 = std::thread(&sendFromFile, "../data/thread1_data.txt", client);
    auto thread2 = std::thread(&sendFromFile, "../data/thread2_data.txt", client);
    auto thread3 = std::thread(&sendFromFile, "../data/thread3_data.txt", client);
    thread1.join();
    thread2.join();
    thread3.join();
}