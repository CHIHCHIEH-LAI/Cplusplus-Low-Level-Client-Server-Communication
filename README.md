# Low-Level Client-Server Communication with Load Balancing

This is a multi-threaded server application written in C++. It uses a thread pool to handle multiple client connections concurrently and a load balancer to distribute the load among multiple servers.

## Features

- Multi-threaded handling of client connections
- Load balancing of client requests across multiple servers
- Basic command processing: `put` and `get`

## How to Run

1. Compile the server application. ```make```
2. Run the server with ```make run```

## Code Overview

The server code is divided into several parts:

- `LoadBalancer::LoadBalancer(vector<Server*> servers)`: This is the constructor of the `LoadBalancer` class. It takes a list of servers and sets up the load balancing strategy.

- `LoadBalancer::run()`: This function starts the load balancer loop. It accepts client connections and send them to the selected server for processing

- `LoadBalancer::handle_client(int client_socket)`: This function is called by the thread pool to handle a client connection. It selects a server based on the load balancing strategy, and forwards the client request to that server.

- `Server::Server(int port, size_t num_threads)`: This is the constructor of the `Server` class. It sets up the server socket and starts listening for connections.

- `Server::run()`: This function starts the server loop. It accepts client requests and enqueues them to the thread pool for processing.

- `Server::handle_client(int client_socket)`: This function is called by the thread pool to handle a client connection. It reads commands from the client, processes them, and sends back responses.

## Commands

The server understands two commands:

- `put <key> <value>`: This command stores a key-value pair in the server's data store.
- `get <key>`: This command retrieves the value for a key from the server's data store.

If the server receives an unknown command, it responds with "Unknown command".
