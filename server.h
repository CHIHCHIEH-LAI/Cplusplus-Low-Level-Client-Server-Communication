#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <unordered_map>
#include <netinet/in.h>
#include <unistd.h>

#include "thread_pool.h"

class Server {
public:
    Server(int port);
    void run(size_t num_threads);
    
private:
    int port;
    int server_socket;
    std::unordered_map<std::string, std::string> data_store;
    std::mutex data_mutex;
    
    void setup_socket(int port);
    void handle_client(int client_socket);
};

#endif // SERVER_H