#include "util.h"
#include "clothing.h"
#include <set>
#include <iostream>
using namespace std;

Clothing::Clothing(const string size, const string brand, const string category, const string name, const double price, const int qty) : Product(category, name, price, qty) {
    size_ = size;
    brand_ = brand;
    category_ = category;
    name_ = name;
    price_ = price;
    qty_ = qty;
}
Clothing::~Clothing() {

}
std::set<std::string> Clothing::keywords() const {
    //combines important stuff for the class
    string combined = this->size_ + " " +  this->brand_ + " " + this->name_;
    std::set<std::string> keys;
    //get the keywords from the combined string formed
    keys = parseStringToWords(combined);
    return keys; 
}
std::string Clothing::displayString() const {
    string display = this->name_ + "\nSize: " + this->size_ + " Brand: " + this->brand_ + "\n" + to_string(this->price_) + " " + to_string(this->qty_) + " left.";
    return display;
}
void Clothing::dump(std::ostream& os) const {
    os << this->category_ << endl;
    os << this->name_ << endl;
    os << this->price_ << endl;
    os << this->qty_ << endl;
    os << this->size_ << endl;
    os << this->brand_ << endl;
}