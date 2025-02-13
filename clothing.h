#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include <iostream>
#include <string>

class Clothing : public Product {
    public:
        std::string size_;
        std::string brand_;
        
        Clothing(const std::string size, const std::string brand, const std::string category, const std::string name, const double price, const int qty);
        ~Clothing();

        virtual std::set<std::string> keywords() const;
        virtual std::string displayString() const;
        virtual void dump(std::ostream& os) const;
    
};
#endif