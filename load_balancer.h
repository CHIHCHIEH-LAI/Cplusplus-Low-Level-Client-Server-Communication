#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
#include <iostream>

#include "load_balancer_strategy.h"

class LoadBalancer {
public:
    LoadBalancer(int port, const std::vector<int>& server_ports, std::unique_ptr<LoadBalancerStrategy> strategy);
    void run();

private:
    int balancer_socket;
    std::vector<int> server_ports;
    std::unique_ptr<LoadBalancerStrategy> strategy;

    void handle_client(int client_socket);
    int get_server_socket();
};

#endif // LOADBALANCER_H