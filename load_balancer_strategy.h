#ifndef LOADBALANCERSTRATEGY_H
#define LOADBALANCERSTRATEGY_H

#include <vector>

class LoadBalancerStrategy {
public:
    virtual int select_server(const std::vector<int>& server_ports) = 0;
    virtual ~LoadBalancerStrategy() = default;
};

#endif // LOADBALANCERSTRATEGY_H