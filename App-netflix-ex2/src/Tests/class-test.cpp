#include <gtest/gtest.h>
#include "../User/user.h"
#include "../Movie/movie.h"
#include "../Movie/AddWatchedMovies.h"
#include "../User/GetAllUsers.h"
#include "../Storage_Logic/FileDataStorage.h"
using namespace std;
//test get id in user class
TEST(UserTest, GetUserID) {
    User user(123);
    EXPECT_EQ(user.getUserID(), 123);
}
//test get id in movie class
TEST(MovieTest, GetMovieID) {
    Movie movie(456);
    EXPECT_EQ(movie.getMovieID(), 456);
}

const string testFilename = "test_user_movies.txt";
FileDataStorage fileStorage(testFilename);
AddWatchedMovies admin(&fileStorage);


//testing adding a user and movies to an empty file
TEST(AddWatchedMoviesTest, AddMoviesToUser) {
    // clear the file
    ofstream clearFile(testFilename, ios::trunc); 
    clearFile.close();

    // add movies to the user 1
    admin.addMoviesToUser(1, {101});
    admin.addMoviesToUser(1, {102, 103});

    // verify 
    set<int> watchedMovies = fileStorage.getWatchedMovies(1);
    set<int> expectedMovies = {101, 102, 103};
    EXPECT_EQ(watchedMovies, expectedMovies);
}

//testing adding a user and movies to a none empty file
TEST(AddWatchedMoviesTest2, AddMoviesToUser) {
    // add movies to the user 2
    admin.addMoviesToUser(2, {201});
    admin.addMoviesToUser(2, {202, 203, 204});

    // verify 
    set<int> watchedMovies = fileStorage.getWatchedMovies(2);
    set<int> expectedMovies = {201, 202, 203, 204};
    EXPECT_EQ(watchedMovies, expectedMovies);
}

//testing adding a more movies to an existing user
TEST(AddWatchedMoviesTest3, AddMoviesToUser) {
    admin.addMoviesToUser(2, {205});
    // verify 
    set<int> watchedMovies = fileStorage.getWatchedMovies(2);
    set<int> expectedMovies = {201, 202, 203, 204, 205};
    EXPECT_EQ(watchedMovies, expectedMovies);
}

//testing adding already watched movies to an existing user
TEST(AddWatchedMoviesTest4, AddMoviesToUser) {
    admin.addMoviesToUser(2, {205});
    // verify 
    set<int> watchedMovies = fileStorage.getWatchedMovies(2);
    set<int> expectedMovies = {201, 202, 203, 204, 205};
    EXPECT_EQ(watchedMovies, expectedMovies);
}

//testing adding a user with no movies
TEST(AddWatchedMoviesTest5, AddMoviesToUser) {
    admin.addMoviesToUser(3,{});
    // verify 
    bool usrExists = fileStorage.userExists(3);
    EXPECT_EQ(usrExists, false);

}

// Test for GetAllUsers class
TEST(GetAllUsersTest, RetrieveAllUsers) {
    const std::string testFilename = "test_user_movies.txt";

    // Clear and prepare the test file
    std::ofstream clearFile(testFilename, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile << "3 301\n";
    clearFile.close();

    // Create FileDataStorage and GetAllUsers instances
    FileDataStorage fileStorage(testFilename);
    GetAllUsers getAllUsers(&fileStorage);

    // Retrieve all users using GetAllUsers
    std::set<User> users = getAllUsers.getAllUsers();

    auto firstI = users.begin();
    User retrieved1 = *firstI;
    firstI++;
    User retrieved2 = *firstI;
    
    // Check if the retrieved users match the expected users
    EXPECT_EQ(retrieved1.getUserID(), 1);
    set<int> expectedMovies = {101, 102, 103};
    EXPECT_EQ(retrieved1.getMovies(), expectedMovies);
    EXPECT_EQ(retrieved2.getUserID(), 3);
    expectedMovies = {301};
    EXPECT_EQ(retrieved2.getMovies(), expectedMovies);
}
