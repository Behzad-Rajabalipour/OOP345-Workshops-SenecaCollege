#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Collection.h"
#include "SpellChecker.h"
#include "Book.h"
#include "Movie.h"

#ifndef SDDS_BOOK_H
#error "The header guard for 'Book.h' doesn't follow the convention!"
#endif
#ifndef SDDS_MOVIE_H
#error "The header guard for 'Movie.h' doesn't follow the convention!"
#endif
#ifndef SDDS_SPELLCHECKER_H
#error "The header guard for 'SpellChecker.h' doesn't follow the convention!"
#endif
#ifndef SDDS_COLLECTION_H
#error "The header guard for 'Collection.h' doesn't follow the convention!"
#endif

int cout = 0; // Won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
    CannotOpenFile = 1,     // An input file cannot be opened
    BadArgumentCount = 2,   // The application didn't receive enough parameters
};

// The observer function for adding books to the collection:
// Should be called every time a new book is added to the collection
void bookAddedObserver(const sdds::Collection<sdds::Book>& theCollection, const sdds::Book& theBook) {
    std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

// The observer function for adding movies to the collection:
// Should be called every time a new movie is added to the collection
void movieAddedObserver(const sdds::Collection<sdds::Movie>& theCollection, const sdds::Movie& theMovie) {
    std::cout << "Movie \"" << theMovie.title()
        << "\" added to collection \"" << theCollection.name()
        << "\" (" << theCollection.size() << " items).\n";
}

// Command line arguments: books.txt movies.txt file_missing.txt file_words.txt
int main(int argc, char** argv)
{
    std::cout << "Command Line:\n";
    std::cout << "--------------------------\n";
    for (int i = 0; i < argc; i++)
        std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
    std::cout << "--------------------------\n\n";

    // Creating a collection of books
    sdds::Collection<sdds::Book> library("Bestsellers");
    if (argc == 5) {
        std::ifstream fileBooks(argv[1]);
        if (!fileBooks) {
            std::cerr << "ERROR: Cannot open file" << argv[1] << ".\n";
            exit(AppErrors::CannotOpenFile);
        }

        std::string line;
        size_t count = 0;
        // Reading the first 4 non-comment lines from the book file
        while (count < 4 && std::getline(fileBooks, line)) {
            if (line[0] != '#') {
                library += sdds::Book(line);  // Adding books to the collection
                count++;
            }
        }

        library.setObserver(bookAddedObserver);  // Setting an observer for book additions

        // Reading the remaining non-comment lines from the book file
        while (std::getline(fileBooks, line)) {
            if (line[0] != '#') {
                library += sdds::Book(line);  // Adding books to the collection
            }
        }
    }
    else {
        std::cerr << "ERROR: Incorrect number of arguments.\n";
        std::exit(AppErrors::BadArgumentCount);
    }

    double usdToCadRate = 1.3;
    double gbpToCadRate = 1.5;

    // Lambda function to fix book prices based on country and year
    auto fixPrice = [&](sdds::Book& book) {
        if (book.country() == "US") {
            book.price() *= usdToCadRate;
        }
        else if (book.country() == "UK" && book.year() >= 1990 && book.year() <= 1999) {
            book.price() *= gbpToCadRate;
        }
    };

    std::cout << "-----------------------------------------\n";
    std::cout << "The library content\n";
    std::cout << "-----------------------------------------\n";
    std::cout << library;
    std::cout << "-----------------------------------------\n\n";

    // Update book prices
    for (size_t i = 0; i < library.size(); i++) {
        fixPrice(library[i]);
    }

    std::cout << "-----------------------------------------\n";
    std::cout << "The library content (updated prices)\n";
    std::cout << "-----------------------------------------\n";
    std::cout << library;
    std::cout << "-----------------------------------------\n\n";

    // Creating a collection of movies
    sdds::Collection<sdds::Movie> theCollection("Action Movies");

    sdds::Movie movies[5];
    if (argc > 2) {
        std::ifstream fileMovies(argv[2]);
        if (!fileMovies) {
            std::cerr << "Error opening file: " << argv[2] << std::endl;
            exit(AppErrors::CannotOpenFile);
        }

        std::string line;
        size_t count = 0;
        // Reading the first 5 non-comment lines from the movie file
        while (count < 5 && std::getline(fileMovies, line)) {
            if (line[0] != '#') {
                movies[count] = sdds::Movie(line);  // Adding movies to the array
                count++;
            }
        }
    }

    std::cout << "-----------------------------------------\n";
    std::cout << "Testing addition and callback function\n";
    std::cout << "-----------------------------------------\n";
    if (argc > 2) {
        // Populating theCollection with movies and setting an observer
        ((theCollection += movies[0]) += movies[1]) += movies[2];
        theCollection += movies[1];

        theCollection.setObserver(movieAddedObserver);

        theCollection += movies[3];
        theCollection += movies[3];
        theCollection += movies[4];
    }
    else {
        std::cout << "** No movies in the Collection\n";
    }
    std::cout << "-----------------------------------------\n\n";

    std::cout << "-----------------------------------------\n";
    std::cout << "Testing exceptions and operator[]\n";
    std::cout << "-----------------------------------------\n";
    try {
        // Trying to access elements using operator[]
        for (auto i = 0u; i < 10; ++i)
            std::cout << theCollection[i] << std::endl;
    }
    catch (const std::exception& error) {
        std::cout << "** EXCEPTION: " << error.what() << std::endl;
    }

    std::cout << "-----------------------------------------\n\n";

    std::cout << "-----------------------------------------\n";
    std::cout << "Testing the functor\n";
    std::cout << "-----------------------------------------\n";
    for (auto i = 3; i < argc; ++i)
    {
        try {
            // Creating a SpellChecker and fixing spelling for books and movies
            sdds::SpellChecker sp(argv[i]);
            for (auto j = 0u; j < library.size(); ++j)
                library[j].fixSpelling(sp);
            sp.showStatistics(std::cout);

            for (auto j = 0u; j < theCollection.size(); ++j)
                theCollection[j].fixSpelling(sp);
            sp.showStatistics(std::cout);

        }
        catch (const std::exception& error) {
            std::cout << "** EXCEPTION: " << error.what() << std::endl;
        }
    }
    if (argc < 3) {
        std::cout << "** Spellchecker is empty\n";
        std::cout << "-----------------------------------------\n";
    }
    std::cout << "\n";

    std::cout << "=========================================\n";
    std::cout << "Wrapping up this workshop\n";
    std::cout << "--------------- Movies ------------------\n";
    std::cout << theCollection;
    std::cout << "--------------- Books -------------------\n";
    std::cout << library;
    std::cout << "-----------------------------------------\n";
    std::cout << "Testing operator[] (the other overload)\n";
    std::cout << "-----------------------------------------\n";
    const sdds::Movie* aMovie = theCollection["Terminator 2"];
    if (aMovie == nullptr)
        std::cout << "** Movie Terminator 2 not in the collection.\n";
    aMovie = theCollection["Dark Phoenix"];
    if (aMovie != nullptr)
        std::cout << "In this collection:\n" << *aMovie << std::endl;
    std::cout << "-----------------------------------------\n";

    return cout; // If using namespace std; in .h files, this line causes an error due to ambiguity
}
