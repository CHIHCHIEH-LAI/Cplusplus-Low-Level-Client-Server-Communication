# Low-Level Client-Server Communication

This is a multi-threaded server application written in C++. It uses a thread pool to handle multiple client connections concurrently.

## Features

- Multi-threaded handling of client connections
- Basic command processing: `put` and `get`
- Logging of server and client activity

## How to Run

1. Compile the server application. ```make```
2. Run the server with ```make run```

## Code Overview

The server code is divided into several parts:

- `Server::Server(int port, size_t num_threads)`: This is the constructor of the `Server` class. It sets up the server socket and starts listening for connections.

- `Server::run()`: This function starts the server loop. It accepts client connections and enqueues them to the thread pool for processing.

- `Server::handle_client(int client_socket)`: This function is called by the thread pool to handle a client connection. It reads commands from the client, processes them, and sends back responses.

## Commands

The server understands two commands:

- `put <key> <value>`: This command stores a key-value pair in the server's data store.
- `get <key>`: This command retrieves the value for a key from the server's data store.

If the server receives an unknown command, it responds with "Unknown command".
