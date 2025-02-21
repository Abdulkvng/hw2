#include "clothing.h"
#include "util.h"
#include <sstream>


Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
           const std::string size, const std::string brand)
    : Product(category, name, price, qty), size_(size), brand_(brand) {}


// chasis for car.- book class is built on product

// intializer list for product

std::set<std::string> Clothing::keywords() const {

std::set<std::string>  keywords = parseStringToWords(name_ + " " + brand_);
return keywords;}

std::string Clothing::displayString() const{
  std::ostringstream oss;
  oss << name_ << '\n'
  << "Size: " << size_ << "Brand: " << brand_ << '\n'
  << price_ << " " << qty_ << " left.";
  return oss.str();
}
// underscore after is to show its from own memebr class
void Clothing::dump(std::ostream& os) const{

  os << category_ << '\n'
  << name_ << '\n'
  << price_ << '\n'
  << qty_ << '\n'
  << size_ << '\n'
  << brand_ << std::endl;
}