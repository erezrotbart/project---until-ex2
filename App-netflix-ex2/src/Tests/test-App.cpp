#include "../App.h"
#include "../Movie/AddWatchedMovies.h"
#include "../Storage_Logic/FileDataStorage.h"
#include "../Commands/Help.h"
#include "../Commands/recommended.h"
#include "gtest/gtest.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>

using namespace std;

// Function to clear the test file before any test
void clearTestFile() {
    ofstream file("test_user_movies.txt", ios::trunc);
    file.close();
}

class AppTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Define a map of command options
        options["add"] = new AddWatchedMovies(&fileStorage);
        options["help"] = new Help;
        options["recommend"] = new recommended(&fileStorage);
    }

    void TearDown() override {
        // Clean up to avoid memory leaks
        delete options["add"];
        delete options["help"];
        delete options["recommend"];
    }

    map<string, IInput*> options;
    FileDataStorage fileStorage{"test_user_movies.txt"};
};

// Test to check if valid input creates the correct entries in the file
TEST_F(AppTest, ValidInputCreatesEntries) {
    clearTestFile();
    App app(options);

    // Simulate input from the terminal
    istringstream input("add 1 101 103 105 205\nexit\n");
    cin.rdbuf(input.rdbuf());

    // Run the app
    app.Run();

    // Check the user's file
    ifstream file("test_user_movies.txt");
    string line;
    bool found = false;

    // Search for the user and their movies
    while (getline(file, line)) {
        if (line == "1 101 103 105 205") {
            found = true;
            break;
        }
    }

    // Close the file and check the result
    file.close();
    EXPECT_TRUE(found);
}

// Test to check if invalid input does not create entries in the file
TEST_F(AppTest, InvalidInputDoesNotCreateEntries) {
    clearTestFile();
    App app(options);

    // Simulate input from the terminal
    istringstream input("add 1 abc\nexit\n");
    cin.rdbuf(input.rdbuf());

    // Run the app
    app.Run();

    // Check the user's file
    ifstream file("test_user_movies.txt");
    string line;
    bool found = false;

    // Search for the invalid entry
    while (getline(file, line)) {
        if (line == "1 abc") {
            found = true;
            break;
        }
    }

    // Close the file and check the result
    file.close();
    EXPECT_FALSE(found);
}

// Test to check if invalid (spaces) input does not create entries in the file
TEST_F(AppTest, InvalidInputDoesNotCreateEntriesWithSpace) {
    clearTestFile();
    App app(options);

    // Simulate input from the terminal
    istringstream input("    add 1 101 103 105 205\nexit\n");
    cin.rdbuf(input.rdbuf());

    // Run the app
    app.Run();

    // Check the user's file
    ifstream file("test_user_movies.txt");
    string line;
    bool found = false;

    // Search for the invalid entry
    while (getline(file, line)) {
        if (line == "1 101 103 105 205") {
            found = true;
            break;
        }
    }

    // Close the file and check the result
    file.close();
    EXPECT_FALSE(found);
}

// Test to check if valid input does not create entries with space between words
TEST_F(AppTest, ValidInputDoesNotCreateEntriesWithSpaceBetweenWords) {
    clearTestFile();
    App app(options);

    // Simulate input from the terminal
    istringstream input("add    1 101  103   105 205\nexit\n");
    cin.rdbuf(input.rdbuf());

    // Run the app
    app.Run();

    // Check the user's file
    ifstream file("test_user_movies.txt");
    string line;
    bool found = false;

    // Search for the valid entry
    while (getline(file, line)) {
        if (line == "1 101 103 105 205") {
            found = true;
            break;
        }
    }

    // Close the file and check the result
    file.close();
    EXPECT_TRUE(found);
}

// Test to check if invalid input does not create entries in the file
TEST_F(AppTest, InvalidInputDoesNotCreateEntries2) {
    clearTestFile();
    App app(options);

    // Simulate input from the terminal
    istringstream input("add abc 105\nexit\n");
    cin.rdbuf(input.rdbuf());

    // Run the app
    app.Run();

    // Check the user's file
    ifstream file("test_user_movies.txt");
    string line;
    bool found = false;

    // Search for the invalid entry
    while (getline(file, line)) {
        if (line == "abc 105") {
            found = true;
            break;
        }
    }

    // Close the file and check the result
    file.close();
    EXPECT_FALSE(found);
}

