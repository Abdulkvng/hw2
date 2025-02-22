#include <iostream>
#include <set>
#include <vector>
#include <string>
#include "mydatastore.h"
#include "util.h"
MyDataStore::MyDataStore(){}
MyDataStore::~MyDataStore()
{for (unsigned int i = 0; i < products_.size(); i++)
    {delete products_[i];
    }
    for (unsigned int i = 0; i < users_.size(); i++)
    {delete users_[i];}}

void MyDataStore::addProduct(Product *p)
//add product or item
{
    products_.push_back(p);
    std::set<std::string> keywords = p->keywords();
    for (const std::string &keyword : keywords)
    {std::string lowerKeyword = convToLower(keyword);
        keywordIndex_[lowerKeyword].insert(p);}
}

void MyDataStore::addUser(User *u)
{users_.push_back(u);}
//add user

std::vector<Product *> MyDataStore::getProducts()
{return products_;}

std::vector<User *> MyDataStore::getUsers()
{return users_;}
//void MyDataStore::addToCart(std::string username, Product p)
void MyDataStore::addToCart(std::string username, Product *p)
{
    User *user = nullptr;
    for (User *u : users_)
    {
        if (u->getName() == username)
        {user = u;
            break;} }

    if (user == nullptr)
    {std::cout << "Invalid request" << std::endl;
        return;}
    userCarts_[username].push_back(p);
}

void MyDataStore::viewCart(std::string username)
{User *user = nullptr;
for (User *u : users_)
    { if (u->getName() == username)
        {user = u;break;} }
    if (user == nullptr)
    {std::cout << "Invalid username" << std::endl;return;
    }

    std::vector<Product *> cart = userCarts_[username];
    for (unsigned int i = 0; i < cart.size(); i++)
    {
        std::cout << "Item: " << i + 1 << std::endl;
        std::cout << cart[i]->displayString() << std::endl;
    }
}

void MyDataStore::buyCart(std::string username)
{User *user = nullptr;
    for (User *u : users_)
    {if (u->getName() == username) {user = u;break;}
    }

    if (user == nullptr)
    { std::cout << "Invalid username" << std::endl;
  return;
    }

    std::vector<Product *> &cart = userCarts_[username];
    std::vector<User *>::iterator userIt = std::find_if(users_.begin(), users_.end(), [&username](User *u)
                                                        { return u->getName() == username; });
    user = *userIt;
    double balance = user->getBalance();

    std::vector<Product *>::iterator it = cart.begin();
    while (it != cart.end())
    {
        Product *product = *it;
        if (product->getQty() > 0 && balance >= product->getPrice())
        {product->subtractQty(1);
            user->deductAmount(product->getPrice());
            balance -= product->getPrice();
            it = cart.erase(it);}
        else{++it;}}
}

void MyDataStore::removeCart(std::string username, Product *p)
{
    User *user = nullptr;
    for (User *u : users_)
    { if (u->getName() == username)
        {  user = u; break;}
    }
//remove if null, show error 
// changed from map to vector
    if (user == nullptr)
    { std::cout << "Error: User '" << username << "' not found." << std::endl;
       return;
    }

    std::vector<Product *> cart = userCarts_[username];
    for (unsigned int i = 0; i < cart.size(); i++)
    { if (cart[i] == p)
        {    cart.erase(cart.begin() + i);    break;}
 }
}

std::vector<Product *> MyDataStore::search(std::vector<std::string> &terms, int type)
{
    std::set<Product *> hits;
    std::set<Product *> temp;
    std::set<std::string> keywords;
    for (size_t i = 0; i < terms.size(); i++)
    {
        std::string term = terms[i];
        std::transform(term.begin(), term.end(), term.begin(), ::tolower);
        if (keywordIndex_.find(term) != keywordIndex_.end())
        {
            temp = keywordIndex_[term];
            if (i == 0)
            {  hits = temp; }
            else { if (type == 0) {
                 hits = setIntersection(hits, temp); }
                else
                {       hits = setUnion(hits, temp); }}}
    }
    std::vector<Product *> hitsVec;
    for (std::set<Product *>::iterator it = hits.begin(); it != hits.end(); ++it)
    { hitsVec.push_back(*it);
    }
    return hitsVec;
}

void MyDataStore::dump(std::ostream &ofile)
{
    ofile << "<products>" << std::endl;
    for (unsigned int i = 0; i < products_.size(); i++)
    {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    for (unsigned int i = 0; i < users_.size(); i++)
    {
        users_[i]->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}
