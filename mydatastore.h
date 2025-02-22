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

    void addProduct(Product* p) ;

    // Add a user 
    void addUser(User* u) ;

    // Search for products (AND/OR)
    std::vector<Product*> search(std::vector<std::string> &terms, int type) override;

    // Save t
    void dump(std::ostream &ofile);
    

    std::vector<Product *> getProducts();
    std::vector<User *> getUsers();


    //  helper functions for commands
  void addToCart(std::string username, Product *p);
//add
//viewCart
    void viewCart( std::string username) ;
  void buyCart( std::string username);
    void removeCart(std::string username, Product *p);


private:
    // Data structures to store products and users
    std::vector<Product*> products_; // List of all products
    std::vector<User *> users_; // Map of users by username
    std::map<std::string, std::set<Product*>> keywordIndex_; // Keyword to products mapping
    std::map<std::string, std::vector<Product*>> userCarts_; // User carts
};

#endif