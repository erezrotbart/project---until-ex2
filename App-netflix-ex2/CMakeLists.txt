cmake_minimum_required(VERSION 3.14)
project(my_project)

# Set C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Fetch GoogleTest from GitHub
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Prevent overriding the parent project's compiler/linker settings (for Windows)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GoogleTest available
FetchContent_MakeAvailable(googletest)

# tests source files
add_executable(runTests src/Tests/server-commands-tests src/Tests/patch-test.cpp src/User/user.cpp src/Movie/movie.cpp src/Movie/AddWatchedMovies.cpp src/Movie/GetWatchedMovies.cpp src/Storage_Logic/FileDataStorage.cpp src/Commands/Help.cpp src/User/GetAllUsers.cpp src/Commands/recommended.cpp src/Commands/GET.cpp src/Commands/DELETE.cpp src/Commands/PATCH.cpp src src/Commands/POST.cpp src/App.cpp)

# main app source files
add_executable(runApp src/User/user.cpp src/Movie/movie.cpp src/Movie/AddWatchedMovies.cpp src/Movie/GetWatchedMovies.cpp src/Storage_Logic/FileDataStorage.cpp src/User/GetAllUsers.cpp src/Commands/Help.cpp src/Commands/recommended.cpp src/User/GetAllUsers.cpp src/Commands/GET.cpp src/Commands/DELETE.cpp src/Commands/PATCH.cpp src src/Commands/POST.cpp src/server/ClientHandler.cpp src/server/server.cpp src/server/Executor.cpp src/App.cpp)

# Link GoogleTest to your test executable
target_link_libraries(runTests gtest gtest_main)
