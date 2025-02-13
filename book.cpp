#include "util.h"
#include "book.h"
#include <set>
#include <string>
#include <iostream>
using namespace std;

Book::Book(const string isbn, const string author, const string category, const string name, const double price, const int qty) : Product(category, name, price, qty) {
    isbn_ = isbn;
    author_ = author;
    category_ = category;
    name_ = name;
    price_ = price;
    qty_ = qty;
}
Book::~Book() {

}
std::set<std::string> Book::keywords() const {
    //combines important stuff for the class
    string combined = this->author_ + " " + this->name_;
    std::set<std::string> keys;
    //get the keywords from the combined string formed
    keys = parseStringToWords(combined);
    keys.insert(convToLower(this->isbn_));
    return keys; 
}
std::string Book::displayString() const {
    string display = this->name_ + "\nAuthor: " + this->author_ + " ISBN: " + this->isbn_ + "\n" + to_string(this->price_) + " " + to_string(this->qty_) + " left.";
    return display;
}
void Book::dump(std::ostream& os) const {
    os << this->category_ << endl;
    os << this->name_ << endl;
    os << this->price_ << endl;
    os << this->qty_ << endl;
    os << this->isbn_ << endl;
    os << this->author_ << endl;
}