#include <multi_send_socket.hpp>

void sendFromFile(std::string file_path, std::shared_ptr<ClientMessageSocket> client) {
    std::fstream file_input(file_path);
    std::string input;
    while (file_input >> input) {
        client->sendMessage(input);
    }
    file_input.close();
}