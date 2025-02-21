#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <set>
#include <string>


class Book : public Product {
  public:


  Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn);

std::set<std::string> keywords() const override;
std::string displayString() const override;
void dump(std::ostream& os) const override;


protected:
std::string author_;
std::string isbn_;
};

#endif