#include <iostream>
#include <algorithm>
#include <numeric>  // for std::accumulate
#include <utility>
#include <vector>
#include <string>
#include <random>
#include <cassert>

//Implement the insertion_sort function using pseudocode 
//Implement the compareStorePtr function and the code in main to create and sort the array of pointers.

using namespace std;

//========================================================================
//  Set this to false to skip the insertion sort tests; you'd do this if
//  you're sorting so many items that insertion_sort would take more time
//  than you're willing to wait.

const bool TEST_INSERTION_SORT = true;

//========================================================================

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif

#include <chrono>

class Timer
{
public:
	Timer()
	{
		start();
	}
	void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	}
	double elapsed() const
	{
		std::chrono::duration<double, std::milli> diff =
			std::chrono::high_resolution_clock::now() - m_time;
		return diff.count();
	}
private:
	std::chrono::high_resolution_clock::time_point m_time;
};

//========================================================================

// These are used for random number generation

std::random_device aRandomDevice;
std::default_random_engine generator(aRandomDevice());

// Here's a class that is not cheap to copy because the objects contain a
// large array.

// We'll simplify writing our timing tests by declaring everything public
// in this class.  (We wouldn't make data public in a class intended for
// wider use.)

using IdType = int;

const int NWEEKS = 4 * 52;

struct Store
{
	IdType id;
	double total;
	double weeklySales[NWEEKS];
	Store(IdType i) : id(i)
	{
		std::uniform_int_distribution<> distro(20, 60);

		// create random sales figures (from 20 to 60)
		for (size_t k = 0; k < NWEEKS; k++)
			weeklySales[k] = distro(generator);
		// (accumulate computes 0.0 + weeklySales[0] + weeklySales[1] + ...)
		total = accumulate(weeklySales, weeklySales + NWEEKS, 0.0);
	}
};

inline
bool compareStore(const Store& lhs, const Store& rhs)
{
	// The Store with the higher total should come first.  If they have
	// the same total, then the Store with the smaller id number should
	// come first.  Return true iff lhs should come first.  Notice that
	// this means that a false return means EITHER that rhs should come
	// first, or there's a tie, so we don't care which comes first,

	if (lhs.total > rhs.total)
		return true;
	if (lhs.total < rhs.total)
		return false;
	return lhs.id < rhs.id;
}

inline
bool compareStorePtr(const Store* lhs, const Store* rhs)
{
	// TODO: You implement this.  Using the same criteria as compareStore,
	//       compare two Stores POINTED TO by lhs and rhs.  Think about
	//       how you can do it in one line by calling compareStore.
	return (compareStore(*lhs, *rhs));
}

void insertion_sort(vector<Store>& s, bool comp(const Store&, const Store&))
{
	// TODO: Using the insertion sort algorithm, sort s
	//       according to the ordering relationship passed in as the
	//       parameter comp.

		//if less than 2 stores 
	if (s.size() < 2) return;

	//for every element in the vector 
	for (int i = 1; i < s.size(); ++i) {

		//storing item to compare 
		Store nextItem = s[i];

		//storing position 
		int loc = i; 

		//if previous item is greater than current item (sorting by comp) 
		//theArray[loc-1] > nextItem 

	// Note that if comp(x,y) is true, it means x must end up before y in the
	// final ordering. 
		while (loc > 0 && comp(nextItem,s[loc-1])) {
			s[loc]=s[loc-1];
			--loc; 
		}
		//remains same 
		s[loc] = nextItem; 
	}
	/*
	void insertionSort(vector<store> s, int n) n is not given here 
	{
	    for (int unsorted = 1; unsorted < n; unsorted++)
	    {
		storing item 
	        T nextItem = theArray[unsorted];
		storing position?
	        int loc = unsorted;
		if the item before is greater than current item 
	        while (loc > 0  &&  theArray[loc-1] > nextItem)
		
		switching the two items 
		    theArray[loc] = theArray[loc-1];
		decrement 
		    loc--;
		}
		item stays same if it is greater than previous element 
	        theArray[loc] = nextItem;
	    }
	}
	*/

	// Just to show you how to use the second parameter, we'll write code
	// that sorts only a vector of 2 elements.  (This is *not* the
	// insertion sort algorithm.)
	/*if (s.size() == 2 && comp(s[1], s[0]))
		swap(s[0], s[1]);*/
}

// Report the results of a timing test

void report(string caption, double t, const vector<Store>& s)
{
	cout << t << " milliseconds; " << caption
		<< "; first few stores are\n\t";
	size_t n = s.size();
	if (n > 4)
		n = 4;
	for (size_t k = 0; k < n; k++)
		cout << " (" << s[k].id << ", " << s[k].total << ")";
	cout << endl;
}
void sortUsingPtrs(vector<Store>& stores, bool comp(const Store*, const Store*));

