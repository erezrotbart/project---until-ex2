#ifndef RECOMMENDED_H
#define RECOMMENDED_H
#include "../Storage_Logic/IDataStorage.h"
#include "IInput.h"
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

// RecommendMovies class
class recommended : public IInput {
private:
    IDataStorage* dataStorage;

    std::set<int> AllUserIDs(IDataStorage* storage);
    
    std::map<int, int> calculateUserRelevance(const std::set<int>& allUserIDs,
     const std::set<int>& userMovies, int userID, int movieID) const;

    std::map<int, int> calculateMovieRelevance(const std::map<int, int>& userIdRelevance,
      const std::set<int>& userMovies, int movieID) const;

    std::vector<std::pair<int, int>> sortRecommendations(const std::map<int, int>& movieIdRelevance)const;  

    void printTopRecommendations(const std::vector<std::pair<int, int>>& sortedRecommendations) const;
    std::string getTopRecommendationsAsString(const std::vector<std::pair<int, int>>& sortedRecommendations) const;

    bool isFullyNumeric(const std::vector<std::string>& convertedInput);

    bool IsUserExists(int userID, const std::set<int>& allUserIDs);
    bool IsMovieExists(int movieID, const std::set<int>& allUserIDs);

public:
    // constructor
    explicit recommended(IDataStorage* storage);

    // recommend function
    std::string recommend(int userID, int movieID);

    // Implement the InputCheck function from IInput
    std::string InputCheck(const std::vector<std::string>& input) override;
};

#endif // RECOMMENDED_H