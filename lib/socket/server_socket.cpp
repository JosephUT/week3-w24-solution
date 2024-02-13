#include <socket/server_socket.hpp>

ServerSocket::ServerSocket(int const domain, int const listen_backlog) {
    auto results = ServerSocket::getAddressInfo(domain);
    ServerSocket(domain, results.first, results.second, listen_backlog);
}

ServerSocket::ServerSocket(const int domain, const std::string& address, const int port, const int listen_backlog) {
  const char* host_address = address.c_str();

  // Set up server socket address.
  server_address_.sin_family = domain;
  server_address_.sin_port = htons(port);
  if (inet_aton(host_address, &server_address_.sin_addr) == 0) {
    throw SocketErrnoException("Failed to convert address.");
  }

  // Create server socket, set it to be non-blocking, bind it to its address, and listen for connections.
  file_descriptor_ = socket(domain, SOCK_STREAM, 0);
  is_open_ = true;
  int flags = fcntl(file_descriptor_, F_GETFL);
  if (flags == -1) throw SocketException("Failed to get flags.");
  if (fcntl(file_descriptor_, F_SETFL, flags | O_NONBLOCK) == -1) {
    throw SocketErrnoException("Failed to set socket nonblocking.");
  }
  int option = 1; // Nonzero value to enable boolean option.
  if (setsockopt(file_descriptor_, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1) {
    throw SocketErrnoException("Failed to set socket to reuse address.");
  }
  if (bind(file_descriptor_, reinterpret_cast<struct sockaddr*>(&server_address_), sizeof(server_address_))) {
    throw SocketErrnoException("Failed to bind to port.");
  }
  if (listen(file_descriptor_, listen_backlog)) {
    throw SocketErrnoException("Failed to listen..");
  }
}

ServerSocket::~ServerSocket() {
  close();
}

template <class ConnectionSocket>
std::shared_ptr<ConnectionSocket> ServerSocket::acceptConnection() {
  if (!is_open_) throw SocketException("Cannot accept on close socket.");
  sockaddr_in client_address = server_address_; // Must assign to avoid issues with accept
  socklen_t client_address_size = sizeof(client_address);
  int connection_file_descriptor =
      accept(file_descriptor_, reinterpret_cast<struct sockaddr*>(&client_address), &client_address_size);
  if (connection_file_descriptor == -1) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      // Return nullptr if accept fails because backlog is empty.
      return nullptr;
    }
    // Throw for other errors.
    throw SocketErrnoException("Failed to accept connection.");
  }
  // Handle appropriate return paths at compile time.
  if constexpr (std::is_same_v<ConnectionSocket, ConnectionMessageSocket>) {
    auto connection = std::make_shared<ConnectionMessageSocket>(connection_file_descriptor);
    return connection;
  } else {
    return std::make_shared<ConnectionSocket>(connection_file_descriptor);
  }
}

void ServerSocket::close() {
  // Cannot throw exception in destructor. Assume close is executed without error.
  if (is_open_) {
    int result = ::close(file_descriptor_);
    is_open_ = false;
  }
}

std::pair<std::string, int> ServerSocket::getAddressInfo(int domain) {
    char const* hostname = "127.0.0.1";
    char const* port = "0";

    struct addrinfo* res = nullptr;
    struct addrinfo address_info{0};

    address_info.ai_family = AF_UNSPEC;
    address_info.ai_socktype = SOCK_STREAM;
    address_info.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(hostname, port, &address_info, &res);
    if (status != 0) {
        throw SocketErrnoException("Error fetching host and port information");
    }

    auto ipv4 = reinterpret_cast<struct sockaddr_in*>(res->ai_addr);
    auto results = std::make_pair<std::string, int>(std::string(inet_ntoa(ipv4->sin_addr)), ntohs(ipv4->sin_port));
    freeaddrinfo(res);
    return results;
}

// Explicit instantiation to work with MessageSockets.
template std::shared_ptr<ConnectionMessageSocket> ServerSocket::acceptConnection<
  ConnectionMessageSocket>();
