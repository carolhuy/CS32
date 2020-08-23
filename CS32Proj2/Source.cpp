#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

//The tests were performed on a set of strings(i.e., ItemType was a type alias for std::string).

int main()
{
//Test Set functions 
	//default constructor for Set 
	Set ss;
	ItemType x;
	//For an empty set 
	assert(ss.size() == 0);        // test size
	assert(ss.empty());            // test empty
	assert(!ss.erase("roti"));     // nothing to remove
	assert(!ss.get(0, x));      //test empty, nothing to get-returns false 
	assert(!ss.get(-2, x));      //invalid position - returns false 
	assert(!ss.contains("roti")); //test empty, contains nothing - returns false

	//For a one element Set
	assert(ss.insert("pineapple")); //testing insert for one item 
	assert(!ss.empty());             //item added, Set not empty 
	assert(!ss.insert("pineapple"));   //insert already has object-returns false 
	assert(ss.size() == 1);      //test has one object 
	assert(ss.contains("pineapple"));  //test whether it contains 
	assert(!ss.contains("roti"));    //not part of Set-return false
	assert(ss.get(0, x));     //has one item to get 
	assert(!ss.get(1, x));    //invalid position for get 
	assert(x == "pineapple"); //checking it changed x correctly 
	assert(ss.erase("pineapple"));  //test erase 
	assert(!ss.erase("roti"));   //invalid value for erase

	//For Typical Set (>=2 items) 
	assert(ss.insert("Z"));  //inserting multiple objects at different positions
	assert(ss.insert("C"));
	assert(ss.insert("D"));
	assert(!ss.empty());    //objects inserted, Set not empty
	assert(ss.size() == 3);   //all items were properly inserted 
	assert(ss.contains("D"));   //test contains for object in middle of Set 
	assert(!ss.contains("E"));   //invalid value for contains
	assert(ss.get(0, x));                  //test that items were inserted by increasing order 
	assert(x == "C");
	assert(ss.get(1, x));
	assert(x == "D");
	assert(ss.get(2, x));
	assert(x == "Z");
	assert(ss.erase("D"));   //testing erase for middle object 
	assert(ss.size() == 2);
	assert(!ss.contains("D"));  //test to make sure item removed 

	//Testing swap - both empty 
	Set swapOne;
	Set swapTwo;
	swapOne.swap(swapTwo);
	assert(swapOne.empty() && swapTwo.empty()); //both sets empty 

	//Testing swap - one empty Set 
	//swapOne is still empty 
	swapTwo.insert("A");
	swapTwo.insert("B");
	swapTwo.insert("C");
	swapOne.swap(swapTwo);
	assert(swapOne.size() == 3 && swapTwo.empty());  //test that sizes were swapped correctly
	assert(swapOne.get(0, x) && x == "A");      //swapOne now has items
	assert(!swapTwo.get(0, x));                //swapTwo is now empty

	//Testing swap - both non empty Set
	ItemType testOne, testTwo;
	swapTwo.insert("1");
	swapTwo.insert("3");
	swapTwo.insert("2");
	swapTwo.insert("4");
	swapOne.swap(swapTwo);
	assert(swapOne.size() == 4 && swapTwo.size() == 3);  //test that sizes swapped correctly
	assert(swapOne.get(0, testOne) && swapTwo.get(0, testTwo)); //test that objects swapped correctly 
	assert(testOne == "1" && testTwo == "A");

	//Copy Constructor 
	//empty set
	Set empty;
	Set CCempty(empty);
	assert(CCempty.empty());

	//typical case 
	Set CC(ss);
	assert(CC.size() == 2);
	ItemType CCTest;
	assert(CC.get(0, CCTest));
	assert(CCTest == "C");

	//Assignment Operator 
	//empty set 
	Set AOempty;
	empty = AOempty;

	//typical case 
	AOempty = CC;
	assert(AOempty.size() == 2);
	ItemType AOtest;
	assert(AOempty.get(0, AOtest));
	assert(AOtest == "C");

//Test Nonmember Function - Unite 
	Set uniteSetOne;
	Set uniteSetTwo;
	Set result;
	//all sets empty 
	unite(uniteSetOne, uniteSetTwo, result);

	//three different sets , result empty 
	Set resultEmpty;
	uniteSetOne.insert("10");
	uniteSetOne.insert("20");
	uniteSetTwo.insert("A");
	uniteSetTwo.insert("B");
	uniteSetTwo.insert("C");
	unite(uniteSetOne, uniteSetTwo, resultEmpty);
	assert(resultEmpty.size() == 5);   //testing to see all items added 

	//three different set, result initially not empty 
	result.insert("notEmpty");
	unite(uniteSetOne, uniteSetTwo, result);
	assert(result.size() == 5);    //testing to make sure result only added the two Sets
	ItemType uniteTest;
	assert(result.get(0, uniteTest));
	assert(uniteTest == "10");
	assert(!result.contains("notEmpty"));

	//tests for duplicates 
	uniteSetOne.erase("10");
	uniteSetOne.insert("A");
	unite(uniteSetOne, uniteSetTwo, result);
	assert(result.size() == 4);  //testing to see if duplicate added 
	assert(result.get(0, uniteTest));
	assert(uniteTest == "20");

	//s1=result 
	unite(uniteSetOne, uniteSetTwo, uniteSetOne);
	assert(uniteSetOne.size() == 4);
	assert(uniteSetOne.get(1, uniteTest));
	assert(uniteTest == "A");

	//s2=result
	unite(uniteSetOne, uniteSetTwo, uniteSetTwo);
	assert(uniteSetTwo.size() == 4);
	assert(uniteSetOne.get(2, uniteTest));
	assert(uniteTest == "B");

	//s1=s2
	unite(uniteSetOne, uniteSetOne, result);
	assert(result.size() == 4);
	assert(uniteSetOne.get(2, uniteTest));
	assert(uniteTest == "B");

	//s1=s2=result 
	unite(result, result, result);
	assert(result.size() == 4);
	assert(result.get(2, uniteTest));
	assert(uniteTest == "B");

//Test Nonmember Function - Subtract 
	//all sets empty
	Set subOne;
	Set subTwo; 
	Set subEmpty; 
	subtract(subOne, subTwo, subEmpty);
	assert(subEmpty.size() == 0);

	//typical set - three different Sets, result empty 
	ItemType subTest;
	subOne.insert("carly"); //inserting values into the sets
	subOne.insert("jason");
	subOne.insert("kriti");
	subTwo.insert("carly");
	subTwo.insert("kriti");
	subTwo.insert("taylor");
	subtract(subOne, subTwo, subEmpty); //testing subtract 
	assert(subEmpty.get(0, subTest));
	assert(subTest == "jason");       //checking value of result after subtracting  
	assert(!subEmpty.get(1, subTest)); //checking if any improper values 

	//three different sets-result not empty initially
	subEmpty.insert("swift");
	subtract(subOne, subTwo, subEmpty); //testing subtract with something in result 
	assert(subEmpty.get(0, subTest));
	assert(subTest == "jason");       //checking value of result after subtracting  
	assert(!subEmpty.get(1, subTest)); //checking if any improper values 

	//s1=result 
	subtract(subOne, subTwo, subOne);
	assert(subOne.get(0, subTest));
	assert(subTest == "jason");

	//s2=result
	subTwo.insert("jason");
	subtract(subTwo, subOne, subTwo);
	assert(subTwo.get(1, subTest));
	assert(subTest == "kriti");

	//s1=s2
	subtract(subOne, subOne, subEmpty); 
	assert(subEmpty.empty());

	//s1=s2=result 
	subtract(subTwo, subTwo, subTwo);
	assert(subTwo.empty());

	cout << "Passed all tests" << endl;
}
