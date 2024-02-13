#include <iostream>
#include <fstream>
#include <memory>

#include <socket/message_socket/client_message_socket.hpp>

void sendFromFile(std::string file_path, std::shared_ptr<ClientMessageSocket> client);