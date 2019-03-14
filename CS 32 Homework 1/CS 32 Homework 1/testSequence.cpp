#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Sequence s;
	assert(s.empty());
	assert(s.find(42) == -1);
	s.insert(42);
	assert(s.size() == 1 && s.find(42) == 0);
	Sequence a;
	for (int i = 0; i < 50; i++)
		assert(a.insert(i) == i);
	assert(a.size() == 50);
	a.insert(10, 2);
	assert(a.size() == 51);
	ItemType test;
	for (int i = 0; i < 10; i++) {
		a.get(i, test);
		assert(test == i);
	}
	a.get(10, test);
	assert(test == 2);
	for (int i = 11; i < a.size(); i++) {
		a.get(i, test);
		assert(i == test + 1);
	}
	a.erase(10);
	assert(a.size() == 50);
	for (int i = 0; i < a.size(); i++) {
		a.get(i, test);
		assert(test == i);
	}
	assert(a.set(50, 10) == false);
	for (int i = 0; i < a.size(); i++) {
		assert(a.set(i, i + 1));
	}
	int test1 = 1;
	for (int i = 0; i < a.size(); i++, test1++) {
		a.get(i, test);
		assert(test == test1);
	}
	assert(a.find(51) == -1);
	assert(a.find(50) == 49);
	assert(a.find(49) == 48);

	Sequence b;
	ItemType even = 2;
	ItemType odd = 3;
	for (int i = 0; i < 50; i++) {
		if (i % 2 == 0)
			b.insert(i, even);
		else
			b.insert(i, odd);
	}
	assert(b.size() == 50);
	
	a.swap(b);
	for (int i = 0; i < b.size(); i++) {
		b.get(i, test);
		assert(test == i + 1);
	}

	for (int i = 0; i < a.size(); i++) {
		a.get(i, test);
		if (i % 2 == 0)
			assert(test == even);
		else
			assert(test == odd);
	}

	assert(a.find(even) == 0);
	assert(a.find(odd) == 1);
	assert(a.remove(even) == 25);
	assert(a.size() == 25);
	for (int i = 0; i < a.size(); i++) {
		a.get(i, test);
		assert(test == odd);
	}

	Sequence c;
	c.insert(0, 34);
	c.insert(0, 63);
	c.insert(0, 57);
	c.insert(0, 84);
	c.insert(0, 733);
	c.insert(0, 865);
	c.insert(0, 454);
	c.insert(0, 75);
	c.insert(0, 38);
	c.insert(0, 95);
	c.insert(0, 24);
	c.insert(0, 14);
	c.insert(0, 72);
	c.insert(0, 84);
	c.insert(0, 73);
	assert(c.size() == 15);
	assert(c.erase(5) == true);
	assert(c.erase(38) == false);
	assert(c.insert(0, 733) == true);
	assert(c.insert(56) == 0);
	assert(c.size() == 16);

	Sequence d;
	d.insert(0, 48);
	d.insert(0, 75);
	d.insert(0, 26);
	d.insert(0, 48);
	d.insert(0, 75);
	d.insert(0, 84);
	d.insert(0, 53); 
	d.insert(0, 83);
	d.insert(0, 85);
	d.insert(0, 48);
	assert(d.size() == 10);
	ItemType dd;
	d.get(2, dd);
	assert(dd == 83);
	assert(d.get(58, dd) == false);
	assert(d.set(0, 74) == true);
	d.get(0, dd);
	assert(dd == 74);
	assert(d.find(48) == 6);
	assert(d.remove(48) == 2);
	assert(d.size() == 8);
	c.swap(d);
	assert(c.size() == 8);
	assert(d.size() == 16);
	for (int i = 0; i < 8; i++) {
		c.get(i, dd);
		cout << dd << endl;
	}
	cout << endl;
	for (int i = 0; i < 16; i++) {
		d.get(i, dd);
		cout << dd << endl;
	}

	cout << "Passed all tests" << endl;
}

