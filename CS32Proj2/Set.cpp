#include"Set.h"
#include<iostream>

//CONSTRUCTORS 
// Create an empty set (i.e., one with no items).
Set::Set():numElem(0){
	head = nullptr;
	tail = nullptr;
};         

//Constructor for Node
Set::Node::Node(ItemType v) {
	value = v;
	next = nullptr;
	previous = nullptr;
}


//Rewriting operators 
//destructor
Set::~Set() {
	Node* ptr = head;
	while (ptr!=nullptr) {
		if (ptr == tail) {
			delete tail;
			break;
		}
		ptr = ptr->next;
		delete ptr->previous;
	}
}

//copy constructor
//When a brand new Set is created as a copy of an existing Set, enough new nodes must be allocated to hold a duplicate of the original list.
Set::Set(const Set& other) {
	//COPY SIZE  
	numElem = other.numElem;

	//EMPTY SET
	if (other.empty() == true) {
		head = nullptr;
		tail = nullptr;
		return; 
	}

	//ONE ELEMENT LIST 
	if (other.head == other.tail) {
		head = new Node(other.head->value);
		tail = head;
		return;
	}

	//walker to traverse other LL
	//MORE THAN ONE ELEMENT
	Node* rhsPtr = other.head;
	Node* lhsPtr = nullptr; 
	while (rhsPtr != nullptr) {
		//HEAD POINTER
		if (rhsPtr == other.head) {
			head = new Node(other.head->value);
			head->previous = nullptr;
			lhsPtr = head;
			rhsPtr = rhsPtr->next;
		}
		//TAIL POINTER
		else if (rhsPtr==other.tail) {
			tail = new Node(rhsPtr->value);
			tail->previous = lhsPtr;
			tail->next = nullptr;
			lhsPtr->next = tail;
			break;
		}
		//MIDDLE 
		else {
			Node* tempPtr = new Node(rhsPtr->value);
			tempPtr->previous = lhsPtr;
			lhsPtr->next = tempPtr;
			lhsPtr = lhsPtr->next;
			rhsPtr = rhsPtr->next;
		}
	}
}

//assignment operator
/*When an existing Set (the left-hand side) is assigned the value of another Set (the right-hand side), 
the result must be that the left-hand side object is a duplicate of the right-hand side object, 
with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).*/
Set& Set::operator=(const Set& rhs) {
	if (this != &rhs) {
	// call CC to make a temporary copy of rhs - if CC correct this works 
	Set temp(rhs);
	//swap Sets so it has the data of rhs 
	swap(temp);
	}
	return *this;
}

//MEMBER FUNCTIONS 
// Return true if the set is empty, otherwise false.
bool Set::empty() const {
	if (numElem == 0) {
		return true;
	}
	else {
		return false;
	}
}

// Return the number of items in the set.
int Set::size() const {
	return numElem;
}  

bool Set::insert(const ItemType& value) {
	//Check if value is already in Set 
	if ((*this).contains(value) == true) {
		return false; 
	}

//IF value is not in the Set
	//CONDITION: If Set is empty, add element to Set
	if ((*this).empty() == true) {
		//creating a pointer to a new node
		Node* newNode= new Node(value);

		//making the head point to the node created
		head = newNode;

		//making tail point to node 
		tail = newNode; 

		//making sure the new node points to the head 
		newNode->previous = nullptr;

		//making sure the new node does not point to anything after 
		newNode->next = nullptr; 

		//increase the number of elements 
		++numElem;
		return true; 
	}

	//CONDITION: Set is non empty, want to link the elements by order 
	//create traversal ptr 
	Node* ptr = head; 

	//until reach end of LL (if insert in beginning or middle) 
	while (ptr!=nullptr) {
		if (value<ptr->value) {
			//if in the beginning of the list 
			if (ptr == head) {
				Node* newVal= new Node(value);
				newVal->next = head;
				newVal->previous = nullptr; 
				head->previous = newVal;
				head = newVal; 
				//increase size 
				++numElem; 
				return true; 
			}
			//insert in middle of list
			else {
				Node* newVal = new Node(value);
				newVal->previous = ptr->previous;
				newVal->next = ptr;
				ptr->previous->next = newVal;
				ptr->previous = newVal; 
				//increase size 
				++numElem;
				return true;
			}
		}
		//moving through LL and checking elements 
		else {
			//advance pointer to next item in LL 
			ptr = ptr->next;
		}
	}

	//If not empty, greater than all values in list, insert at the end of list 
	Node* tempPtr = new Node(value); 
	tempPtr->previous = tail; 
	tempPtr->next = nullptr; 
	tail->next = tempPtr; 
	tail = tempPtr; 
	++numElem;
	// Return true if the value is actually inserted. 
	return true; 
}

