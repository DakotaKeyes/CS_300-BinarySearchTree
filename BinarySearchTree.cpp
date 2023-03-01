//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Dakota Keyes
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node* left; // pointer for values < parent
    Node* right; // pointer for values > parent

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Custom constructor with a bid param
    Node(Bid t_bid) : Node() { // calls default constructor
        this->bid = t_bid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // Initialize housekeeping variable
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // Call private method that contains the logic
    this->inOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    if (root == nullptr) {
        root = new Node(bid);
    }
    else {
        this->addNode(root, bid);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // Call private method that contains the logic
    this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {

    Node* current = root;

    while (current != nullptr) {
        // If current node matches, return it
        if (current->bid.bidId.compare(bidId) == 0) {
            return current->bid;
        }
        // If bid is smaller, traverse left subtree
        if (bidId.compare(current->bid.bidId) < 0) {
            current = current->left;
        }
        // traverse right subtree
        else {
            current = current->right;
        }
    }

    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {

    // If node > bid, add to left subtree
    if (node->bid.bidId.compare(bid.bidId) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }
        // If left node exists, keep traversing down left subtree
        else {
            this->addNode(node->left, bid);
        }
    }
    // If node < bid, add to right subtree
    else {
        if (node->right == nullptr) {
            node->right = new Node(bid);
        }
        // If right node exists, keep traversing down right subtree
        else {
            this->addNode(node->right, bid);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {

    if (node != nullptr) {

        inOrder(node->left); // Traverse left side first

        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
            << node->bid.fund << endl;

        inOrder(node->right); // Traverse right side after each level's been checked
    }
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {

    if (node == nullptr) {
        return node;
    }

    if (bidId.compare(node->bid.bidId) < 0) {
        node->left = removeNode(node->left, bidId);
    }
    else if (bidId.compare(node->bid.bidId) > 0) {
        node->right = removeNode(node->right, bidId);
    }
    else {
        // no kids
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // one child, left kid
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        // one child, right kid
        else if (node->left == nullptr && node->right != nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // two children
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->bid = temp->bid;
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }
    return node;

}

 //============================================================================
 // Static methods used for testing
 //============================================================================

 /**
  * Display the bid information to the console (std::out)
  *
  * @param bid struct containing the bid info
  */
 void displayBid(Bid bid) {
     cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
         << bid.fund << endl;
     return;
 }

 /**
  * Load a CSV file containing bids into a container
  *
  * @param csvPath the path to the CSV file to load
  * @return a container holding all the bids read
  */
 void loadBids(string csvPath, BinarySearchTree * bst) {
     cout << "Loading CSV file " << csvPath << endl;

     // initialize the CSV Parser using the given path
     csv::Parser file = csv::Parser(csvPath);

     // read and display header row - optional
     vector<string> header = file.getHeader();
     for (auto const& c : header) {
         cout << c << " | ";
     }
     cout << "" << endl;

     try {
         // loop to read rows of a CSV file
         for (unsigned int i = 0; i < file.rowCount(); i++) {

             // Create a data structure and add to the collection of bids
             Bid bid;
             bid.bidId = file[i][1];
             bid.title = file[i][0];
             bid.fund = file[i][8];
             bid.amount = strToDouble(file[i][4], '$');

             //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

             // push this bid to the end
             bst->Insert(bid);
         }
     }
     catch (csv::Error& e) {
         std::cerr << e.what() << std::endl;
     }
 }

 /**
  * Simple C function to convert a string to a double
  * after stripping out unwanted char
  *
  * credit: http://stackoverflow.com/a/24875936
  *
  * @param ch The character to strip out
  */
 double strToDouble(string str, char ch) {
     str.erase(remove(str.begin(), str.end(), ch), str.end());
     return atof(str.c_str());
 }

 /**
  * The one and only main() method
  */
 int main(int argc, char* argv[]) {

     // process command line arguments
     string csvPath, bidKey;
     switch (argc) {
     case 2:
         csvPath = argv[1];
         bidKey = "98109";
         break;
     case 3:
         csvPath = argv[1];
         bidKey = argv[2];
         break;
     default:
         csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
         bidKey = "98109";
     }

     // Define a timer variable
     clock_t ticks;

     // Define a binary search tree to hold all bids
     BinarySearchTree* bst;
     bst = new BinarySearchTree();
     Bid bid;

     int choice = 0;
     while (choice != 9) {
         cout << "Menu:" << endl;
         cout << "  1. Load Bids" << endl;
         cout << "  2. Display All Bids" << endl;
         cout << "  3. Find Bid" << endl;
         cout << "  4. Remove Bid" << endl;
         cout << "  9. Exit" << endl;
         cout << "Enter choice: ";
         cin >> choice;

         switch (choice) {

         case 1:

             // Initialize a timer variable before loading bids
             ticks = clock();

             // Complete the method call to load the bids
             loadBids(csvPath, bst);

             //cout << bst->Size() << " bids read" << endl;

             // Calculate elapsed time and display result
             ticks = clock() - ticks; // current clock ticks minus starting clock ticks
             cout << "time: " << ticks << " clock ticks" << endl;
             cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
             break;

         case 2:
             bst->InOrder();
             break;

         case 3:
             ticks = clock();

             bid = bst->Search(bidKey);

             ticks = clock() - ticks; // current clock ticks minus starting clock ticks

             if (!bid.bidId.empty()) {
                 displayBid(bid);
             }
             else {
                 cout << "Bid Id " << bidKey << " not found." << endl;
             }

             cout << "time: " << ticks << " clock ticks" << endl;
             cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

             break;

         case 4:
             bst->Remove(bidKey);
             break;
         }
     }

     cout << "Good bye." << endl;

     return 0;
 }
