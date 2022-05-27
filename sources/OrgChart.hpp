#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "iterator.hpp"
#include "node.hpp"
#include <list>

using std::string;
using std::vector;

using std::queue;
using std::stack;
using std::ostream;

namespace ariel{



    class OrgChart{
        private:
            myIter* itBegin;
            node* root;
            vector<node*> nodes;

            // node* levelorder;
            // node* reverseorder;
            // node* preorder;
            // node* preorder_root;

            // std::list <node*> levelorder;
            // std::list <node*> reverseorder;
            // std::list <node*> preorder;

            int counter;

        public:
            // constructor
            OrgChart();
            // de-structor
            // ~OrgChart();
            // // copy constructor
            // OrgChart(const OrgChart &other);
            // // move constructor
            // OrgChart(OrgChart&& other);

            OrgChart &add_root(const string& boss); //& - for:  organization.add_root("CEO").add_sub("CEO", "CTO")      
            OrgChart &add_sub(const string& boss, const string& employ);

            //input, output operators
            friend std::ostream & operator << (std::ostream &out, const OrgChart &Org); //friend func to access private & protected members
            
            myIter begin_level_order();
            myIter end_level_order();

            myIter begin_reverse_order();
            myIter reverse_order();

            myIter begin_preorder();
            myIter end_preorder();
            
            // default iterators
            myIter begin();
            myIter end();



            // help funcs
            void traverse_tree();
            void levelOrder();
            void levelOrdeReverse();
            
            
    };
}