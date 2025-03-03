#include "movie.h"

// Constructor
Movie::Movie(int movieID) : movieID(movieID) {}

// Getters
int Movie::getMovieID() const {
    return movieID;
}
