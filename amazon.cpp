#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "datastore.h"
#include "mydatastore.h"
using namespace std;

struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0); 
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if(cmd == "VIEWCART") {
                string username_;
                if(ss >> username_) {
                    //check to see if the username exists
                    if(ds.userID.find(username_) != ds.userID.end()) 
                        ds.viewCart(username_);
                     else cout << "Invalid username" << endl;
                    
                } else cout << "Invalid username" << endl;
            }
            else if(cmd == "BUYCART") {
                string username_;
                if(ss >> username_) {
                    //check to see if the username exists
                    if(ds.userID.find(username_) != ds.userID.end()) 
                        ds.buyCart(username_);
                    else cout << "Invalid username" << endl; 
                } else cout << "Invalid username" << endl;
            } 
            else if(cmd == "ADD") {
                 string username_;
                 int hitNumber;
                 if(ss >> username_) {
                    //check to see if the username exists
                    if(ds.userID.find(username_) != ds.userID.end()) {
                        if(ss >> hitNumber) {
                            //subtract by 1 since the value is probably stored in one less 
                            //if someone types 1, it would be stored as 0
                            hitNumber = hitNumber - 1;
                            //check if hit number is even valid
                            if(hitNumber < ds.finalHits.size()) 
                                ds.addCart(username_, ds.finalHits[hitNumber]);
                        } else cout << "Invalid request" << endl;
                    } else cout << "Invalid request" << endl;
                 } else cout << "Invalid request" << endl;
            }  
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    //to deal with valgrind errors
    ds.deallocate();
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
