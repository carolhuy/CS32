#ifndef _SET_
#define _SET_
#include<string>
#include<iostream>

using ItemType = std::string;

class Set
{
private:
	//making a Node 
	struct Node {
		//Node constructor 
		Node(ItemType enter);

		//stores the value of Node
		ItemType value;

		//points to next Node
		Node* next;

		//points to previous Node
		Node* previous;
	};

	//number of elements in array
	int numElem;

	//points to last element of list 
	Node* tail; 

	//linked list to store values 
	//points to first element of list
	Node* head;


public:
	Set();         // Create an empty set (i.e., one with no items).

	//destructor
	~Set();
	
	//copy constructor
	Set(const Set& other);

	//assignment operator
	Set& operator=(const Set& rhs);

	bool empty() const;  // Return true if the set is empty, otherwise false.

	int size() const;    // Return the number of items in the set.

	bool insert(const ItemType& value);
	// Insert value into the set if it is not already present.  Return
	// true if the value is actually inserted.  Leave the set unchanged
	// and return false if the value was not inserted (perhaps because it
	// was already in the set or because the set has a fixed capacity and
	// is full).

	bool erase(const ItemType& value);
	// Remove the value from the set if it is present.  Return true if the
	// value was removed; otherwise, leave the set unchanged and
	// return false.

	bool contains(const ItemType& value) const;
	// Return true if the value is in the set, otherwise false.

	bool get(int i, ItemType& value) const;
	// If 0 <= i < size(), copy into value the item in the set that is
	// strictly greater than exactly i items in the set and return true.
	// Otherwise, leave value unchanged and return false.

	void swap(Set& other);
	// Exchange the contents of this set with the other one.
};

//NONMEMBER FUNCTIONS
void unite(const Set& s1, const Set& s2, Set& result);

void subtract(const Set& s1, const Set& s2, Set& result);
#endif