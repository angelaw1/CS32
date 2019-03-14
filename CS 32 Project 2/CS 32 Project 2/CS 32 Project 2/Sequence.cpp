#include "Sequence.h"

Sequence::Sequence() {
	head = nullptr;
	tail = nullptr;
}

Sequence::~Sequence() {
	Node *temp;
	temp = head;
	while (temp != nullptr) {
		Node *p = temp->next;
		delete temp;
		temp = p;
	}
}

Sequence::Sequence(const Sequence &old) {
	if (old.size() == 0) {
		head = nullptr;
		tail = nullptr;
		return;
	}

	// traverses through old sequence
	Node *tempOld = old.head;
	head = new Node;

	// traverses thorugh new sequence
	Node *tempNew = head;
	tempNew->previous = nullptr;
	tempNew->value = tempOld->value;

	for (int i = 0; i != old.size() - 1; i++) {
		tempNew->next = new Node;
		tempNew->next->value = tempOld->next->value;
		tempNew->next->previous = tempNew;
		tempNew = tempNew->next;
		tempOld = tempOld->next;
	}

	// last Node
	tempNew->next = nullptr;
	tail = tempNew;
}

Sequence& Sequence::operator=(const Sequence &old) {
	if (&old == this)
		return *this;
	Node *temp = head;

	// deletes all of the sequences current nodes
	while (temp != nullptr) {
		Node *p = temp->next;
		delete temp;
		temp = p;
	}

	// if old is empty
	if (old.size() == 0) {
		head = nullptr;
		tail = nullptr;
		return *this;
	}

	// traverses through old sequence
	Node *tempOld = old.head;
	head = new Node;

	//traverses through new sequence
	Node *tempNew = head;
	tempNew->previous = nullptr;
	tempNew->value = tempOld->value;

	for (int i = 0; i != old.size() - 1; i++) {
		tempNew->next = new Node;
		tempNew->next->value = tempOld->next->value;
		tempNew->next->previous = tempNew;

		// point to node whose values we just changed
		tempNew = tempNew->next;
		tempOld = tempOld->next;
	}

	// last node
	tempNew->next = nullptr;
	tail = tempNew;
	return *this;
}

bool Sequence::empty() const {
	return (head == nullptr);
}

int Sequence::size() const {
	Node *temp = head;
	int count = 0;
	if (!empty()) {
		count = 1;
		while (temp->next != nullptr) {
			count++;
			temp = temp->next;
		}
	}
	return count;
}

bool Sequence::insert(int pos, const ItemType& value) {
	Node* temp = head;
	int count = 0;

	if (pos < 0 || pos > size())
		return false;

	Node *newItem = new Node;
	newItem->value = value;

	// insert into empty sequence
	if (size() == 0) {
		newItem->previous = nullptr;
		newItem->next = nullptr;
		head = newItem;
		tail = newItem;
		return true;
	}

	// insert at top of sequence
	if (pos == 0) {
		newItem->previous = nullptr;
		newItem->next = head;
		head->previous = newItem;
		head = newItem;
		return true;
	}

	// insert at end of sequence
	if (pos == size()) {
		newItem->previous = tail;
		newItem->next = nullptr;
		tail->next = newItem;
		tail = newItem;
		return true;
	}

	// insert at middle of sequence
	for (; count != pos; count++) {
		temp = temp->next;
	}

	newItem->next = temp;
	newItem->previous = temp->previous;
	temp->previous->next = newItem;
	temp->previous = newItem;
	return true;
}

int Sequence::insert(const ItemType& value) {
	int count = 0;
	Node *temp = head;

	// insert in empty sequence or top of sequence
	if (size() == 0 || temp->value >= value) {
		insert(0, value);
		return count;
	}

	//Node *newItem = new Node;
	//newItem->value = value;

	for (; count != size() && temp->value < value; count++)
		temp = temp->next;

	insert(count, value);
	return count;
}

bool Sequence::erase(int pos) {
	Node *temp = head;
	if (pos < 0 || pos >= size())
		return false;

	// erase from top of list
	if (pos == 0) {
		// emptying list
		if (size() == 1) {
			delete temp;
			head = nullptr;
			tail = nullptr;
			return true;
		}
		Node *temp = head;
		head = temp->next;
		delete temp;
		head->previous = nullptr;
		return true;
	}

	for (int i = 0; i != pos; i++)
		temp = temp->next;

	//erase last node
	if (pos == size() - 1) {
		temp->previous->next = nullptr;
		tail = temp->previous;
		delete temp;
		return true;
	}

	temp->previous->next = temp->next;
	temp->next->previous = temp->previous;
	delete temp;
	return true;
}

int Sequence::remove(const ItemType& value) {
	Node *temp = head;
	int count = 0;
	for (int i = 0; i != size(); i++) {
		if (temp->value == value) {
			temp = temp->next;
			erase(i);
			count++;
			i--;
		}
		else
			temp = temp->next;
	}
	return count;
}

bool Sequence::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= size())
		return false;

	Node *temp = head;
	for (int i = 0; i != pos; i++)
		temp = temp->next;
	value = temp->value;
	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
	if (pos < 0 || pos >= size())
		return false;

	Node *temp = head;
	for (int i = 0; i != pos; i++)
		temp = temp->next;
	temp->value = value;
	return true;
}

int Sequence::find(const ItemType& value) const {
	int p = -1;
	if (head == nullptr)
		return p;

	Node *temp = head;
	for (int i = 0; i != size(); i++) {
		if (temp->value == value) {
			p = i;
			break;
		}
		temp = temp->next;
	}
	return p;
}

void Sequence::swap(Sequence& other) {
	Node *tempHead = head;
	Node *tempTail = tail;
	head = other.head;
	tail = other.tail;
	other.head = tempHead;
	other.tail = tempTail;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
	int index = -1;
	if (seq2.size() > seq1.size())
		return index;

	for (int i = 0; i != seq1.size() - seq2.size() + 1; i++) {
		int temp = i;

		// index for seq2
		int j = 0;
		while (j != seq2.size()) {
			ItemType value1;
			ItemType value2;
			seq1.get(temp, value1);
			seq2.get(j, value2);
			if (value1 != value2)
				break;
			j++;
			temp++;
		}

		// if all of all of seq2 was processed
		if (j == seq2.size()) {
			index = i;
			break;
		}
	}
	return index;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
	int resultIndex = 0;
	int index = 0;
	int resultSize = result.size();

	// erase all nodes currently in result
	for (int i = 0; i != resultSize; i++)
		result.erase(0);
	while (resultIndex != seq1.size() + seq2.size()) {
		ItemType value;
		if (index < seq1.size()) {
			seq1.get(index, value);
			result.insert(resultIndex, value);
			resultIndex++;
		}
		if (index < seq2.size()) {
			seq2.get(index, value);
			result.insert(resultIndex, value);
			resultIndex++;
		}
		index++;
	}
}