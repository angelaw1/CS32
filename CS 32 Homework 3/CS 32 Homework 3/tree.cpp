// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
	int count = 0;
	bool isMarked = false;
	if (n2 == 0)
		return 1;
	if (n1 == 0)
		return 0;
	if (a1[0] != a2[0]) {
		count += countIncludes(a1 + 1, n1 - 1, a2, n2);
	}
	if (a1[0] == a2[0]) {
		isMarked = true;
		count += countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	}
	if (isMarked) {
		count += countIncludes(a1 + 1, n1 - 1, a2, n2);
		isMarked = false;
	}
	return count;
}

// Exchange two doubles
void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > separator come before all the other elements,
// and all the elements whose value is < separator come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= separator, or n if there is no such element, and firstLess is
// set to the index of the first element that is < separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > separator
//   * for firstNotGreater <= i < firstLess, a[i] == separator
//   * for firstLess <= i < n, a[i] < separator
// All the elements > separator end up in no particular order.
// All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator,
	int& firstNotGreater, int& firstLess)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	//  Every element earlier than position firstNotGreater is > separator
	//  Every element from position firstNotGreater to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstLess-1 is not known yet
	//  Every element at position firstLess or later is < separator

	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
		if (a[firstUnknown] < separator)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if (a[firstUnknown] > separator)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
	if (n <= 0)
		return;
	int firstNotGreater;
	int firstLess;
	separate(a, n, a[0], firstNotGreater, firstLess);
	order(a, firstNotGreater);
	order(a + firstLess, n - firstLess);
}

/* #include <cassert>
#include <iostream>
using namespace std;
int main() {
	double arr[10] = { 2.5, 6.7, -2.4, 6.8, 3.7, 5.0, -6.4, 5.3, 6.8, 2.5 };
	int firstNotGreater;
	int firstLess;
	order(arr, 10);
	for (int i = 0; i != 9; i++)
		assert(arr[i] >= arr[i + 1]);

	double arr1[7] = { 10, 50, 40, 20, 50, 40, 30 };
	double arr2[3] = { 50, 40, 30 };
	double arr3[3] = { 10, 20, 40 };
	double arr4[3] = { 10, 40, 30 };
	double arr5[3] = { 20, 10, 40 };
	assert(countIncludes(arr1, 7, arr2, 3) == 3);
	assert(countIncludes(arr1, 7, arr3, 3) == 1);
	assert(countIncludes(arr1, 7, arr4, 3) == 2);
	assert(countIncludes(arr1, 7, arr5, 3) == 0);
	assert(countIncludes(arr1, 7, arr1, 7) == 1);
	assert(countIncludes(arr1, 7, arr2, 0) == 1);
	assert(countIncludes(arr1, 0, arr2, 3) == 0);
	assert(countIncludes(arr1, 0, arr2, 0) == 1);
	order(arr1, 7);
	for (int i = 0; i != 6; i++)
		assert(arr1[i] >= arr1[i + 1]);
	order(arr2, 3);
	for (int i = 0; i != 2; i++)
		assert(arr2[i] >= arr2[i + 1]);
	order(arr3, 3);
	for (int i = 0; i != 2; i++)
		assert(arr3[i] >= arr3[i + 1]);
	order(arr4, 3);
	for (int i = 0; i != 2; i++)
		assert(arr4[i] >= arr4[i + 1]);
	order(arr5, 3);
	for (int i = 0; i != 2; i++)
		assert(arr5[i] >= arr5[i + 1]);

	double arr6[7] = { 10, 20, 40, 50, 40, 50, 50 };
	double arr7[3] = { 10, 40, 50 };
	double arr8[3] = { 50, 40, 50 };
	double arr9[3] = { 40, 50, 50 };
	assert(countIncludes(arr6, 7, arr7, 3) == 5);
	assert(countIncludes(arr6, 7, arr8, 3) == 2);
	assert(countIncludes(arr6, 7, arr9, 3) == 4);
	order(arr6, 7);
	for (int i = 0; i != 6; i++)
		assert(arr6[i] >= arr6[i + 1]);
	order(arr7, 3);
	for (int i = 0; i != 2; i++)
		assert(arr7[i] >= arr7[i + 1]);
	order(arr8, 3);
	for (int i = 0; i != 2; i++)
		assert(arr8[i] >= arr8[i + 1]);
	order(arr9, 3);
	for (int i = 0; i != 2; i++)
		assert(arr9[i] >= arr9[i + 1]);

	double arr10[7] = { 10, 20, 10, 20, 10, 20, 10 };
	double arr11[3] = { 10, 20, 10 };
	double arr12[3] = { 20, 10, 20 };
	assert(countIncludes(arr10, 7, arr11, 3) == 10);
	assert(countIncludes(arr10, 7, arr12, 3) == 4);
	order(arr10, 7);
	for (int i = 0; i != 6; i++)
		assert(arr10[i] >= arr10[i + 1]);
	order(arr11, 3);
	for (int i = 0; i != 2; i++)
		assert(arr11[i] >= arr11[i + 1]);
	order(arr12, 3);
	for (int i = 0; i != 2; i++)
		assert(arr12[i] >= arr12[i + 1]);
	order(arr10, -9);
 
	cout << "All tests passed!" << endl;
} */