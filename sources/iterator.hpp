#include <iostream>
#include <string.h>
#include "node.hpp"

using std::string;

namespace ariel{

    class myIter{

    public:
        // data of my iterator
        node* nd;

        // default constructor
        myIter(){
            nd = nullptr;
        }
        // constructor
        myIter(node* root){
            nd = root;
        }

        // opreator of my iterator
        string* operator->() const {
            return &(nd->data);
        }

        string& operator*() const {
            return nd->data;
        }

        node* operator&() const {
            return nd;
        }

        bool operator==(const myIter& other) const {
            return nd == other.nd;
        }

        bool operator!=(const myIter& other) const {
            return nd != other.nd;
        }
        myIter& operator++() {
            nd = nd->next;
            return *this;
        }

        myIter operator++(int) {
            myIter tmp= *this;
            nd = nd->next;
            return tmp;
        }
    };
}
