#include "ClientHandler.h"
#include "../Commands/recommended.h"
#include "../Movie/AddWatchedMovies.h"
#include "../Commands/Help.h"
#include "../Storage_Logic/FileDataStorage.h"
#include "../App.h"
#include "../Commands/GET.h"
#include "../Commands/POST.h"
#include "../Commands/DELETE.h"
#include "../Commands/PATCH.h" 

// Shared data structure and mutex
std::unordered_map<int, std::set<int>> userMovies;
std::mutex dataMutex;

void handleClient(int clientSocket) {
    //preproccessing
    // const string filename = "data/data.txt"; // mark as comment when running with docker, and unmark next line
    const string filename = "/usr/src/App-netflix/data/data.txt"; // unmark as comment when running with docker, and mark previus line
    FileDataStorage fileStorage(filename);
    map<string, IInput*> options;
    options["POST"] = new POST(&fileStorage);
    options["PATCH"] = new PATCH(&fileStorage);
    options["help"] = new Help;
    options["GET"] = new GET(&fileStorage); 
    options["DELETE"] = new DELETE(&fileStorage);
    App app(options);

    char buffer[1024];

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        // Read data from the client
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
        if (bytesRead <= 0) {
            break; // Client disconnected
        }

        std::string command(buffer);
        std::string response;

        // Lock the shared data during processing
        {
            std::lock_guard<std::mutex> lock(dataMutex);
            response = app.handleCommand(command);
            if (!response.empty()) { // Only print non-empty output
                response += "\n";
            }
            
            // Send the response to the client
            write(clientSocket, response.c_str(), response.size());
        }
    }
    // Close the client socket
    close(clientSocket);
}