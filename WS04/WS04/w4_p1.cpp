// w4_p1.cpp
// Jan 28 2023
// Michael Huang

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "Cheese.h"

// Cheching if header guards exist and follow convention.
#ifndef SDDS_CHEESE_H
    #error "The header guard for 'Cheese.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces
    
void printdivider(size_t cnt, const std::string heading = "") {
  if (heading != "")
    std::cout << heading << "\n";
  for (auto i = 0u; i < cnt; ++i)
    std::cout << "-";
  std::cout << std::endl;
}

int main() {
  sdds::Cheese **cheeses = nullptr;                             // pointer be pointer. #ref1
  size_t cnt = 0;

  if (1) {
    std::ifstream file("cheeses.txt");
    if (!file) {
      std::cout << "ERROR: Cannot open file [" << "].\n";
      return 1;
    }

    std::string cheeseline;
    
    do {
      std::getline(file, cheeseline);
      if (file) {
        if (cheeseline[0] != '#')
          ++cnt;
      }
    } while (file);

    cheeses = new sdds::Cheese *[cnt];                                          // yek array class pointer be pointer. tedade item haye array ro ba cnt dar avordim. #ref1
    cnt = 0;

   
    file.clear();
    file.seekg(std::ios::beg);                                                  // pointere file ro mibare avale text dobare
    do {
      std::getline(file, cheeseline);
   
      if (file) {
        if (cheeseline[0] != '#') {
          cheeses[cnt] = new sdds::Cheese(cheeseline);                          // har string line ro dadim be yek pointer be object. mesle => Test *p = new Test("behzad"). #ref2
          ++cnt;
        }
      }
    } while (file);
    file.close();
  } else {
    std::cout << "ERROR: cheeses.txt file not provided.\n";
    return 2;
  }

  printdivider(70, "Cheese Inventory");
  for (auto i = 0u; i < cnt; ++i) {
    std::cout << *cheeses[i];
  }
  printdivider(70);
  
  if (cnt != 0) {
    sdds::Cheese c1 = cheeses[0]->slice(100);   // to array cheeses, har item, pointer be object hast. #ref2
    sdds::Cheese c2 = cheeses[3]->slice(500);   
    sdds::Cheese c3 = cheeses[8]->slice(10000);  
    
    printdivider(70, "Sliced Cheeses");
    std::cout << c1 << c2 << c3;
    printdivider(70);
  }

  
  printdivider(70, "Cheese Inventory");
  for (auto i = 0u; i < cnt; ++i) {
    std::cout << *cheeses[i];                   // chon bayad dade bashe pas mishe *cheeses[i]
  }
  printdivider(70);

  // cleanup
  for (auto i = 0u; i < cnt; ++i)
    delete cheeses[i];                          // chon **cheese hast. delete pointer haye har item
  delete[] cheeses;                             // delete pointere array

  return cout;
}
