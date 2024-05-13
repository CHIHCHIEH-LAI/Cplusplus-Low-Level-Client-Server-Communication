#include "round_robin_strategy.h"

int RoundRobinStrategy::select_server(const std::vector<int>& server_ports) {
    int port = server_ports[current_server];
    current_server = (current_server + 1) % server_ports.size();
    return port;
}