// Workshop 5 - Functions and Error Handling
// 2020/02 - Cornel
// 2021/01/19 - Chris
// 2021/02/12 - Cornel
// 2023/10/05 - Cornel

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Book.h" // intentional

// Cheching if header guards exist and follow convention.
#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// ws books.txt
int main(int argc, char** argv)
{

	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";


	// get the books
	sdds::Book library[7];
	if (argc == 2) {
		std::ifstream file("books.txt");
		if (!file) {
			std::cerr << "ERROR: Cannot open file"  << ".\n";							// cerr mesle cout mimune baraye error. 
			exit(AppErrors::CannotOpenFile);					//  exit kon ba classe AppErrors::CannotOpenFile. mitunestim exit(0); ham bokonim
		}
		std::string line;								// chon to Book.cpp az using namespace std; estefade karim, inja std:: mizarim ke ghati nashe ba un
		size_t index = 0;
		while (std::getline(file, line) && index < 7) {			// getline(), true ya false bar migardune. line por mishe.
			if (line[0] != '#') {
				library[index] = sdds::Book(line);		// haminja yek class besaz va beriz to library[index]
				index++;
			}
		}
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		exit(AppErrors::BadArgumentCount);
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	// lambda function
	auto fixPrice = [&](sdds::Book& book) {							// output = auto. [&] yani global variable haro ba reference begir
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
	/*
		auto yani dakhele array library type item ha harchi bud okeye, inja Book hast. yani mishe bejaye auto bezarim sdds::BooK
		const yani dakhele loop book ro taghir nade. masalan book.setPrice(10.0); error mide
		& yani dakhele loop vaghti iterate mikoni khode book ro biyar, na copish ro 
	*/
	for (const auto& book : library) {				
		std::cout << book << std::endl;
	}

	std::cout << "-----------------------------------------\n\n";

	for (sdds::Book& book : library) {					// conste aval ro nazashtim ke betunim book ro taghir bedim
		fixPrice(book);
	}


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	for (const auto& book : library) {
		std::cout << book << std::endl;
	}


	std::cout << "-----------------------------------------\n";

	return cout;
}
