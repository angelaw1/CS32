#include "ScoreList.h"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
	ScoreList a;
	assert(a.size() == 0);
	assert(a.minimum() == NO_SCORE);
	assert(a.maximum() == NO_SCORE);
	a.add(100);
	assert(a.size() == 1);
	a.add(50);
	a.add(56);
	a.add(87);
	a.add(98);
	a.add(56);
	a.add(87);
	a.add(68);
	a.add(97);
	a.add(83); 
	a.add(79);
	a.add(74);
	a.add(97);
	a.add(86);
	a.add(86);
	a.add(95);
	a.add(83);
	a.add(75);
	a.add(85);
	assert(a.size() == 19);
	assert(a.minimum() == 50);
	assert(a.maximum() == 100);
	assert(a.add(200) == false);
	assert(a.remove(100) == true);
	assert(a.size() == 18);
	assert(a.maximum() == 98);


	cout << "Passed all tests" << endl;
}