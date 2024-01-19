#include <iostream>
#include "CheeseShop.h"
#include "Cheese.h"					// "Cheese.h" bayad ham to .h va .cpp include beshe, agar na error mide. CheeseShop.h => #ref5

using namespace std;

namespace sdds {
	// Constructor: Initializes a CheeseShop object with a given name.
    CheeseShop::CheeseShop(const std::string& name) : shopName(name), inventory(nullptr), inventorySize(0) {};

    // Member function to add a Cheese object to the shop's inventory.
    CheeseShop& CheeseShop::addCheese(const Cheese& obj) {
        // Create a new array of pointers with increased size.
        const Cheese** temp = new const Cheese*[inventorySize + 1];
    
        // Copy existing pointers to the new array.
        for (size_t i = 0; i < inventorySize; i++) {
            temp[i] = inventory[i];
        }

        // Copy the given Cheese object to the new array.
        temp[inventorySize] = new const Cheese(obj);
    
        // Delete the existing array of pointers.
        delete[] inventory;
    
        // Update the inventory pointer to the new array.
        inventory = temp;
    
        // Increment the inventory size.
        inventorySize++;
    
        return *this;
    }

    // Destructor: Cleans up memory allocated for the inventory.
    CheeseShop::~CheeseShop() {
        for (size_t i = 0; i < inventorySize; i++) {
            delete inventory[i];
        }
        delete[] inventory;
    }

    // Copy constructor: Creates a new CheeseShop by deep copying the contents of another.
    CheeseShop::CheeseShop(const CheeseShop& obj) : shopName(obj.shopName), inventorySize(obj.inventorySize) {
        inventory = new const Cheese*[inventorySize];
    
        // Deep copy each Cheese object in the inventory.
        for (size_t i = 0; i < inventorySize; i++) {
            inventory[i] = new Cheese(*(obj.inventory[i]));
        }
    }

    // Move constructor: Creates a new CheeseShop by taking ownership of the contents of another.
    CheeseShop::CheeseShop(CheeseShop&& obj) noexcept : shopName(std::move(obj.shopName)), inventorySize(obj.inventorySize) {
        inventory = obj.inventory;
        obj.inventory = nullptr;
        obj.inventorySize = 0;
    }

    // Copy assignment operator: Deep copies the contents of another CheeseShop.
    CheeseShop& CheeseShop::operator=(const CheeseShop& obj) {
        if (this != &obj) {
            // Clean up existing inventory.
            for (size_t i = 0; i < inventorySize; i++) {
                delete inventory[i];
            }
            delete[] inventory;

            // Copy shop name and inventory size.
            shopName = obj.shopName;
            inventorySize = obj.inventorySize;

            // Create a new array of pointers.
            inventory = new const Cheese*[inventorySize];

            // Deep copy each Cheese object in the inventory.
            for (size_t i = 0; i < inventorySize; i++) {
                inventory[i] = new Cheese(*(obj.inventory[i]));
            }
        }
        return *this;
    }

    // Move assignment operator: Takes ownership of the contents of another CheeseShop.
    CheeseShop& CheeseShop::operator=(CheeseShop&& obj) noexcept {
        if (this != &obj) {
            // Clean up existing inventory.
            for (size_t i = 0; i < inventorySize; i++) {
                delete inventory[i];
            }
            delete[] inventory;

            // Move shop name and inventory size.
            shopName = std::move(obj.shopName);
            inventory = obj.inventory;
            obj.inventory = nullptr;
            obj.inventorySize = 0;
        }
        return *this;
    }

    // Overloaded stream insertion operator: Outputs the contents of a CheeseShop to a stream.
    ostream& operator<<(ostream& ostr, const CheeseShop& obj) {
        ostr << "--------------------------\n";
        ostr << obj.shopName << "\n";
        ostr << "--------------------------\n";
        if (obj.inventorySize == 0) {
            ostr << "This shop is out of cheese!\n";
        } else {
            // Output each Cheese object in the inventory.
            for (size_t i = 0; i < obj.inventorySize; i++) {
                ostr << *obj.inventory[i];
            }
        }
        ostr << "--------------------------\n";
        return ostr;
    }
}