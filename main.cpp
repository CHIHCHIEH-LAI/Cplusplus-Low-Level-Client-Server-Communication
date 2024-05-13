#include <vector>

#include "load_balancer.h"
#include "load_balancer_strategy.h"
#include "round_robin_strategy.h"
#include "server.h"

int main() {
    std::vector<int> server_ports = {8080, 8081, 8082};

    // Choose the load balancing strategy
    std::unique_ptr<LoadBalancerStrategy> strategy = std::make_unique<RoundRobinStrategy>();

    LoadBalancer load_balancer(8080, server_ports, std::move(strategy));
    load_balancer.run();
    return 0;
}