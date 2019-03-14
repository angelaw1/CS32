#include "newSequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence() {
	m_size = 0;
	m_arr = new ItemType[DEFAULT_MAX_ITEMS];
	m_maxObjects = DEFAULT_MAX_ITEMS;
}

Sequence::Sequence(int numberOfObjects) {
	if (numberOfObjects < 0) {
		cout << "Number of objects in sequence has to be positive" << endl;
		return;
	}
	m_size = 0;
	m_arr = new ItemType[numberOfObjects];
	m_maxObjects = numberOfObjects;
}

Sequence::Sequence(const Sequence &old) {
	m_size = old.m_size;
	m_maxObjects = old.m_maxObjects;
	m_arr = new ItemType[m_maxObjects];
	for (int i = 0; i < m_size; i++)
		m_arr[i] = old.m_arr[i];
	
}

Sequence::~Sequence() {
	delete [] m_arr;
}

Sequence& Sequence::operator=(const Sequence &seq) {
	if (&seq == this)
		return *this;
	delete[] m_arr;
	m_size = seq.m_size;
	m_maxObjects = seq.m_maxObjects;
	m_arr = new ItemType[m_maxObjects];
	for (int i = 0; i < m_size; i++)
		m_arr[i] = seq.m_arr[i];
	return (*this);
}

bool Sequence::empty() const {
	return (m_size == 0);
}

int Sequence::size() const {
	return m_size;
}

bool Sequence::insert(int pos, const ItemType& value) {
	// Insert value into the sequence so that it becomes the item at
	// position pos.  The original item at position pos and those that
	// follow it end up at positions one higher than they were at before.
	// Return true if 0 <= pos <= size() and the value could be
	// inserted.  (It might not be, if the sequence has a fixed capacity,
	// (e.g., because it's implemented using a fixed-size array) and is
	// full.)  Otherwise, leave the sequence unchanged and return false.
	// Notice that if pos is equal to size(), the value is inserted at the
	// end.

	if (pos < 0 || pos > m_size || m_size == m_maxObjects)
		return false;
	for (int i = m_size; i > pos; i--) {
		m_arr[i] = m_arr[i - 1];
	}
	m_arr[pos] = value;
	m_size++;
	return true;
}

int Sequence::insert(const ItemType& value) {
	// Let p be the smallest integer such that value <= the item at
	// position p in the sequence; if no such item exists (i.e.,
	// value > all items in the sequence), let p be size().  Insert
	// value into the sequence so that it becomes the item at position
	// p.  The original item at position p and those that follow it end
	// up at positions one higher than before.  Return p if the value
	// was actually inserted.  Return -1 if the value was not inserted
	// (perhaps because the sequence has a fixed capacity and is full).

	if (m_size == m_maxObjects)
		return -1;

	int p = m_size;
	for (int i = 0; i < m_size; i++) {
		if (value <= m_arr[i]) {
			p = i;
		}
		break;
	}
	insert(p, value);
	return p;
}

bool Sequence::erase(int pos) {
	// If 0 <= pos < size(), remove the item at position pos from
	// the sequence (so that all items that followed this item end up at
	// positions one lower than they were at before), and return true.
	// Otherwise, leave the sequence unchanged and return false.

	if (pos < 0 || pos >= m_size)
		return false;
	for (int i = pos; i < m_size - 1; i++)
		m_arr[i] = m_arr[i + 1];
	m_size--;
	return true;
}

int Sequence::remove(const ItemType& value) {
	// Erase all items from the sequence that == value.  Return the
	// number of items removed (which will be 0 if no item == value).

	int count = 0;
	for (int i = m_size - 1; i >= 0; i--) {
		if (m_arr[i] == value) {
			erase(i);
			count++;
		}
	}
	return count;
}

bool Sequence::get(int pos, ItemType& value) const {
	// If 0 <= pos < size(), copy into value the item at position pos
	// in the sequence and return true.  Otherwise, leave value unchanged
	// and return false.

	if (pos < 0 || pos >= m_size)
		return false;
	value = m_arr[pos];
	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
	// If 0 <= pos < size(), replace the item at position pos in the
	// sequence with value and return true.  Otherwise, leave the sequence
	// unchanged and return false.

	if (pos < 0 || pos >= m_size)
		return false;
	m_arr[pos] = value;
	return true;
}

int Sequence::find(const ItemType& value) const {
	// Let p be the smallest integer such that value == the item at
	// position p in the sequence; if no such item exists, let p be -1.
	// Return p.

	int p = -1;
	for (int i = 0; i < m_size; i++) {
		if (m_arr[i] == value) {
			p = i;
			break;
		}
	}
	return p;
}

void Sequence::swap(Sequence& other) {
	// Exchange the contents of this sequence with the other one.

	int tempSize = m_size;
	int tempMax = m_maxObjects;
	ItemType* tempArr = m_arr;
	m_size = other.m_size;
	m_maxObjects = other.m_maxObjects;
	m_arr = other.m_arr;
	other.m_size = tempSize;
	other.m_maxObjects = tempMax;
	other.m_arr = tempArr;
	tempArr = nullptr;
}