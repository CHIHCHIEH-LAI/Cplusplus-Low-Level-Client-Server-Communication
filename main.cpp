#include <vector>
#include <thread>

#include "load_balancer.h"
#include "load_balancer_strategy.h"
#include "round_robin_strategy.h"
#include "server.h"

void run_server(int port) {
    Server server(port);
    server.run(5);
}

void run_balancer(int port, std::vector<int> &server_ports) {

    // Choose the load balancing strategy
    std::unique_ptr<LoadBalancerStrategy> strategy = std::make_unique<RoundRobinStrategy>();

    LoadBalancer load_balancer(port, server_ports, std::move(strategy));
    load_balancer.run(5);
}

int main() {
    std::vector<int> server_ports = {8081, 8082, 8083, 8084, 8085};
    std::vector<std::thread> server_threads;

    for (int port : server_ports) {
        server_threads.push_back(std::thread(run_server, port));
    }

    std::thread balancer_thread(run_balancer, 8080, std::ref(server_ports));

    for (std::thread &thread : server_threads) {
        thread.join();
    }

    balancer_thread.join();
}