#include "mydatastore.h"
#include "util.h"
#include <algorithm>
#include <iostream>
#include <iterator>

// Constructor
MyDataStore::MyDataStore() {}

// Destructor - just in case
MyDataStore::~MyDataStore() {
    // 
    for (size_t i = 0; i < products_.size(); i++) {
        delete products_[i];
    }
    // 
    std::map<std::string, User*>::iterator userIt;
    for (userIt = users_.begin(); userIt != users_.end(); ++userIt) {
        delete userIt->second;
    }
}

// Add a product or an item to the data store
void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);
    // Index the product by its keywords
    std::set<std::string> keywords = p->keywords();
    std::set<std::string>::iterator kit;
    for (kit = keywords.begin(); kit != keywords.end(); ++kit) {
        keywordIndex_[*kit].insert(p);
    }
}

// Add a user to the data store
void MyDataStore::addUser(User* u) {
    std::string uname = u->getName();
    users_[uname] = u;
    // Initialize an empty cart for the new user
    if (userCarts_.find(uname) == userCarts_.end()) {
        userCarts_[uname] = std::vector<Product*>();
    }
}

// Search for products based on terms (AND/OR)
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> resultSet;
    if (terms.empty()) {
        return std::vector<Product*>();
    }
    // AND search
    if (type == 0) {
        if (keywordIndex_.find(terms[0]) != keywordIndex_.end()) {
            resultSet = keywordIndex_[terms[0]];
        } else {
            return std::vector<Product*>();
        }
        for (size_t i = 1; i < terms.size(); i++) {
            if (keywordIndex_.find(terms[i]) != keywordIndex_.end()) {
                resultSet = setIntersection(resultSet, keywordIndex_[terms[i]]);
            } else {
                resultSet.clear();
                break;
            }
        }
    }
    // OR search
    else if (type == 1) {
        for (size_t i = 0; i < terms.size(); i++) {
            if (keywordIndex_.find(terms[i]) != keywordIndex_.end()) {
                resultSet = setUnion(resultSet, keywordIndex_[terms[i]]);
            }
        }
    }
    return std::vector<Product*>(resultSet.begin(), resultSet.end());
}

// Save the current state of the database to a file
void MyDataStore::dump(std::ostream& ofile) {
    // Dump products

    ofile << "<products>\n" ;

    for (size_t i = 0; i < products_.size(); i++) {
           products_[i]->dump(ofile);}

    ofile <<  "</products>\n";
    // Dump users
    std::map<std::string, User*>::iterator it;
    ofile << "<users>\n" ; 

    for (it = users_.begin(); it != users_.end(); ++it) {
        ofile << "user" << std::endl;
        ofile << it->second->getName() << " " << it->second->getBalance() << " 0" << std::endl;}
    
    ofile <<  "</users>\n";}

// Add a product t0]o cart
void MyDataStore::addToCart(const std::string& username, Product* product) {
    if (users_.find(username) != users_.end()) {
        userCarts_[username].push_back(product);
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}

// show what is isnide the cart
void MyDataStore::viewCart(const std::string& username) const {
    if (userCarts_.find(username) != userCarts_.end()) {
        const std::vector<Product*>& cart = userCarts_.find(username)->second;
        if (cart.empty()) {
            std::cout << "Cart is empty." << std::endl;
        } else {
            for (size_t i = 0; i < cart.size(); i++) {
                std::cout << "Item " << i + 1 << ":\n" << cart[i]->displayString() << "\n";
            }
        }
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}

// it should Process the purchase of items in the cart --
void MyDataStore::buyCart(const std::string& username) {
    if (userCarts_.find(username) != userCarts_.end()) {
        std::vector<Product*>& cart = userCarts_[username];
        User* user = users_[username];
        std::vector<Product*>::iterator it = cart.begin();
        while (it != cart.end()) {
            Product* product = *it;
            // Only purchase if product is in stock and user has enough balance
            if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
                product->subtractQty(1);
                user->deductAmount(product->getPrice());
                it = cart.erase(it); // Remove purchased item from cart
            } else {
                ++it;
            }
        }
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}
