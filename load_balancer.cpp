#include "load_balancer.h"

LoadBalancer::LoadBalancer(int port, const std::vector<int>& server_ports, std::unique_ptr<LoadBalancerStrategy> strategy)
    : server_ports(server_ports), strategy(std::move(strategy)) {
    balancer_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in balancer_address;
    balancer_address.sin_family = AF_INET;
    balancer_address.sin_addr.s_addr = INADDR_ANY;
    balancer_address.sin_port = htons(port);

    bind(balancer_socket, (sockaddr*)&balancer_address, sizeof(balancer_address));
    listen(balancer_socket, 5);

    std::cout << "Load Balancer started on port " << port << std::endl;
}

void LoadBalancer::run() {
    while (true) {
        int client_socket = accept(balancer_socket, nullptr, nullptr);
        handle_client(client_socket);
        std::cout << "Accepted new client connection." << std::endl;
    }
    close(balancer_socket);
    std::cout << "Load Balancer stopped." << std::endl;
}

void LoadBalancer::handle_client(int client_socket) {
    int server_socket = get_server_socket();
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_socket);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    int server_connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(server_connection, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Failed to connect to server instance on port " << server_socket << std::endl;
        close(client_socket);
        return;
    }

    char buffer[1024];
    int bytes_received;
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        send(server_connection, buffer, bytes_received, 0);
        bytes_received = recv(server_connection, buffer, sizeof(buffer), 0);
        send(client_socket, buffer, bytes_received, 0);
    }
    close(client_socket);
    close(server_connection);
}

int LoadBalancer::get_server_socket() {
    return strategy->select_server(server_ports);
}