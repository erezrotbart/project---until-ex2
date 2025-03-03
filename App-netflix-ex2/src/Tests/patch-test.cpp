#include "../Commands/PATCH.h"
#include "../Storage_Logic/FileDataStorage.h"
#include "gtest/gtest.h"
#include <fstream>

// Test setup for PATCH command
const std::string testFilePATCH = "test_user_movies_patch.txt";
FileDataStorage fileStoragePATCH(testFilePATCH);
PATCH patchCommand(&fileStoragePATCH);

// Test for a valid PATCH command with an existing user and movies
TEST(PATCHTest, ValidPATCHCommand) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFilePATCH, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile.close();

    std::vector<std::string> input = {"PATCH", "1", "104", "105"};
    std::string response = patchCommand.InputCheck(input);

    // Expect "204 No Content" for successful update
    EXPECT_EQ(response, "204 No Content");

    // Verify that the movies were added to the user
    std::ifstream file(testFilePATCH);
    std::string line;
    bool moviesAdded = false;
    while (std::getline(file, line)) {
        if (line.find("1 101 102 103 104 105") != std::string::npos) {
            moviesAdded = true;
            break;
        }
    }
    file.close();

    EXPECT_TRUE(moviesAdded);
}

// Test for PATCH command with a non-existent user
TEST(PATCHTest, NonExistentUser) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFilePATCH, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile.close();

    std::vector<std::string> input = {"PATCH", "2", "104"};
    std::string response = patchCommand.InputCheck(input);

    // Expect "404 Not Found" for non-existent user
    EXPECT_EQ(response, "404 Not Found");

    // Verify that no changes were made to the file
    std::ifstream file(testFilePATCH);
    std::string line;
    bool userFound = false;
    while (std::getline(file, line)) {
        if (line.find("1 101 102 103") != std::string::npos) {
            userFound = true;
            break;
        }
    }
    file.close();

    EXPECT_TRUE(userFound);
}

// Test for PATCH command with invalid input format
TEST(PATCHTest, InvalidInputFormat) {
    std::vector<std::string> input = {"PATCH", "abc", "101"};
    std::string response = patchCommand.InputCheck(input);

    // Expect "400 Bad Request" for invalid input
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for PATCH command with fewer arguments
TEST(PATCHTest, InsufficientArguments) {
    std::vector<std::string> input = {"PATCH", "1"};
    std::string response = patchCommand.InputCheck(input);

    // Expect "400 Bad Request" for insufficient arguments
    EXPECT_EQ(response, "400 Bad Request");
}

// Test for PATCH command with tab character in input
TEST(PATCHTest, TabCharacterInInput) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFilePATCH, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile.close();

    std::vector<std::string> input = {"PATCH", "1", "\t104"};
    std::string response = patchCommand.InputCheck(input);

    // Expect "400 Bad Request" for input with tab character
    EXPECT_EQ(response, "400 Bad Request");

    // Verify that no changes were made to the file
    std::ifstream file(testFilePATCH);
    std::string line;
    bool userFound = false;
    while (std::getline(file, line)) {
        if (line.find("1 101 102 103") != std::string::npos) {
            userFound = true;
            break;
        }
    }
    file.close();

    EXPECT_TRUE(userFound);
}

// Test to ensure no new users are added when using PATCH command
TEST(PATCHTest, NoNewUsersAdded) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFilePATCH, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile << "2 201 202 203\n";
    clearFile.close();

    // Add movies to existing users
    std::vector<std::string> input1 = {"PATCH", "1", "104"};
    std::string response1 = patchCommand.InputCheck(input1);
    EXPECT_EQ(response1, "204 No Content");

    std::vector<std::string> input2 = {"PATCH", "2", "204"};
    std::string response2 = patchCommand.InputCheck(input2);
    EXPECT_EQ(response2, "204 No Content");

    // Verify that no new users were added
    bool userExists = fileStoragePATCH.userExists(3);
    EXPECT_EQ(userExists, false);

    // Verify that the movies were added to the existing users
    set<int> watchedMovies1 = fileStoragePATCH.getWatchedMovies(1);
    set<int> expectedMovies1 = {101, 102, 103, 104};
    EXPECT_EQ(watchedMovies1, expectedMovies1);

    set<int> watchedMovies2 = fileStoragePATCH.getWatchedMovies(2);
    set<int> expectedMovies2 = {201, 202, 203, 204};
    EXPECT_EQ(watchedMovies2, expectedMovies2);
}

// Test for PATCH command with a mix of valid and invalid movies
TEST(PATCHTest, MixedValidAndInvalidMovies) {
    // Clear and prepare the test file
    std::ofstream clearFile(testFilePATCH, std::ios::trunc);
    clearFile << "1 101 102 103\n";
    clearFile.close();

    std::vector<std::string> input = {"PATCH", "1", "104", "invalid"};
    std::string response = patchCommand.InputCheck(input);

    // Expect "400 Bad Request" for invalid movie ID
    EXPECT_EQ(response, "400 Bad Request");

    // Verify that no changes were made to the file
    std::ifstream file(testFilePATCH);
    std::string line;
    bool userFound = false;
    while (std::getline(file, line)) {
        if (line.find("1 101 102 103") != std::string::npos) {
            userFound = true;
            break;
        }
    }
    file.close();

    EXPECT_TRUE(userFound);
}