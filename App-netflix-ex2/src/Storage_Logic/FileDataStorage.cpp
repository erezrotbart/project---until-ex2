#include "FileDataStorage.h"
using namespace std;

unordered_map<int, set<int>> FileDataStorage::loadData() const {
    unordered_map<int, set<int>> data;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        int userID;
        ss >> userID;
        set<int> movies;
        int movieID;
        while (ss >> movieID) {
            movies.insert(movieID);
        }
        data[userID] = movies;
    }
    return data;
}

void FileDataStorage::saveData(const unordered_map<int, set<int>>& data) const {
    ofstream file(filename, ios::trunc);
    for (const auto& [userID, movies] : data) {
        file << userID;
        for (int movieID : movies) {
            file << " " << movieID;
        }
        file << endl;
    }
}

bool FileDataStorage::userExists(int userID) const {
    auto data = loadData();
    return data.find(userID) != data.end();
}

set<int> FileDataStorage::getWatchedMovies(int userID) const {
    auto data = loadData();
    if (data.find(userID) != data.end()) {
        return data.at(userID);
    }
    return {};
}

void FileDataStorage::addWatchedMovies(int userID, const vector<int>& moviesID) {
    auto data = loadData();
    for (int movieID : moviesID) {
        data[userID].insert(movieID);
    }
    saveData(data);
}
unordered_map<int, set<int>> FileDataStorage::getAllUserData() const {
    return loadData();
}

void FileDataStorage::deleteWatchedMovies(int userID, const std::vector<int>& movieIDs) {
    auto data = loadData();
    if (data.find(userID) != data.end()) {
        for (int movieID : movieIDs) {
            data[userID].erase(movieID);
        }
        saveData(data);
    }
}
