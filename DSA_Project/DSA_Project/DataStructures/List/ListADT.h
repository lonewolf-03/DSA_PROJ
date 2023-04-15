#pragma once

#include "../../DataStructures/Node.h"
#include "ListADT.h"
#include <iostream>
#define max_size 1000

template <typename type>
class LinkedList {
private:
	int count;
	Node<type>* head;
public:
	LinkedList() {
		count = 0;
		head = nullptr;
	}

	// copy constructor

	LinkedList(const LinkedList& L) : count(0), head(nullptr) {
		Node<type>* node = L.getHead();
		while (node) {
			this->append(node->getData());
			node = node->getNext();
		}
	}

	// overloading assignment operator
	void operator =(const LinkedList& L) {
		this->clear();
		count = 0;
		head = nullptr;
		Node<type>* node = L.getHead();
		while (node) {
			this->append(node->getData());
			node = node->getNext();
		}
	}


	Node<type>* getHead() const { return head; }

	bool isEmpty() const { return (count == 0); }

	int getLength() const { return count; }

	bool insert(int new_pos, type new_item) {      // Complexity O(n) in the worst case
		if ((new_pos < 0) || (new_pos >= count) || (count == max_size)) {
			return false;
		}

		type n = new_item;
		Node<type>* new_node = new Node<type>;
		new_node->setData(n);

		if (new_pos == 0) {
			new_node->setNext(head->getNext());
			head = new_node;
		}
		else {

			Node<type>* curr_node = head;
			Node<type>* prev_node = curr_node;


			for (int i = 0; i < new_pos; i++) {
				prev_node = curr_node;
				curr_node = curr_node->getNext();
			}

			new_node->setNext(curr_node);
			prev_node->setNext(new_node);
			count++;
		}

		return true;
	}

	bool insert_beginning(type new_item) {         // complexity O(1)
		if (count == max_size) { return false; }

		Node<type>* new_node = new Node<type>;
		type n = new_item;
		new_node->setData(n);

		new_node->setNext(head);
		head = new_node;
		count++;
		return true;
	}

	bool append(type new_item) {              // complexity O(n) in all cases
		if (count == max_size) { return false; }

		type n = new_item;
		Node<type>* new_node = new Node<type>;
		new_node->setData(n);

		if (!head) {
			new_node->setNext(head);
			head = new_node;
			count++;
			return true;

		}

		Node<type>* last_node = head;
		for (int i = 0; i < count - 1; i++) {
			last_node = last_node->getNext();
		}

		new_node->setNext(last_node->getNext());
		last_node->setNext(new_node);
		count++;
		return true;
	}

	bool remove(int pos) {                // complexity O(n) in the worst case
		if ((pos < 0) || (pos >= count)) {
			return false;
		}

		Node<type>* prev_node = head;
		Node<type>* temp;
		for (int i = 0; i < pos - 1; i++) {
			prev_node = prev_node->getNext();
		}

		temp = prev_node->getNext();
		prev_node->setNext(temp->getNext());
		delete temp;
		count--;

		return true;
	}

	bool pop(type& item) {     // complexity O(n)
		if (!head) {
			return false;
		}

		Node<type>* second_last_node = head;
		for (int i = 0; i < count - 2; i++) {
			second_last_node = second_last_node->getNext();
		}

		Node<type>* temp = second_last_node->getNext();
		second_last_node->setNext(temp->getNext());
		item = temp->getData();
		delete temp;
		count--;
		return true;
	}

	bool remove_entry(type item) {      // Complexity O(n) in the worst case. The complexity is a funtion of pos
		bool node_found = false;
		Node<type>* curr_node = head;
		Node<type>* prev_node = curr_node;
		for (int i = 0; i < count - 1; i++) {
			if (curr_node->getData() == item) {
				node_found = true;
				break;
			}
			prev_node = curr_node;
			curr_node = curr_node->getNext();
		}

		if (!node_found && curr_node->getData() == item) {
			node_found = true;
		}

		if (node_found) {
			Node<type>* temp = curr_node;
			prev_node->setNext(curr_node->getNext());
			delete temp;
			count--;
		}

		return node_found;
	}

	bool remove_beginning() {  // complexity O(1)
		if (!head) {  // list is empty
			return false;
		}

		Node<type>* temp = head;
		head = head->getNext();
		delete temp;
		count--;
		return true;
	}

	void clear() {  // complexity O(n)
		if (head) {
			Node<type>* curr_node = head;
			Node<type>* temp;
			while (curr_node->getNext()) {
				temp = curr_node;
				curr_node = curr_node->getNext();
				delete temp;
			}

			delete curr_node;
			head = nullptr;
			count = 0;
		}
	}

	type getEntry(int pos) const {  // Complexity O(n) in the worst case. The complexity is a funtion of pos
		Node<type>* curr_node = head;
		if ((pos < 0) || (pos >= count)) {
			return nullptr; // NOTE: this works only when type is an integral type or any pointer type
		}

		for (int i = 0; i < pos; i++) {
			curr_node = curr_node->getNext();
		}
		return curr_node->getData();
	}

	bool replace(int pos, type new_item) {  // Complexity O(n) in the owrst case. The complexity is a funtion of pos
		Node<type>* curr_node = head;
		if ((pos < 0) || (pos >= count)) {
			return false;
		}

		for (int i = 0; i < pos; i++) {
			curr_node = curr_node->getNext();
		}

		curr_node->setData(new_item);
		return true;
	}

	void Print() const {
		if (head) {
			Node<type>* curr_node = head;
			while (curr_node) {
				std::cout << " [ " << curr_node->getData() << " ]-->";
				curr_node = curr_node->getNext();
			}

		}

		std::cout << "NULL\n";
	}

	~LinkedList() {
		this->clear();
	}
};

