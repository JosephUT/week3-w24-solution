#include <socket/socket.hpp>

Socket::Socket() {}

Socket::Socket(int file_descriptor) : file_descriptor_(file_descriptor) {}

Socket::~Socket() {}
