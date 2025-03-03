#ifndef MOVIE_H
#define MOVIE_H
using namespace std;
class Movie {
private:
    const int movieID;

public:
    // Constructor
    explicit Movie(int movieID);

    // Getters
    int getMovieID() const;
};

#endif
