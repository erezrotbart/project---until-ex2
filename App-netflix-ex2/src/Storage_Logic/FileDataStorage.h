#ifndef FILE_DATA_STORAGE_H
#define FILE_DATA_STORAGE_H

#include "IDataStorage.h"
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

class FileDataStorage : public IDataStorage {
private:
    std::string filename;

    // loads data from the file
    std::unordered_map<int, std::set<int>> loadData() const;

    // saves data to the file
    void saveData(const std::unordered_map<int, std::set<int>>& data) const;

public:
    explicit FileDataStorage(const std::string& file) : filename(file) {}

    bool userExists(int userID) const override;
    std::set<int> getWatchedMovies(int userID) const override;
    void addWatchedMovies(int userID, const std::vector<int>& moviesID) override;
    // Retrieve all user data
    std::unordered_map<int, std::set<int>> getAllUserData() const override;
    void deleteWatchedMovies(int userID, const std::vector<int>& movieIDs);
};

#endif
