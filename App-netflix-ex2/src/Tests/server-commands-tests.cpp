#include "../Commands/GET.h"
#include "../Commands/DELETE.h"
#include "../Commands/POST.h"
#include "../Commands/Help.h"
#include "../Storage_Logic/FileDataStorage.h"
#include "gtest/gtest.h"
#include <fstream>

// Test setup for GET command
const std::string testFileGET = "test_user_movies_get.txt";
FileDataStorage fileStorageGET(testFileGET);
GET getCommand(&fileStorageGET);

// Test setup for DELETE command
const std::string testFileDELETE = "test_user_movies_delete.txt";
FileDataStorage fileStorageDELETE(testFileDELETE);
DELETE deleteCommand(&fileStorageDELETE);

// Test for a valid GET command with an existing user and movie
TEST(GETTest, ValidGETCommand) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFileGET, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile << "2 104 105 106\n";
    clearFile.close();

    std::vector<std::string> input = {"GET", "1", "106"};
    std::string response = getCommand.InputCheck(input);

    // Expected recommendations for user 1 based on movie 101
    std::string expectedResponse = "200 Ok\n\n104 105"; // Example recommendation
    EXPECT_EQ(response, expectedResponse);
}

// Test for GET command with a non-existent user
TEST(GETTest, NonExistentUser) {
    std::vector<std::string> input = {"GET", "999", "101"};
    std::string response = getCommand.InputCheck(input);

    // Expect "404 Not Found" for non-existent user
    EXPECT_EQ(response, "404 Not Found");
}

// Test for GET command with an invalid movie ID
TEST(GETTest, NonExistentMovie) {
    std::vector<std::string> input = {"GET", "1", "999"};
    std::string response = getCommand.InputCheck(input);

    // Expect an empty response for non-existent movie
    EXPECT_EQ(response, "200 Ok\n\n");
}

