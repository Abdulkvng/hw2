#include "movie.h"
#include "util.h"
#include <sstream>

// chasis for car.- book class is built on product

// intializer list for product


Movie::Movie(const std::string category, const std::string name, double price, int qty,
           const std::string genre, const std::string rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

std::set<std::string> Movie::keywords() const {

std::set<std::string>  keywords = parseStringToWords(name_ + " " + genre_);
return keywords;}

std::string Movie::displayString() const{
std::ostringstream oss;
  oss << name_ << '\n'
  << "Genre: " << genre_ << "Rating: " << rating_ << '\n'
  << price_ << " " << qty_ << " left.";
  return oss.str();
}
// underscore after is to show its from own memebr class
void Movie::dump(std::ostream& os) const{

  os << category_ << '\n'
  << name_ << '\n'
  << price_ << '\n'
  << qty_ << '\n'
  << genre_ << '\n'
  << rating_ << std::endl;
}