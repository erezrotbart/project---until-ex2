#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>
#include <unordered_map>
#include <set>
#include <mutex>
#include <sstream>
#include <iostream>
#include <unistd.h> 
#include <cstring>  

void handleClient(int clientSocket);

#endif 