/* #include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Sequence s;
	assert(s.empty());
	assert(s.find("laobing") == -1);
	s.insert("laobing");
	assert(s.size() == 1 && s.find("laobing") == 0);
	cout << "Passed all tests" << endl;

	ItemType test;
	Sequence a;
	assert(a.insert("a") == 0);
	assert(a.insert("b") == 1);
	assert(a.insert("c") == 2);
	assert(a.insert("d") == 3);
	a.insert("e");
	a.insert("f");
	a.insert("g");
	a.insert("h");
	a.insert("i");
	a.insert("j");
	a.insert("k");
	a.insert("l");
	a.insert("m");
	a.insert("n");
	a.insert("o");
	a.insert("p");
	a.insert("q");
	a.insert("r");
	a.insert("s");
	a.insert("t");
	a.insert("u");
	a.insert("v");
	a.insert("w");
	a.insert("x");
	a.insert("y");
	assert(a.insert("z") == 25);
	assert(a.size() == 26);
	assert(a.insert(10, "!") == true);
	assert(a.size() == 27);
	assert(a.find("!") == 10);
	assert(a.find("hello") == -1);
	a.get(26, test);
	assert(test == "z");
	assert(a.erase(10) == true);
	assert(a.size() == 26);
	for (int i = 0; i < a.size() - 1; i++) {
		a.get(i + 1, test);
		a.set(i, test);
	}
	a.set(a.size() - 1, "a");
	a.get(0, test);
	assert(test == "b");
	a.get(1, test);
	assert(test == "c");
	a.get(25, test);
	assert(test == "a");

	Sequence b;
	for (int i = 0; i < a.size(); i++) {
		if (i % 2 == 0)
			b.insert(i, "even");
		else
			b.insert(i, "odd");
	}
	a.swap(b);
	b.get(0, test);
	assert(test == "b");
	b.get(1, test);
	assert(test == "c");
	b.get(25, test);
	assert(test == "a");
	a.get(0, test);
	assert(test == "even");
	a.get(1, test);
	assert(test == "odd");
	a.get(25, test);
	assert(test == "odd");
	a.remove("odd");
	assert(a.size() == 13);
	for (int i = 0; i < a.size(); i++) {
		a.get(i, test);
		assert(test == "even");
	} 

	Sequence s1;
	s1.insert(0, "paratha");
	s1.insert(0, "focaccia");
	Sequence s2;
	s2.insert(0, "roti");
	s1.swap(s2);
	assert(s1.size() == 1 && s1.find("roti") == 0 && s2.size() == 2 &&
		s2.find("focaccia") == 0 &&  s2.find("paratha") == 1);
} */


/* #include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{ */
	/* Sequence s;
	assert(s.insert(0, "lavash"));
	assert(s.insert(0, "tortilla"));
	assert(s.size() == 2);
	ItemType x = "injera";
	assert(s.get(0, x) && x == "tortilla");
	assert(s.get(1, x) && x == "lavash"); */

	/* Sequence s;
	s.insert(0, "a");
	s.insert(1, "b");
	s.insert(2, "c");
	s.insert(3, "b");
	s.insert(4, "e");
	assert(s.remove("b") == 2);
	assert(s.size() == 3);
	string x;
	assert(s.get(0, x) && x == "a");
	assert(s.get(1, x) && x == "c");
	assert(s.get(2, x) && x == "e"); */

	/* Sequence s;
	s.insert(0, "dosa");
	s.insert(1, "pita");
	s.insert(2, "");
	s.insert(3, "matzo");
	assert(s.find("") == 2);
	s.remove("dosa");
	assert(s.size() == 3 && s.find("pita") == 0 && s.find("") == 1 &&
		s.find("matzo") == 2);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
} */

/* #include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Sequence s;
	assert(s.insert(0, 10));
	assert(s.insert(0, 20));
	assert(s.size() == 2);
	ItemType x = 999;
	assert(s.get(0, x) && x == 20);
	assert(s.get(1, x) && x == 10);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
} */