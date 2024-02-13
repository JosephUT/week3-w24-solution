#include <thread>

#include <socket/server_socket.hpp>
#include <socket/message_socket/connection_message_socket.hpp>
#include <chat_socket.hpp>

int main() {
    ServerSocket server(AF_INET, "127.0.0.1", 13330, 1);
    auto connection = std::shared_ptr<ConnectionMessageSocket>();
    do {
        connection = server.acceptConnection<ConnectionMessageSocket>();
    } while (!connection);
    singleThreadedReceiveSend(connection);
}
