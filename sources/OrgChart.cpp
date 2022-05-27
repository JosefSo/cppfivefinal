#include "OrgChart.hpp"
/* helped with https://www.geeksforgeeks.org/preorder-traversal-of-n-ary-tree-without-recursion/ 
   and https://www.geeksforgeeks.org/level-order-traversal-of-n-ary-tree/ code
*/
namespace ariel{
    // check funcs
    void noTree(node* root){
        if (root == nullptr){
            throw std::runtime_error("no tree");
        }
    }

    OrgChart::OrgChart(){
        std::cout<<"constructor\n";
        root = nullptr;
        itBegin = new myIter(root);
        counter = 0;
    }
    // OrgChart::~OrgChart(){
    //     std::cout << "\nde-structor"; 
    //     delete itBegin; // del myIter
    // }
    // OrgChart::OrgChart(const OrgChart &other){
    //     counter = other.nodes.size();
    //     for (unsigned long i = 0; i < other.nodes.size(); ++i) {
    //         nodes.push_back(new node(other.nodes.at(i)->data));
    //     }
    //     if(other.root == nullptr){
    //         root = nullptr;
    //     }
    //     else{
    //         root = nodes.at(0);
    //     }
    //     itBegin = new myIter(root);
    // }
    // OrgChart::OrgChart(OrgChart&& other){
    //     itBegin = other.itBegin;
    // }



    // Also need to add to queue and stack (What happens if we want to change the root? Need to clear all queue...)
    OrgChart &OrgChart::add_root(const string& boss){
        if (boss.empty()){
            throw std::runtime_error("empty name");
        }
        if (root == nullptr){
            // create new node
            root = new node;
        }
        ++counter;
        root->data = boss; 
        // add node to vector
        nodes.push_back(root);
        return *this;
    }
    // ADD_SUB
    OrgChart &OrgChart::add_sub(const string& boss, const string& employ){
        

        for (unsigned int i = 0; i < nodes.size(); i++){
            
            if (nodes.at(i)->data == boss){
                // create new employ node 
                node *newNode = new node;
                newNode->data = employ;
                // add (employ) to subs of the boss
                nodes.at(i)->sub_worker.push_back(newNode);
                // add to vector: nodes
                nodes.push_back(newNode);

                ++counter;
                return *this;
            }
        }
        throw std::runtime_error("Can't find boss");
    }

    // LEVEL ORDER
    myIter OrgChart::begin_level_order(){
        noTree(root);
        levelOrder();
        return *itBegin;
    }
    myIter OrgChart::end_level_order(){
        noTree(root);
        return nullptr;
    }

    // REVEERSE ORDER
    myIter OrgChart::begin_reverse_order(){
        noTree(root);
        levelOrdeReverse();
        return *itBegin;  
    }
    myIter OrgChart::reverse_order(){
        noTree(root);
        return nullptr;
    }

    // PRE-ORDER
    myIter OrgChart::begin_preorder(){
        noTree(root);
        traverse_tree();
        return *itBegin;
    }
    myIter OrgChart::end_preorder(){
        noTree(root);
        return nullptr;
    }

    // MUST WORK LIKE LEVEL-ORDER
    myIter OrgChart::begin(){
        return begin_level_order();
    }
    myIter OrgChart::end(){
        return end_level_order();
    }


    std::ostream & operator << (std::ostream &out, const OrgChart &Org){

        // help data
        vector<node*> temp;
        vector<vector<node*>> vectors;
        queue<node*> myQ;
        myQ.push(Org.root);
        

        while (!myQ.empty()){
            size_t size = myQ.size();

            for (size_t i = 0; i < size; i++){
                node *curr = myQ.front();
                myQ.pop();
                temp.push_back(curr);

                for (auto *u : curr->sub_worker) { myQ.push(u);}
            }
            vectors.push_back(temp);
            temp.clear();
        }
        for (auto const &v : vectors) {
            for (node* node : v){
                out << node->data << " ";
            }
        out << "\n";
        }
        return out;
    }

    /* -------------- help funcs ----------------- */

    // Function to traverse tree without recursion
    void OrgChart::traverse_tree()
    {

        // save the root into iterator
        itBegin->nd = root;
        node* temp = root;
        bool first = true;
        
        // Stack to store the nodes
        stack<node*> Nodes;
    
        // push the current node onto the stack
        Nodes.push(root);
        
        // loop while the stack is not empty
        while (!Nodes.empty()) {
    
            // store the current node and pop it from the stack
            node* curr = Nodes.top();
            Nodes.pop();
    
            // current node has been travarsed
            if(curr != NULL)
            {
                if (!first){
                    temp->next = curr;
                    temp = temp->next;
                }
                //std::cout << curr->data << " ";
        
                // store all the childrent of current node from
                // right to left.
                vector<node*>::iterator it = curr->sub_worker.end();
        
                while (it != curr->sub_worker.begin()) {
                    it--;
                    Nodes.push(*it);
                }
            }
            if(first) {first = false;}
        }
        temp->next = nullptr;
    }

    // Function for level order traversal for n-array tree
    void OrgChart::levelOrder()
    {
        vector<vector<node*> > ans;
        noTree(root);
            
        // save the root into iterator
        itBegin->nd = root;
        node *before_root = new node("before_root");
        before_root->next = root;
        node* neeDelete = before_root;
        
        bool first = true;

        // Create a queue namely main_queue
        queue<node*> main_queue;
    
        // Push the root value in the main_queue
        main_queue.push(root);
    
        // Create a temp vector to store the all the node values
        // present at a particular level
        vector <node*> temp;
    
        // Run a while loop until the main_queue is empty
        while (!main_queue.empty()) {
    
            // Get the front of the main_queue
            int n = main_queue.size();
    
            // Iterate through the current level
            for (int i = 0; i < n; i++) {
                node* cur = main_queue.front();
                main_queue.pop();
                temp.push_back(cur);
                for (auto *u : cur->sub_worker){
                    main_queue.push(u);
                }
            }
            //ans.push_back(temp);
            for (auto *v : temp){
                before_root->next = v;
                before_root = before_root->next;
            }
            
            temp.clear();
            if(first) {first = false;}
        }
        before_root->next = nullptr;
        delete neeDelete;
    }

    // Function for reverse level order traversal for n-array tree
    void OrgChart::levelOrdeReverse()
    {
        // save the root into iterator
        node *before_root = new node("before_root");
        before_root->next = root;
        node* neeDelete = before_root;

        // help data
        vector<node*> temp;
        vector<vector<node*>> vectors;
        queue<node*> myQ;
        myQ.push(root);
        

        while (!myQ.empty()){
            size_t size = myQ.size();

            for (size_t i = 0; i < size; i++){
                node *curr = myQ.front();
                myQ.pop();
                temp.push_back(curr);

                for (auto *u : curr->sub_worker) { myQ.push(u);}
            }
            vectors.push_back(temp);
            temp.clear();
        }
        for (unsigned int i = vectors.size()-1; i >= 1; i--){
            for(unsigned int j = 0; j < vectors.at(i).size(); ++j){
                // std::cout << vectors.at(i).at(j)->data << " ";
                before_root->next = vectors.at(i).at(j);
                before_root = before_root->next;
            }
        }
        before_root->next = root;
        before_root = before_root->next;

        before_root->next = nullptr;

        itBegin->nd = neeDelete->next;
        delete neeDelete;
    }
}

