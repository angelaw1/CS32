#include "Sequence.h"
#include <cassert>
using namespace std;

int main() {
	ItemType value;
	Sequence a;
	assert(a.empty());					// standard case
	assert(a.insert(0, "hello"));		// insert (2 parameters) in empty list
	assert(a.size() == 1);
	a.get(0, value);					// get value at top
	assert(value == "hello");
	assert(!a.insert(2, "aaaaa"));		// false case, not enough nodes
	assert(a.insert(0, "aaaaa"));		// insert (2 parameters) at top
	assert(a.size() == 2);
	a.get(0, value);
	assert(value == "aaaaa");
	assert(a.insert(2, "b"));			// insert (2 parameters) at end of list
	assert(a.size() == 3);
	a.get(2, value);
	assert(value == "b");
	assert(a.insert("aaaa") == 0);		// insert (1 paramter) at top
	assert(a.size() == 4);
	a.get(0, value);
	assert(value == "aaaa");
	assert(a.insert("z") == 4);			// insert (1 parameter) at end
	assert(a.size() == 5);
	a.get(4, value);
	assert(value == "z");
	assert(a.insert("h") == 2);			// standard insert (1 parameter)
	assert(a.size() == 6);
	a.get(2, value);
	assert(value == "h");
	assert(a.insert("y") == 5);
	assert(a.size() == 7);
	a.get(5, value);
	assert(value == "y");
	assert(a.erase(3));					// standard erase
	assert(a.size() == 6);
	a.get(0, value);
	assert(value == "aaaa");
	a.get(1, value);
	assert(value == "aaaaa");
	a.get(2, value);
	assert(value == "h");
	a.get(3, value);
	assert(value == "b");
	a.get(4, value);
	assert(value == "y");
	a.get(5, value);
	assert(value == "z");
	assert(a.erase(0));					// erase at top
	assert(a.size() == 5);
	a.get(0, value);
	assert(value == "aaaaa");
	a.get(1, value);
	assert(value == "h");
	assert(a.erase(4));					// erase at end
	assert(!a.erase(7));				// false case, not enough nodes
	assert(a.size() == 4);
	a.get(3, value);
	assert(value == "y");
	assert(a.insert("aaaa") == 0);
	a.get(0, value);
	assert(value == "aaaa");
	a.get(1, value);
	assert(value == "aaaaa");
	assert(a.insert(a.size(), "aaaa"));
	assert(a.size() == 6);
	a.get(5, value);
	assert(value == "aaaa");
	assert(a.remove("aaaa") == 2);		// standard remove
	assert(a.size() == 4);
	a.get(0, value);
	assert(value == "aaaaa");
	a.get(1, value);
	assert(value == "h");
	a.get(2, value);
	assert(value == "b");
	a.get(3, value);
	assert(value == "y");
	assert(a.insert("b") == 1);
	assert(a.insert(0, "b"));
	assert(a.insert(a.size(), "b"));
	assert(a.size() == 7);
	assert(a.remove("b") == 4);
	assert(a.size() == 3);
	a.get(0, value);
	assert(value == "aaaaa");
	a.get(1, value);
	assert(value == "h");
	a.get(2, value);
	assert(value == "y");
	assert(a.remove("aaaaaaaaaaa") == 0);	// remove nothing
	assert(a.set(0, "aaaa"));
	assert(!a.set(-1, "dfs"));				// false case, negative pos
	a.get(0, value);
	assert(value == "aaaa");
	assert(a.set(1, "f"));
	a.get(1, value);
	assert(value == "f");
	assert(a.set(2, "yy"));
	a.get(2, value);
	assert(value == "yy");
	assert(a.find("a") == -1);				// find nonexistent value
	assert(a.find("yy") == 2);				// standard find
	assert(a.find("aaaa") == 0);
	assert(a.find("f") == 1);

	Sequence b;
	b.insert(b.size(), "ss");
	b.insert(b.size(), "ww");
	b.insert(b.size(), "qq");
	b.insert(b.size(), "ll");
	b.insert(b.size(), "aa");
	a.swap(b);								// standard swap
	assert(a.size() == 5);
	assert(b.size() == 3);
	a.get(0, value);
	assert(value == "ss");
	a.get(1, value);
	assert(value == "ww");
	a.get(2, value);
	assert(value == "qq");
	a.get(3, value);
	assert(value == "ll");
	a.get(4, value);
	assert(value == "aa");
	b.get(0, value);
	assert(value == "aaaa");
	b.get(1, value);
	assert(value == "f");
	b.get(2, value);
	assert(value == "yy");

	Sequence c = b;					// standard copy constructore
	assert(c.size() == 3);
	c.get(0, value);
	assert(value == "aaaa");
	c.get(1, value);
	assert(value == "f");
	c.get(2, value);
	assert(value == "yy");

	c = a;						// standard operator=
	assert(c.size() == 5); 
	c.get(0, value);
	assert(value == "ss");
	c.get(1, value);
	assert(value == "ww");
	c.get(2, value);
	assert(value == "qq");
	c.get(3, value);
	assert(value == "ll");
	c.get(4, value);
	assert(value == "aa");
	assert(c.size() == 5);

	Sequence d;
	d.insert(0, "qq");
	d.insert(1, "ll");
	d.insert(2, "aa");
	assert(subsequence(c, d) == 2);		// subsequence at end

	Sequence e;
	assert(subsequence(c, e) == 0);		// subsequence with empty list
	e.insert(0, "ss");
	e.insert(1, "ww");
	assert(subsequence(c, e) == 0);		// subsequence at beginning

	Sequence f;
	interleave(d, e, f);				// standard interleave
	assert(f.size() == 5);
	f.get(0, value);
	assert(value == "qq");
	f.get(1, value);
	assert(value == "ss");
	f.get(2, value);
	assert(value == "ll");
	f.get(3, value);
	assert(value == "ww");
	f.get(4, value);
	assert(value == "aa");

	Sequence g;
	Sequence h;
	interleave(g, h, f);			// interleave two empty lists
	assert(f.size() == 0);
	g.insert("a");
	assert(g.erase(0));				// erase from list with size = 1
	assert(g.size() == 0);
	g.insert("a");
	g.insert("a");
	g.insert("a");
	g.insert("a");
	g.insert("a");
	assert(g.remove("a") == 5);

	Sequence i;
	i.insert("a");
	i.insert("b");
	i.insert("c");
	i.insert("d");
	i.insert("e");
	i.insert("f");
	assert(i.size() == 6);
	Sequence j;
	Sequence k;
	interleave(i, j, k);			// interleave with one empty list
	assert(k.size() == 6);
	k.get(0, value);
	assert(value == "a");
	k.get(1, value);
	assert(value == "b");
	k.get(2, value);
	assert(value == "c");
	k.get(3, value);
	assert(value == "d");
	k.get(4, value);
	assert(value == "e");
	k.get(5, value);
	assert(value == "f");
	interleave(i, i, j);				// interleave same list
	assert(j.size() == 12);
	j.get(0, value);
	assert(value == "a");
	j.get(1, value);
	assert(value == "a");
	j.get(2, value);
	assert(value == "b");
	j.get(3, value);
	assert(value == "b");
	j.get(4, value);
	assert(value == "c");
	j.get(5, value);
	assert(value == "c");
	j.get(6, value);
	assert(value == "d");
	j.get(7, value);
	assert(value == "d");
	j.get(8, value);
	assert(value == "e");
	j.get(9, value);
	assert(value == "e");
	j.get(10, value);
	assert(value == "f");
	j.get(11, value);
	assert(value == "f");

	Sequence l;
	l.insert(0, "bob");
	l.insert(1, "mary");
	l.insert(2, "george");
	l.insert(3, "bobby");
	l.insert(4, "jacob");
	Sequence m;
	m.insert(0, "katie");
	m.insert(1, "max");
	m.insert(2, "david");
	Sequence n;
	interleave(l, m, n);
	assert(n.size() == 8);
	n.get(0, value);
	assert(value == "bob");
	n.get(1, value);
	assert(value == "katie");
	n.get(2, value);
	assert(value == "mary");
	n.get(3, value);
	assert(value == "max");
	n.get(4, value);
	assert(value == "george");
	n.get(5, value);
	assert(value == "david");
	n.get(6, value);
	assert(value == "bobby");
	n.get(7, value);
	assert(value == "jacob");

	Sequence o;
	o.insert(0, "bob");
	o.insert(1, "katie");
	o.insert(2, "jacob");
	o.insert(3, "david");
	o.insert(4, "bob");
	o.insert(5, "bob");
	o.insert(6, "emily");
	o.insert(7, "max");
	o.insert(8, "lily");
	o.insert(9, "frank");
	Sequence p;
	p.insert(0, "bob");
	p.insert(1, "emily");
	p.insert(2, "max");
	assert(subsequence(o, p) == 5);				// standard subsequence
	Sequence q;
	p = q;
	assert(p.size() == 0);						// operator=, assign empty list
	
	cout << "All tests passed" << endl;
}



