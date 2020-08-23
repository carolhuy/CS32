#include"Set.h"
#include<iostream>

Set::Set():numElem(0){}         // Create an empty set (i.e., one with no items).

bool Set::empty() const{
	// Return true if the set is empty,
	if (numElem==0) {
		return true;
	}
	//otherwise false.
	return false;
}

int Set::size() const{
	// Return the number of items in the set.
	return numElem;
}    

// Insert value into the set if it is not already present.
bool Set::insert(const ItemType& value){
	//First, check if can insert another value 
	if (numElem >= DEFAULT_MAX_ITEMS) {
		//return false if set has a fixed capacity and is full
		return false; 
	}

	//IF NOT FULL, see if value is present in the set   
	//checking each value stored 
	for (int i = 0; i < numElem; ++i) {
		//if value is present
		if (arr[i] == value) {
			//do not change array size since not added 
			numElem = numElem;
			//return false if the value already in the set
			return false; 
		}
	}
//if value not found in the array, then add to array
//INSERTING INTO ARRAY ALPHABETICALLY

	//increase array size 
	++numElem;

	//if there is nothing currently in numElem, add the first element 
	if (numElem == 1) {
		arr[0] = value;
		//Return true if the value is actually inserted.  
		return true;
	}

	//if not the first element 
	else {
		//FIND POSITION OF WHERE TO INSERT 
		//traverse the list 
		for (int j = 0; j < numElem-1; ++j) {
			//if smallest value 
			if (value<arr[j]) {
				for (int k=numElem-1; k >0 ;--k) {
					//move everything to right 
					arr[k] = arr[k-1];
			}
				arr[0] = value;
				break;
			}
			//if in between values, then insert at j and move everything to right 
			else if (value>=arr[j] && value<arr[j+1]) {
				for (int g = numElem-1; g > j+1;--g) {
					arr[g] = arr[g - 1];
				}
				arr[j+1] = value;
				break;
			}
			//if the highest value, then insert at end 
			else {
				arr[numElem - 1] = value;
				break;
			}
		}
		return true;
	} 
}

// Remove the value from the set if it is present.
bool Set::erase(const ItemType& value){
//CHECK IF PRESENT 
	//get position of element want to remove
	int remPos = 0; 

	//traversing through array 
	for (int i = 0; i < numElem; ++i) {
		//if not match value
		if (arr[i] != value) {
			++remPos;
		}
		else {
			//if is value 
			remPos = remPos;
			break;
		}
	}
	//NOT PRESENT 
	if (remPos == numElem) {
		return false;
	}

//PRESENT, THEN DELETE FROM ARRAY
//DELETING FROM ARRAY
	//CASE 1: if at the end of the array 
	else if (remPos==numElem-1) {
		//decrement size
		--numElem;
		// Return true if the value was removed; 
		return true; 
	}
	//CASE 2: not at the end of array 
	else {
		//decrement size
		--numElem;
		//Shift everything to the left of the spot 
		for (int j = remPos; j < numElem; ++j) {
			arr[j] = arr[j+1];
		}
		// Return true if the value was removed; 
		return true;
	}
}


bool Set::contains(const ItemType& value) const{
	//if empty 
	if (numElem==0) {
		return false; 
	}
	
	//Traverse through array 
	for (int i = 0; i < numElem; ++i) {
		//if find value 
		if (arr[i] == value) {
			// Return true if the value is in the set
			return true;
		}
	}
	//otherwise false.
	return false;
}

bool Set::get(int i, ItemType& value) const{
	// If 0 <= i < size()
	if (i >= 0 && i < numElem) {
		// copy into value the item in the set that is strictly greater than exactly i items in the set 
		value = arr[i];
		// then return true.
		return true;
	}
	 
	//if i is greater than the number of items in the set
		//leave value unchanged and return false
	else {
		value = value;
		return false;
	}
}

// Exchange the contents of this set with the other one.
void Set::swap(Set& other){
	//temporary variable to store object 
	ItemType temp;

	//temp variable to store size 
	int size; 

	//biggest size 
	int biggest;

	//if the same Set
	if (&other == this) {
		return;
	}

	//finding out which is bigger
	if ((*this).numElem > other.numElem) {
		biggest = (*this).numElem;
	}
	else {
		biggest = other.numElem;
	}

	//SWAPPING THE SIZES 
	size = (*this).numElem;
	(*this).numElem = other.numElem;
	other.numElem = size;

	//SWAPPING THE OBJECTS
	for (int i = 0; i < biggest; ++i) {
		temp = (*this).arr[i];
		(*this).arr[i] = other.arr[i];
		other.arr[i] = temp;
	}
}