int main()
{
	size_t nstores;
	cout << "Enter number of stores to sort: ";
	cin >> nstores;
	if (!cin || nstores <= 0)
	{
		cout << "You must enter a positive number.  Goodbye." << endl;
		return 1;
	}

	// Create a random ordering of id numbers 0 through nstores-1
	vector<IdType> ids;
	for (size_t j = 0; j < nstores; j++)
		ids.push_back(IdType(j));
	shuffle(ids.begin(), ids.end(), generator);  // from <algorithm>

	  // Create a bunch of Stores
	vector<Store> unorderedStores;
	for (size_t k = 0; k < ids.size(); k++)
		unorderedStores.push_back(Store(ids[k]));

	// Create a timer

	Timer timer;

	// Sort the Stores using the STL sort algorithm.  It uses a variant
	// of quicksort called introsort.

	vector<Store> stores(unorderedStores);
	timer.start();
	sort(stores.begin(), stores.end(), compareStore);
	report("STL sort", timer.elapsed(), stores);
	assert(is_sorted(stores.begin(), stores.end(), compareStore));  // from <algorithm>

	  // Sort the already sorted array using the STL sort.  This should be
	  // fast.

	timer.start();
	sort(stores.begin(), stores.end(), compareStore);
	report("STL sort if already sorted", timer.elapsed(), stores);
	assert(is_sorted(stores.begin(), stores.end(), compareStore));

	if (TEST_INSERTION_SORT)
	{
		// Sort the original unsorted array using insertion sort.  This
		// should be really slow.  If you have to wait more than a minute,
		// try rerunning the program with a smaller number of Stores.

		stores = unorderedStores;
		timer.start();
		insertion_sort(stores, compareStore);
		double elapsed = timer.elapsed();
		if (is_sorted(stores.begin(), stores.end(), compareStore))
		{
			report("insertion sort if not already sorted", elapsed, stores);

			// Sort the already sorted array using insertion sort.  This
			// should be fast.

			timer.start();
			insertion_sort(stores, compareStore);
			report("insertion sort if already sorted", timer.elapsed(), stores);
			assert(is_sorted(stores.begin(), stores.end(), compareStore));
		}
		else
			cout << "[Skipping tests of insertion_sort, since it's not correctly implemented.]" << endl;
	}

	// Since Stores are expensive to copy, and since the STL's sort copies
	// Stores O(N log N) times, let's sort POINTERS to the Stores, then
	// make one final pass to rearrange the Stores according to the
	// reordered pointers.  We'll write some code; you write the rest
	// below in sortUsingPtrs.

	// Set stores to the original unsorted sequence
	stores = unorderedStores;

	// Start the timing
	timer.start();

	// Sort using pointers
	sortUsingPtrs(stores, compareStorePtr);

	// Report the timing and verify that the sort worked
	report("STL sort of pointers", timer.elapsed(), stores);

	// Until you correctly implement sortUsingPointers, this assertion will fail.
	assert(is_sorted(stores.begin(), stores.end(), compareStore));
}

void sortUsingPtrs(vector<Store>& stores, bool comp(const Store*, const Store*))
{
	// Since Stores are expensive to copy, and since the STL's sort copies
	// Stores O(N log N) times, let's sort POINTERS to the Stores, then
	// make one final pass to rearrange the Stores according to the
	// reordered pointers.  We'll write some code; you write the rest.

	// Create an auxiliary copy of stores to faciliate the later reordering.
	vector<Store> auxStores(stores);

	// TODO:  Create a vector of Store pointers, and set each pointer
	//        to point to the corresponding Store in auxStores.
	vector<Store*> ptrStores; 
	//basically converting auxStores to pointers and storing in vector 
	for (int i = 0; i < auxStores.size(); ++i) {
		//cannot do ptrStores[0] for an empty vector - need to create new ptr and pushback 
		Store* newStorePtr = &auxStores[i];
		ptrStores.push_back(newStorePtr);
	}

	// TODO:  Sort the vector of pointers using the STL sort algorithm
	//        with comp as the ordering relationship.  
	sort(ptrStores.begin(), ptrStores.end(), compareStorePtr);

	// TODO:  Using the now-sorted vector of pointers, replace each Store
	//        in stores with the Stores from auxStores in the correct order.
	//stores is in the vector entered 
	for (int i = 0; i < stores.size(); ++i) {
		//ptrStores is the one that has been sorted , so store that into stores 
		stores[i] = (*ptrStores[i]);
	}
}