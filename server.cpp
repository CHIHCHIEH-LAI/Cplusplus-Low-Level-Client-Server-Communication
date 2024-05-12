#include "server.h"

Server::Server(int port, size_t num_threads): num_threads(num_threads) {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    bind(server_socket, (sockaddr*)&server_address, sizeof(server_address));
    listen(server_socket, 5);
}

void Server::run() {
    ThreadPool thread_pool(num_threads);

    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        thread_pool.enqueue([this, client_socket] { handle_client(client_socket); });
    }
    close(server_socket);
}

void Server::handle_client(int client_socket) {
    char buffer[1024];
    while (true) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }
        buffer[bytes_received] = '\0';
        std::string command(buffer);

        std::string response;
        {
            std::lock_guard<std::mutex> lock(data_mutex);
            if (command.substr(0, 3) == "put") {
                size_t pos = command.find(" ");
                std::string key = command.substr(4, pos - 4);
                std::string value = command.substr(pos + 1);
                data_store[key] = value;
                response = "OK";
            } else if (command.substr(0, 3) == "get") {
                std::string key = command.substr(4);
                response = data_store[key];
            } else {
                response = "Unknown command";
            }
        }
        send(client_socket, response.c_str(), response.size(), 0);
    }
    close(client_socket);
}

int main() {
    Server server(8080, 4);
    server.run();
    return 0;
}