// Test for GET command with invalid input format
TEST(GETTest, InvalidInputFormat) {
    std::vector<std::string> input = {"GET", "abc", "101"};
    std::string response = getCommand.InputCheck(input);

    // Expect "400 Bad Request" for invalid input
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for GET command with fewer arguments
TEST(GETTest, InsufficientArguments) {
    std::vector<std::string> input = {"GET", "1"};
    std::string response = getCommand.InputCheck(input);

    // Expect "400 Bad Request" for insufficient arguments
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for GET command with additional arguments
TEST(GETTest, ExcessiveArguments) {
    std::vector<std::string> input = {"GET", "1", "101", "extra"};
    std::string response = getCommand.InputCheck(input);

    // Expect "400 Bad Request" for excessive arguments
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for GET command with no movies or users in the system
TEST(GETTest, NoMoviesAvailable) {
    // Clear the file
    std::ofstream clearFile(testFileGET, std::ios::trunc);
    clearFile.close();

    std::vector<std::string> input = {"GET", "1", "101"};
    std::string response = getCommand.InputCheck(input);

    // Expect an empty response if no movies are in the system
    EXPECT_EQ(response, "404 Not Found");
}

// Test for DELETE command with valid movies
TEST(DELETETest, ValidMoviesDeletion) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFileDELETE, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile << "2 104 105 106\n";
    clearFile.close();

    std::vector<std::string> input = {"DELETE", "1", "102", "103"};
    std::string response = deleteCommand.InputCheck(input);

    // Expect "204 No Content" for successful deletion
    EXPECT_EQ(response, "204 No Content");

    // Verify that the movies (102, 103) were deleted
    std::ifstream file(testFileDELETE);
    std::string line;
    bool moviesDeleted = true;
    while (std::getline(file, line)) {
        if (line.find("102") != std::string::npos || line.find("103") != std::string::npos) {
            moviesDeleted = false;
            break;
        }
    }
    file.close();

    EXPECT_TRUE(moviesDeleted);
}

// Test for DELETE command with a non-existent user
TEST(DELETETest, NonExistentUser) {
    std::vector<std::string> input = {"DELETE", "999", "101"};
    std::string response = deleteCommand.InputCheck(input);

    // Expect "404 Not Found" for non-existent user
    EXPECT_EQ(response, "404 Not Found");
}

// Test for DELETE command with a non-existent movie
TEST(DELETETest, NonExistentMovie) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFileDELETE, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile << "2 104 105 106\n";
    clearFile.close();

    std::vector<std::string> input = {"DELETE", "1", "999"};
    std::string response = deleteCommand.InputCheck(input);

    // Expect "404 Not Found" for non-existent movie
    EXPECT_EQ(response, "404 Not Found");
}

// Test for DELETE command with invalid input format
TEST(DELETETest, InvalidInputFormat) {
    std::vector<std::string> input = {"DELETE", "abc", "101"};
    std::string response = deleteCommand.InputCheck(input);

    // Expect "400 Bad Request" for invalid input
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for DELETE command with fewer arguments
TEST(DELETETest, InsufficientArguments) {
    std::vector<std::string> input = {"DELETE", "1"};
    std::string response = deleteCommand.InputCheck(input);

    // Expect "400 Bad Request" for insufficient arguments
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for DELETE command with additional arguments
TEST(DELETETest, ExcessiveArguments) {
    std::vector<std::string> input = {"DELETE", "1", "101", "extra"};
    std::string response = deleteCommand.InputCheck(input);

    // Expect "400 Bad Request" for excessive arguments
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for DELETE command with no movies or users in the system
TEST(DELETETest, NoMoviesAvailable) {
    // Clear the file
    std::ofstream clearFile(testFileDELETE, std::ios::trunc);
    clearFile.close();

    std::vector<std::string> input = {"DELETE", "1", "101"};
    std::string response = deleteCommand.InputCheck(input);

    // Expect "404 Not Found" if no movies are in the system
    EXPECT_EQ(response, "404 Not Found");
}

// Test for DELETE command with tab character in input
TEST(DELETETest, TabCharacterInInput) {
    std::vector<std::string> input = {"DELETE", "1", "\t101"};
    std::string response = deleteCommand.InputCheck(input);

    // Expect "400 Bad Request" for input with tab character
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for DELETE command with a mix of valid and invalid movies
TEST(DELETETest, MixedValidAndInvalidMovies) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFileDELETE, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile << "2 104 105 106\n";
    clearFile.close();

    std::vector<std::string> input = {"DELETE", "1", "102", "999"};
    std::string response = deleteCommand.InputCheck(input);

    // Expect "404 Not Found" if at least one movie is not found
    EXPECT_EQ(response, "404 Not Found");

    // Verify that the valid movie (102) was not deleted
    std::ifstream file(testFileDELETE);
    std::string line;
    bool movieFound = false;
    while (std::getline(file, line)) {
        if (line.find("1 101 102 103") != std::string::npos) {
            movieFound = true;
            break;
        }
    }
    file.close();

    EXPECT_TRUE(movieFound);
}
TEST(HelpTest, ReturnsCorrectHelpString) {
    Help help;
    std::string expected_output = 
        "DELETE, arguments: [userid] [movieid]\n"
        "GET, arguments: [userid] [movieid]\n"
        "PATCH, arguments: [userid] [movieid]\n"
        "POST, arguments: [userid] [movieid]\n"
        "help";
    
    EXPECT_EQ(help.getHelp(), expected_output);
}
// Test setup for POST command
const std::string testFilePOST = "test_user_movies_post.txt";
FileDataStorage fileStoragePOST(testFilePOST);
POST postCommand(&fileStoragePOST);

// Test for a valid POST command (new user)
TEST(POSTTest, ValidPOSTCommand) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFilePOST, std::ios::trunc);
    clearFile.close();

    std::vector<std::string> input = {"POST", "1", "101", "102"};
    std::string response = postCommand.InputCheck(input);

    // Expect "201 Created" for successful new user creation
    EXPECT_EQ(response, "201 Created");

    // Verify that the user was added to the file
    std::ifstream file(testFilePOST);
    std::string line;
    bool userExists = false;
    while (std::getline(file, line)) {
        if (line.find("1 101 102") != std::string::npos) {
            userExists = true;
            break;
        }
    }
    file.close();

    EXPECT_TRUE(userExists);
}

// Test for POST command with an existing user
TEST(POSTTest, UserAlreadyExists) {
    std::vector<std::string> input = {"POST", "1", "103"};
    std::string response = postCommand.InputCheck(input);

    // Expect "400 Bad Request" since user already exists
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for POST command with invalid user ID (non-numeric)
TEST(POSTTest, InvalidUserID) {
    std::vector<std::string> input = {"POST", "abc", "101"};
    std::string response = postCommand.InputCheck(input);

    // Expect "400 Bad Request" for non-numeric user ID
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for POST command with non-numeric movie ID
TEST(POSTTest, InvalidMovieID) {
    std::vector<std::string> input = {"POST", "2", "xyz"};
    std::string response = postCommand.InputCheck(input);

    // Expect "400 Bad Request" for non-numeric movie ID
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for POST command with insufficient arguments
TEST(POSTTest, InsufficientArguments) {
    std::vector<std::string> input = {"POST", "1"};
    std::string response = postCommand.InputCheck(input);

    // Expect "400 Bad Request" since no movie IDs are provided
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for POST command with extra arguments
TEST(POSTTest, ExcessiveArguments) {
    std::vector<std::string> input = {"POST", "1", "101", "102", "extra"};
    std::string response = postCommand.InputCheck(input);

    // Expect "400 Bad Request" for excessive arguments
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for POST command with empty input file (first user)
TEST(POSTTest, FirstUserCreation) {
    // Clear the file
    std::ofstream clearFile(testFilePOST, std::ios::trunc);
    clearFile.close();

    std::vector<std::string> input = {"POST", "5", "201", "202"};
    std::string response = postCommand.InputCheck(input);

    // Expect "201 Created" for first user creation
    EXPECT_EQ(response, "201 Created");

    // Verify that the user was added to the file
    std::ifstream file(testFilePOST);
    std::string line;
    bool userExists = false;
    while (std::getline(file, line)) {
        if (line.find("5 201 202") != std::string::npos) {
            userExists = true;
            break;
        }
    }
    file.close();

    EXPECT_TRUE(userExists);
}