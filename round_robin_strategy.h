#ifndef ROUNDROBINSTRATEGY_H
#define ROUNDROBINSTRATEGY_H

#include <cstddef>
#include "load_balancer_strategy.h"

class RoundRobinStrategy : public LoadBalancerStrategy {
public:
    RoundRobinStrategy() : current_server(0) {}
    int select_server(const std::vector<int>& server_ports) override;

private:
    size_t current_server;
};

#endif // ROUNDROBINSTRATEGY_H