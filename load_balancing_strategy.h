#ifndef LOADBALANCINGSTRATEGY_H
#define LOADBALANCINGSTRATEGY_H

#include <vector>

class LoadBalancingStrategy {
public:
    virtual int select_server(const std::vector<int>& server_ports) = 0;
    virtual ~LoadBalancingStrategy() = default;
};

#endif // LOADBALANCINGSTRATEGY_H