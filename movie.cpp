#include "util.h"
#include "movie.h"
#include <set>
#include <iostream>
using namespace std;

Movie::Movie(const string genre, const string rating, const string category, const string name, const double price, const int qty) : Product(category, name, price, qty) {
    genre_ = genre;
    rating_ = rating;
    category_ = category;
    name_ = name;
    price_ = price;
    qty_ = qty;
}
Movie::~Movie() {

}
std::set<std::string> Movie::keywords() const {
    //combines important stuff for the class
    string combined = this->genre_ + " " +  this->rating_ + " " + this->name_;
    std::set<std::string> keys;
    //get the keywords from the combined string formed
    keys = parseStringToWords(combined);
    return keys; 
}
std::string Movie::displayString() const {
    string display = this->name_ + "\nGenre: " + this->genre_ + " Rating: " + this->rating_ + "\n" + to_string(this->price_) + " " + to_string(this->qty_) + " left.";
    return display;
}
void Movie::dump(std::ostream& os) const {
    os << this->category_ << endl;
    os << this->name_ << endl;
    os << this->price_ << endl;
    os << this->qty_ << endl;
    os << this->genre_ << endl;
    os << this->rating_ << endl;
}