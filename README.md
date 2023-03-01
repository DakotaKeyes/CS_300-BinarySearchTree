Requirements & Rubric

# CS_300-BinarySearchTree
CS_300 Binary Search Tree pseudocode and cpp 

Overview
GitHub

eBid_Monthly_Sales.csv (larger set of 12,023 bids)
eBid_Monthly_Sales_Dec_2016.csv (smaller set of 76 bids)
This assignment is designed to explore linked lists, so you will implement a singly linked list to hold a collection of bids loaded from a CSV file. We provide a starter console program that uses a menu to enable testing of the hash table logic you will complete. It also allows you to pass in the path to the bids CSV file to be loaded, enabling you to try both files. In this version, the following menu is presented when the program is run:

# Menu:

Load Bids
Display All Bids
Find Bid
Remove Bid
Exit
Enter choice:

The BinarySearchTree.cpp program is partially completed. It contains empty methods representing the programming interface used to interact with a binary search tree. You will need to add logic to the methods to implement the necessary behavior. Here is the public API for BinarySearchTree.cpp that you have to complete:

public:

BinarySearchTree();
virtual ~BinarySearchTree();
void Insert(Bid bid);
void Remove(string bidId);
Bid Search(string bidId);

Prompt
You will need to perform the following steps to complete this activity:

Setup: Begin by creating a new C++ project with a project type of "Hello World C++ Project".

---------------------------------------------------------------------------------------------------------------------------
***Task 1: Define structures for tree node and housekeeping variables.

Task 2: Implement inserting a bid into the tree.

Task 3: Implement removing a bid from the tree.

Task 4: Implement searching the tree for a bid.

Task 5: Complete the function to display all bids. Note that you may be able to reuse a portion of your code from a previous assignment to save you time. Look for where you have used a Node structure to implement a linked list.***
---------------------------------------------------------------------------------------------------------------------------

Here is sample output from running the completed program:

> ./BinarySearchTree ~/Downloads/eBid_Monthly_Sales.csv
> BinarySearchTree.exe Downloads\eBid_Monthly_Sales.csv

Load bids from CSV and display the hash table contents:

Example Input	Choice: 1	Choice: 43
Display	Menu:
1. Load Bids
2. Display All Bids
3. Find Bid
4. Remove Bid
9. Exit
Enter choice: 1	Menu:
1. Load Bids
2. Display All Bids
3. Find Bid
4. Remove Bid
9. Exit
Enter choice: 3
Output	
Loading CSV file eBid_Monthly_Sales.csv
12,023 bids read
time: 6795773 clock ticks
time: 6.79577 seconds

98129: Printer | 52.00 | Enterprise
time: 183 clock ticks
time: 0.000183 seconds
Note that it took only 183 clock ticks to search over 12,000 records in a binary tree.
