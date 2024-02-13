#include <chat_socket.hpp>

void singleThreadedSendReceive(const std::shared_ptr<MessageSocket> &socket) {
    std::string message;
    while(true) {
        std::cout << "enter a message: ";
        std::getline(std::cin, message);
        socket->sendMessage(message);
        message = socket->receiveMessage();
        std::cout << "received: " << message << std::endl;
    }
}

void singleThreadedReceiveSend(const std::shared_ptr<MessageSocket> &socket) {
    std::string message;
    while(true){
        message = socket->receiveMessage();
        std::cout << "received: " << message << std::endl;
        std::cout << "enter a message: ";
        std::getline(std::cin, message);
        socket->sendMessage(message);
    }
}

void receiveAndPrint(const std::shared_ptr<MessageSocket> &socket) {
    while(true) {
        std::cout << socket->receiveMessage() << std::endl;
    }
}

void readAndSend(const std::shared_ptr<MessageSocket> &socket) {
    while(true) {
        std::string message;
        std::getline(std::cin, message);
        socket->sendMessage(message);
    }
}
