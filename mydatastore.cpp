#include "mydatastore.h"
#include "book.h"
#include "movie.h"
#include "clothing.h"
#include "util.h"
#include "datastore.h"
#include "product_parser.h"
#include "user.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

MyDataStore::MyDataStore() {

}
MyDataStore::~MyDataStore() {
    
}
void MyDataStore::addUser(User* u) {
    totalUsers.insert(u);
    userID.insert({u->getName(), u});
} 
void MyDataStore::addProduct(Product * p) {
    totalProducts.insert(p);
    keywords.insert({p->keywords(), p});
}

void MyDataStore::addCart(string user_, Product *p) {
    //check if user even exists in what we have
    if(userID.find(user_) != userID.end()) {
        cart[user_].push_back(p);
    } 
}
void MyDataStore::buyCart(string user_) {
    double totalCost;
    //check if user even exists
    if(userID.find(user_) != userID.end()) {
        vector<Product*> &userCart = cart[user_]; //creating a new variable for ease
        //looks through the items in the cart
        for(vector<Product*>::iterator it = userCart.begin(); it != userCart.end();) {
            totalCost = 0; 
            totalCost = totalCost + (*it)->getPrice();
            //check in the case that there is enough in stock and the user has enough money
            if((*it)->getQty() > 0 && userID[user_]->getBalance() >= totalCost) {
                userID[user_]->deductAmount(totalCost);
                (*it)->subtractQty(1);
                it = userCart.erase(it);
            } else ++it; //just move on to next if it was not the case
        }
    } 
}
void MyDataStore::viewCart(string user_) {
    int itemCount = 0;
    if(userID.find(user_) != userID.end()) {
        //assigning it to a new vector for ease
        vector<Product*> &userCart = cart[user_];
        for(vector<Product*>::iterator it = userCart.begin(); it != userCart.end(); ++it) {
            itemCount++;
            cout << "Item " << itemCount << endl;
            cout << (*it)->displayString() << endl;
        } 
    } 
}
vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    map<set<string>, Product*>::const_iterator it;
    vector<Product*> hits;
    set<string> results;
    set<string> termsAsSet(terms.begin(), terms.end());
    //check if AND 
    if(type == 0) {
        //iterate through the terms and keywords map
        for(it = keywords.begin(); it != keywords.end(); ++it) {
            //assign terms to one set so we can call setIntersection 
            set<string> productKeywords = it->first;
            results = setIntersection(productKeywords, termsAsSet);
            if(termsAsSet.size() == results.size())
                hits.push_back(it->second);
        }
    } else if(type == 1) { //check if OR
        for(it = keywords.begin(); it != keywords.end(); ++it) {
            //assign terms to one set so we can call setUnion 
            set<string> productKeywords = it->first;
            results = setUnion(productKeywords, termsAsSet);

            bool isCommon = false;
            //essentially checking to see if there are  common terms beteween the two sets
            for(set<string>::const_iterator itTerm = termsAsSet.begin(); itTerm != termsAsSet.end(); ++itTerm) {
                //check through productKeywords on termsAsSet for common words
                if(productKeywords.find(*itTerm) != productKeywords.end()) {
                    isCommon = true;
                    break;
                }
            }
            //if it exists, add it to hits
            if(isCommon) hits.push_back(it->second);              
        }
    } 
    //set finalHits to it so it can be used in amazon
    this->finalHits = hits;
    return hits;
}
void MyDataStore::dump(std::ostream& ofile){
    set<Product*>::iterator itProduct;
    set<User*>::iterator itUser;
    ofile << "<products>" << endl;
    for(itProduct = totalProducts.begin(); itProduct != totalProducts.end(); ++itProduct) {
        (*itProduct)->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for(itUser = totalUsers.begin(); itUser != totalUsers.end(); ++itUser) {
        (*itUser)->dump(ofile);
    }
    ofile << "</users>" << endl;
}
//to handle all valgrind errors
void MyDataStore::deallocate() {
    //deletes all products 
    for(set<Product*>::iterator itProduct = totalProducts.begin(); itProduct != totalProducts.end(); itProduct++) {
        delete (*itProduct);
    }
    //deletes all users
    for(set<User*>::iterator itUser = totalUsers.begin(); itUser != totalUsers.end(); itUser++) {
        delete (*itUser);
    }
}