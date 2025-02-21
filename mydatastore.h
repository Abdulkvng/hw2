#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <set>
#include <vector>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p) override;

    // Add a user 
    void addUser(User* u) override;

    // Search for products (AND/OR)
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    // Save t
    void dump(std::ostream& ofile) override;

    //  helper functions for commands
    void addToCart(const std::string& username, Product* product);
    void viewCart(const std::string& username) const;
    void buyCart(const std::string& username);

private:
    // Data structures to store products and users
    std::vector<Product*> products_; // List of all products
    std::map<std::string, User*> users_; // Map of users by username
    std::map<std::string, std::set<Product*>> keywordIndex_; // Keyword to products mapping
    std::map<std::string, std::vector<Product*>> userCarts_; // User carts
};

#endif