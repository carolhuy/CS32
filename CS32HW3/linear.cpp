/* your solution must not use the keywords while, for, or goto.
For this part of the homework, you will turn in one file named linear.cpp that contains the five functions and nothing more: 
no #include directives, no implementation of somePredicate and no main routine.

The first four take an array of strings and the number of strings to examine in the array; 
the last takes two arrays of strings and the number of strings to examine in each:
*/

//somePredicate on first 
//call a helper function on the rest of the array (aka countFalse)
//firstFalse 
//cimilar to countFalse 

// Return false if the somePredicate function returns true for at
// least one of the array elements; return true otherwise.
bool allFalse(const string a[], int n)
{ 
	//If any of the parameters n, n1, or n2 is negative, act as if it were zero. PROBLEM: (zero is base condition - what should return? false? ) 
	//checking if negative 
	if (n <= 0) {
		return true; 
	}
	//first to last approach - initialize at zero (first element)

	//call the function in the if statement to see if it returns true at one element 
	//examine the first element
	if (somePredicate(a[0])==true) {
		return false;
	}

	else {
		//checks the rest of the array 
		allFalse(a+1, n-1);
		}
	//base condition - if all are false 
	return true;
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	if (n == 0)
		return 0;

	if (somePredicate(a[0]) == false)
	{
		return 1 + countFalse(a + 1, n - 1);
	}
	else
	{
		return 0 + countFalse(a + 1, n - 1);
	}
}
// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.

//if this is the first element would this return 1 or 0? 
int firstFalse(const string a[], int n)
{
	//BASE CONDITION: n is negative or zero : no element returns false (or return 0?) 
	if (n <= 0) {
		return -1;
	}

	//BASE CONDITION: first element is false, return correct subscript  
	if (somePredicate(a[0]) == false) {
		return 0;
	}
	else {
		return 1 + firstFalse(a + 1, n - 1);
	}
}

// Return the subscript of the greatest string in the array (i.e.,
// the smallest subscript m such that a[m] >= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.
int locateMaximum(const string a[], int n)
{
	//BASE CONDITION: nothing to examine 
	if (n <= 0) {
		return -1;
	}

	//BASE CONDITION : if only have one string, return the string 
	if (n == 1) {
		return 0;
	}

	//BASE CONDITION: comparing two strings 
	if (a[0] >= a[n-1]) {
		return 0 + locateMaximum(a, n-1);
	}

	//compare rest of array, move position 
	return 1 + locateMaximum(a + 1, n - 1);
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"

//recursively compare the arrays, no need to call somePredicate 
bool contains(const string a1[], int n1, const string a2[], int n2)
{
	//BASE CONDITION: both arrays empty 
	if (n1 == 0 && n2 == 0) {
		return true;
	}

	//BASE CONDITION: only array one is empty 
	if (n1 == 0) {
		return false;
	}

	//BASE CONDITION: only array two is empty 
	if (n2 == 0) {
		return true;
	}

	//BASE CONDITION: the first strings are not the same 
	if (a1[0] != a2[0]) {
		//check the other strings in the first array 
		return contains(a1 + 1, n1 - 1, a2, n2);
	}
	//if strings are the same, then check the other strings 
	return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
}