/* #include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Sequence s;
	assert(s.insert(0, "lavash"));
	assert(s.insert(0, "tortilla"));
	assert(s.size() == 2);
	ItemType x = "injera";
	assert(s.get(0, x) && x == "tortilla");
	assert(s.get(1, x) && x == "lavash");
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



/* #include "Sequence.h"

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

static_assert(std::is_default_constructible<Sequence>::value,
	"Sequence must be default-constructible.");
static_assert(std::is_copy_constructible<Sequence>::value,
	"Sequence must be copy-constructible.");

void thisFunctionWillNeverBeCalled()
{
	CHECKTYPE(&Sequence::operator=, Sequence& (Sequence::*)(const ItemType&));
	CHECKTYPE(&Sequence::empty, bool (Sequence::*)() const);
	CHECKTYPE(&Sequence::size, int  (Sequence::*)() const);
	CHECKTYPE(&Sequence::insert, bool (Sequence::*)(int, const ItemType&));
	CHECKTYPE(&Sequence::insert, int (Sequence::*)(const ItemType&));
	CHECKTYPE(&Sequence::erase, bool (Sequence::*)(int));
	CHECKTYPE(&Sequence::remove, int  (Sequence::*)(const ItemType&));
	CHECKTYPE(&Sequence::get, bool (Sequence::*)(int, ItemType&) const);
	CHECKTYPE(&Sequence::set, bool (Sequence::*)(int, const ItemType&));
	CHECKTYPE(&Sequence::find, int  (Sequence::*)(const ItemType&) const);
	CHECKTYPE(&Sequence::swap, void (Sequence::*)(Sequence&));
	CHECKTYPE(subsequence, int(*)(const Sequence&, const Sequence&));
	CHECKTYPE(interleave, void(*)(const Sequence&, const Sequence&, Sequence&));
}

int main()
{} */



/* #include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Sequence s;
	assert(s.insert(0, "lavash"));
	assert(s.insert(0, "tortilla"));
	assert(s.size() == 2);
	ItemType x = "injera";
	assert(s.get(0, x) && x == "tortilla");
	assert(s.get(1, x) && x == "lavash");
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