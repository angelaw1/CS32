#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED
#include <iostream>
#include <string>

typedef std::string ItemType;
//typedef unsigned long ItemType;

struct Node {
	ItemType value;
	Node *next;
	Node *previous;
};

class Sequence
{
public:
	Sequence();
	~Sequence();
	Sequence(const Sequence &old);
	Sequence &operator=(const Sequence &seq);
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
	//void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

private:
	Node *head;
	Node *tail;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif