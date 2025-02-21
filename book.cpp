#include "book.h"
#include "util.h"
#include <sstream>

  Book::Book(const std::string category, const std::string name, double price, int qty,
           const std::string author, const std::string isbn)
    : Product(category, name, price, qty), author_(author), isbn_(isbn) {}
// chasis for car.- book class is built on product

// intializer list for product

std::set<std::string> Book::keywords() const {

std::set<std::string>  keywords = parseStringToWords(name_ + " " + author_);
keywords.insert(isbn_);
return keywords;}

std::string Book::displayString() const{
  std::ostringstream oss;
  oss << name_ << '\n'
  << "Author: " << author_ << "ISBN: " << isbn_ << '\n'
  << price_ << " " << qty_ << " left.";
  return oss.str();
}
// underscore after is to show its from own memebr class
void Book::dump(std::ostream& os) const{

  os << category_ << '\n'
  << name_ << '\n'
  << price_ << '\n'
  << qty_ << '\n'
  << isbn_ << '\n'
  << author_ << std::endl;
}