// Test to check if help input prints the right output
TEST_F(AppTest, HandleHelpCommand) {
    clearTestFile();
    App app(options);

    // Simulate input from the terminal
    istringstream input("help\nexit\n");
    cin.rdbuf(input.rdbuf());

    // Capture the output
    ostringstream output;
    streambuf* oldCout = cout.rdbuf(output.rdbuf());

    // Run the app
    app.Run();

    // Restore the original cout buffer
    cout.rdbuf(oldCout);

    // Check the output
    string expectedOutput = "add [userid] [movieid1] [movieid2] ...\nrecommend [userid] [movieid]\nhelp\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check output for confusing inputs
TEST_F(AppTest, HandleHelpCommandTrick) {
    clearTestFile();
    App app(options);

    // Simulate input from the terminal
    istringstream input("help 123 345\nexit\n");
    cin.rdbuf(input.rdbuf());

    // Capture the output
    ostringstream output;
    streambuf* oldCout = cout.rdbuf(output.rdbuf());

    // Run the app
    app.Run();

    // Restore the original cout buffer
    cout.rdbuf(oldCout);

    // Check the output
    string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check if input with Tab does not create entries in the file
TEST_F(AppTest, InputWithTabDoesNotCreateEntries) {
    clearTestFile();
    App app(options);

    // Simulate input from the terminal with Tab character
    istringstream input("add\t1\t101\t103\t105\t205\nexit\n");
    cin.rdbuf(input.rdbuf());

    // Run the app
    app.Run();

    // Check the user's file
    ifstream file("test_user_movies.txt");
    string line;
    bool found = false;

    // Search for the entry
    while (getline(file, line)) {
        if (line == "1 101 103 105 205") {
            found = true;
            break;
        }
    }

    // Close the file and check the result
    file.close();
    EXPECT_FALSE(found);
}

TEST_F(AppTest, RecommendMoviesExampleFromEX1) {
    clearTestFile();
    FileDataStorage fileStorage("test_data.txt");

    recommended recommend(&fileStorage);

    // Capture the output
    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    // Simulate input from the terminal
    istringstream input(
        "add 1 100 101 102 103\n"
        "add 2 101 102 104 105 106\n"
        "add 3 100 104 105 107 108\n"
        "add 4 101 105 106 107 109 110\n"
        "add 5 100 102 103 105 108 111\n"
        "add 6 100 103 104 110 111 112 113\n"
        "add 7 102 105 106 107 108 109 110\n"
        "add 8 101 104 105 106 109 111 114\n"
        "add 9 100 103 105 107 112 113 115\n"
        "add 10 100 102 105 106 107 109 110 116\n"
        "recommend 1 104\n"
        "exit\n"
    );
    cin.rdbuf(input.rdbuf());

    // Run the app
    App app(options);
    app.Run();

    // Restore std::cout
    std::cout.rdbuf(oldCoutBuffer);

    // Define the expected output
    std::string expectedOutput = "105 106 111 110 112 113 107 108 109 114 \n";

    // Check the output
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check recommendations for a watched movie
TEST_F(AppTest, RecommendForWatchedMovie) {
    clearTestFile();
    FileDataStorage fileStorage("testFile.txt");

    recommended recommend(&fileStorage);

    // Capture the output
    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    // Simulate input from the terminal
    istringstream input(
        "add 1 101 102 103\n"
        "add 2 103 104 105\n"
        "add 3 102 105 106\n"
        "recommend 1 103\n"
        "exit\n"
    );
    cin.rdbuf(input.rdbuf());

    // Run the app
    App app(options);
    app.Run();

    // Restore std::cout
    std::cout.rdbuf(oldCoutBuffer);

    // Define the expected output
    std::string expectedOutput = "104 105 \n"; // Expected recommendations

    // Check the output
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check if invalid recommend input does not produce output
TEST_F(AppTest, InvalidRecommendInputDoesNothing) {
    clearTestFile();
    FileDataStorage fileStorage("testFile.txt");

    recommended recommend(&fileStorage);

    // Capture the output
    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    // Simulate input from the terminal
    istringstream input(
        "add 1 101 102 103\n"
        "add 2 103 104 105\n"
        "add 3 102 105 106\n"
        "recommend 1 abc\n"
        "exit\n"
    );
    cin.rdbuf(input.rdbuf());

    // Run the app
    App app(options);
    app.Run();

    // Restore std::cout
    std::cout.rdbuf(oldCoutBuffer);

    // Define the expected output
    std::string expectedOutput = ""; // No output expected

    // Check the output
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check if recommend input with tab does not produce output
TEST_F(AppTest, RecommendInputWithTabDoesNothing) {
    clearTestFile();
    FileDataStorage fileStorage("testFile.txt");

    recommended recommend(&fileStorage);

    // Capture the output
    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    // Simulate input from the terminal
    istringstream input(
        "add 1 101 102 103\n"
        "add 2 103 104 105\n"
        "add 3 102 105 106\n"
        "recommend\t1\t103\n"
        "exit\n"
    );
    cin.rdbuf(input.rdbuf());

    // Run the app
    App app(options);
    app.Run();

    // Restore std::cout
    std::cout.rdbuf(oldCoutBuffer);

    // Define the expected output
    std::string expectedOutput = ""; // No output expected

    // Check the output
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check if recommend input with non-existing user does not produce output
TEST_F(AppTest, RecommendNonExistingUserDoesNothing) {
    clearTestFile();
    FileDataStorage fileStorage("testFile.txt");

    recommended recommend(&fileStorage);

    // Capture the output
    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    // Simulate input from the terminal
    istringstream input(
        "add 1 101 102 103\n"
        "add 2 103 104 105\n"
        "add 3 102 105 106\n"
        "recommend 999 103\n"
        "exit\n"
    );
    cin.rdbuf(input.rdbuf());

    // Run the app
    App app(options);
    app.Run();

    // Restore std::cout
    std::cout.rdbuf(oldCoutBuffer);

    // Define the expected output
    std::string expectedOutput = ""; // No output expected

    // Check the output
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check if recommend input with non-existing movie does not produce output
TEST_F(AppTest, RecommendNonExistingMovieDoesNothing) {
    clearTestFile();
    FileDataStorage fileStorage("testFile.txt");

    recommended recommend(&fileStorage);

    // Capture the output
    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    // Simulate input from the terminal
    istringstream input(
        "add 1 101 102 103\n"
        "add 2 103 104 105\n"
        "add 3 102 105 106\n"
        "recommend 1 999\n"
        "exit\n"
    );
    cin.rdbuf(input.rdbuf());

    // Run the app
    App app(options);
    app.Run();

    // Restore std::cout
    std::cout.rdbuf(oldCoutBuffer);

    // Define the expected output
    std::string expectedOutput = ""; // No output expected

    // Check the output
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check if recommend input with empty user ID does not produce output
TEST_F(AppTest, RecommendEmptyUserIDDoesNothing) {
    clearTestFile();
    FileDataStorage fileStorage("testFile.txt");

    recommended recommend(&fileStorage);

    // Capture the output
    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    // Simulate input from the terminal
    istringstream input(
        "add 1 101 102 103\n"
        "add 2 103 104 105\n"
        "add 3 102 105 106\n"
        "recommend  103\n" // Empty user ID
        "exit\n"
    );
    cin.rdbuf(input.rdbuf());

    // Run the app
    App app(options);
    app.Run();

    // Restore std::cout
    std::cout.rdbuf(oldCoutBuffer);

    // Define the expected output
    std::string expectedOutput = ""; // No output expected

    // Check the output
    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check if recommend input with empty movie ID does not produce output
TEST_F(AppTest, RecommendEmptyMovieIDDoesNothing) {
    clearTestFile();
    FileDataStorage fileStorage("testFile.txt");

    recommended recommend(&fileStorage);

    // Capture the output
    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    // Simulate input from the terminal
    istringstream input(
        "add 1 101 102 103\n"
        "add 2 103 104 105\n"
        "add 3 102 105 106\n"
        "recommend 1 \n" // Empty movie ID
        "exit\n"
    );
    cin.rdbuf(input.rdbuf());

    // Run the app
    App app(options);
    app.Run();

    // Restore std::cout
    std::cout.rdbuf(oldCoutBuffer);

    // Define the expected output
    std::string expectedOutput = ""; // No output expected

    // Check the output
    EXPECT_EQ(output.str(), expectedOutput);
}