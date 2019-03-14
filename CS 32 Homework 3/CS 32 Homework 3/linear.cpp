#include <cassert>
#include <iostream>

using namespace std;


//bool somePredicate(double x);

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
	bool result = true;
	if (n <= 0)
		return result;
	bool part1 = somePredicate(a[n - 1]);
	bool part2 = allTrue(a, n - 1);
	return (part1 && part2);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
	int count = 0;
	if (n <= 0) {
		return count;
	}
	int part1 = 0;
	if (!somePredicate(a[n - 1]))
		part1 = 1;
	int part2 = countFalse(a, n - 1);
	count = part1 + part2;
	return count;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
	if (n <= 0) {
		return -1;
	}
	if (!somePredicate(a[0]))
		return 0;
	int part1 = 1;
	int part2 = firstFalse(a + 1, n - 1);
	if (part2 == -1)
		return -1;
	int result = part1 + part2;
	if (result == 0)
		return -1;
	return result;
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
	if (n < 1)
		return -1;
	int indexMin = n - 1;
	double min = a[indexMin];
	int index2 = indexOfMin(a, indexMin);
	if (index2 == -1)
		return indexMin;
	if (min >= a[index2])
		indexMin = index2;
	return indexMin;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0)
		return true;
	if (n1 <= 0)
		return false;
	//bool part1 = true;
	bool result = true;
	if (a1[0] == a2[0])
		result = includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	else
		result = includes(a1 + 1, n1 - 1, a2, n2);
	return result;
}

/* bool somePredicate(double x) {
	return (x < 0);
}

int main() {
	double arr[10] = { -1, 4, 5, -9, 4, 0, 6, -4, -5, 6 };
	double arr1[5] = { -1, -2, -3, -4, -5 };
	double arr2[5] = { 2, -3, -5, -9, -4 };
	double arr3[4] = { 4, -9, 4, 6 };
	double arr4[5] = { -7.5, -9.2, -9.6, -9.1, 4.7 };
	double arr5[5] = { 3.4, 6.7, 8.2, 2.6, 7.2 };
	double arr6[5] = { 0, 7.6, 4.5, 2.6, 9.8 };
	double arr7[5] = { -5.6, 7.1, -5.6, 2.3, 7.0 };
	assert(allTrue(arr + 10, 0));
	assert(!allTrue(arr, 10));
	assert(allTrue(arr1, 5));
	assert(!allTrue(arr2, 5));
	assert(!allTrue(arr3, 4));
	assert(!allTrue(arr4, 5));
	assert(!allTrue(arr5, 5));
	assert(!allTrue(arr6, 5));
	assert(countFalse(arr + 10, 0) == 0);
	assert(countFalse(arr, 10) == 6);
	assert(countFalse(arr1, 5) == 0);
	assert(countFalse(arr2, 5) == 1);
	assert(countFalse(arr3, 4) == 3);
	assert(countFalse(arr4, 5) == 1);
	assert(countFalse(arr5, 5) == 5);
	assert(countFalse(arr6, 5) == 5);
	assert(firstFalse(arr + 10, 0) == -1);
	assert(firstFalse(arr, 10) == 1);
	assert(firstFalse(arr1, 5) == -1);
	assert(firstFalse(arr2, 5) == 0);
	assert(firstFalse(arr3, 4) == 0);
	assert(firstFalse(arr4, 5) == 4);
	assert(firstFalse(arr5, 5) == 0);
	assert(firstFalse(arr6, 5) == 0);
	assert(indexOfMin(arr + 10, 0) == -1);
	assert(indexOfMin(arr, 10) == 3);
	assert(indexOfMin(arr1, 5) == 4);
	assert(indexOfMin(arr2, 5) == 3);
	assert(indexOfMin(arr3, 4) == 1);
	assert(indexOfMin(arr4, 5) == 2);
	assert(indexOfMin(arr5, 5) == 3);
	assert(indexOfMin(arr6, 5) == 0);
	assert(indexOfMin(arr7, 5) == 0);
	assert(includes(arr, 10, arr3, 4));
	assert(!includes(arr3, 4, arr, 10));
	assert(!includes(arr, 10, arr1, 5));
	assert(includes(arr1, 5, arr + 10, 0));

	cout << "All Tests Passed!" << endl;
} */