#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <iostream>
#include <string>

class Book : public Product {
    public:
        std::string author_;
        std::string isbn_;
        
        Book(const std::string isbn, const std::string author, const std::string category, const std::string name, const double price, const int qty);
        ~Book();

        virtual std::set<std::string> keywords() const;
        virtual std::string displayString() const;
        virtual void dump(std::ostream& os) const;
    
};
#endif