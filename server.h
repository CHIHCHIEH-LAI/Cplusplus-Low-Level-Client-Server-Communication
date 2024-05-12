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
    Server(int port, size_t num_threads);
    void run();
    
private:
    int server_socket;
    int num_threads;
    std::unordered_map<std::string, std::string> data_store;
    std::mutex data_mutex;
    
    void handle_client(int client_socket);
};