// Remove the value from the set if it is present.  Return true if the
// value was removed; 
bool Set::erase(const ItemType& value) {
//CHECK IF IN SET 
//If not in set, leave the set unchanged and return false.
if((*this).contains(value)==false){
	return false; 
}
//if one element set 
if (head == tail) {
	delete head;
	head = nullptr;
	tail = nullptr;
	--numElem;
	return true;
}
Node* ptr = head; 
while (ptr != nullptr) {
	//if at the beginning 
	if (ptr==head && ptr->value==value) {
		ptr->next->previous = nullptr;
		head = ptr->next;
		//get rid of memory 
		delete ptr; 
		//lower number of elements 
		--numElem;
		return true; 
	}
	//if at end 
	else if (ptr==tail && ptr->value==value) {
		tail = ptr->previous;
		tail->next = nullptr;
		delete ptr;
		--numElem;
		return true;
	}
	//if in middle 
	else {
		//if value matches 
		if (ptr->value == value) {
			ptr->next->previous = ptr->previous;
			ptr->previous->next = ptr->next; 
			delete ptr;
			--numElem;
			return true; 
		}
		else {
			//advance pointer 
			ptr = ptr->next; 
		}
	}
}
return false; 
}

// Return true if the value is in the set, otherwise false.
bool Set::contains(const ItemType& value) const {
	//check for empty list 
	if ((*this).empty() == true) {
		return false;
	}

	//Node pointer to traverse through LL
	Node* walker = head;

	//if not at end of list 
	while(walker!=nullptr){
		//if the value is found 
		if (walker->value == value) {
			return true;
		}
		//value not found and not at end 
		walker = walker->next; 
	}
	//if value not found and reach end
	return false; 
}


bool Set::get(int i, ItemType& value) const {

	//walker to traverse LL
	Node* ptr = head;

	// If 0 <= i < size(),
	if (i >= 0 && i < numElem){
		for (int j = 0; j < numElem; ++j) {
			//if this is the one want 
			if (j == i) {
				//copy into value the item in the set that is strictly greater than exactly i items in the set
				value = ptr->value;
				return true;
			}
			//advance pointer 
			else {
				ptr = ptr->next;
			}
		}
	}
	//for invalid size : if set is empty or i>=size, return false 
		value = value;
		return false;
}


// Exchange the contents of this set with the other one.
void Set::swap(Set& other) {
	//swapping the sizes 
	int store; 
	store = (*this).size();
	(*this).numElem = other.size();
	other.numElem = store;

	//swapping the linked lists 
	//HEAD
	Node* tempHead; 
	tempHead = (*this).head;
	(*this).head = other.head;
	other.head = tempHead;

	//TAIL 
	Node* tempTail = (*this).tail;
	(*this).tail = other.tail;
	other.tail = tempTail;
}

//NONMEMBER FUNCTIONS
void unite(const Set& s1, const Set& s2, Set& result) {
	Set newSet=s1;

	//add set 2 to set 1 - no duplicates because of insert function 
	for (int j = 0; j < s2.size(); ++j) {
		ItemType tempTwo;
		s2.get(j, tempTwo);
		newSet.insert(tempTwo);
	}
	result = newSet;
}

void subtract(const Set& s1, const Set& s2, Set& result) {
	Set subSet;
	//combine sets 
	unite(s1, s2, subSet);
	//remove elements of set 2 
	for (int i = 0; i < s2.size(); ++i) {
		ItemType toDel; 
		s2.get(i, toDel);
		if (subSet.contains(toDel)) {
			subSet.erase(toDel);
		}
	}
	result = subSet;
}
