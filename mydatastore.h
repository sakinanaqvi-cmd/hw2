#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "util.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

class MyDataStore : public DataStore {
    public:
        MyDataStore();
        ~MyDataStore();
        void addProduct(Product* p);
        void addUser(User* u);
        void addCart(std::string user_, Product *p);
        void buyCart(std::string user_);
        void viewCart(std::string user_);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);
        void deallocate();

        std::vector<Product*> finalHits;
        std::string user_;
        std::map<std::string, std::vector<Product *>> cart;
        std::set<Product*> totalProducts;
        std::set<User*> totalUsers;
        std::map<std::string, User*> userID;
        std::map<std::set<std::string>, Product*> keywords;



};
#endif