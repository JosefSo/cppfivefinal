#pragma once
#include <iostream>
#include <vector>

using std::vector;
using std::string;

namespace ariel{

    class node{

    public:
        string data;
        vector<node*> sub_worker; // vector of sub workers
        node* next;

        node(){
            //this->data;
            this->next = NULL;
        }
        node(string name){
            this->data = std::move(name);
            this->next = NULL;
        }

    };
}