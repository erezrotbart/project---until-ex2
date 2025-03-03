#include <iostream>
#include <thread>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include "ClientHandler.h"
#include "Executor.h"
#include "../Storage_Logic/FileDataStorage.h"
// Main server function
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }

    int server_port = std::stoi(argv[1]);

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Bind the socket to the port
    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(serverSocket, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        return 1;
    }

    // Start listening for connections
    if (listen(serverSocket, 5) < 0) {
        perror("Listen failed");
        close(serverSocket);
        return 1;
    }

    std::cout << "Server is listening on port " << server_port << "...\n";
    Executor executor;
    // Accept and handle connections
    while (true) {
        struct sockaddr_in client_sin;
        socklen_t clientLen = sizeof(client_sin);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&client_sin, &clientLen);
        if (clientSocket == -1) {
            perror("Accepting client failed");
            continue;
        }

        std::cout << "Client connected\n";

        // Use Executor to run the client handler in a new thread
        executor.execute([clientSocket]() {
            handleClient(clientSocket);
        });
    }

    close(serverSocket);
    return 0;
}