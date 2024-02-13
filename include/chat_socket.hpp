#pragma once

#include <iostream>
#include <memory>

#include <socket/message_socket/message_socket.hpp>

void singleThreadedSendReceive(const std::shared_ptr<MessageSocket> &socket);
void singleThreadedReceiveSend(const std::shared_ptr<MessageSocket> &socket);
void receiveAndPrint(const std::shared_ptr<MessageSocket> &socket);
void readAndSend(const std::shared_ptr<MessageSocket> &socket);
