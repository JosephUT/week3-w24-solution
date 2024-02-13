#include <memory>
#include <thread>

#include <socket/message_socket/client_message_socket.hpp>
#include <chat_socket.hpp>

int main() {
    auto client = std::make_shared<ClientMessageSocket>(AF_INET, "127.0.0.1", 13330);
    client->connect();
    singleThreadedSendReceive(client);
}
