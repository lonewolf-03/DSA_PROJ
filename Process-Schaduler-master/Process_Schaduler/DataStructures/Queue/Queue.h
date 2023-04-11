#pragma once
#include "../Node.h"

#include<iostream>
#define null NULL
using namespace std;
template <class type>
class Queue {
	Node<type>* front = null;
	Node<type>* rear = null;
	int count;
public:
	Queue() : count(0), front(nullptr), rear(nullptr) {}

	// copy constructor
	Queue(const Queue& Q) : count(0), front(nullptr), rear(nullptr) {
		Node<T>* node = Q.front;
		while (node) {
			this->enqueue(node->getData());
			node = node->getNext();
		}
	}

	// overloading assignement operator
	void operator =(const Queue& Q) {
		this->clear();
		count = 0;
		front = nullptr;
		rear = nullptr;
		Node<T>* node = Q.front;
		while (node) {
			this->enqueue(node->getData());
			node = node->getNext();
		}
	}

	bool isEmpty() const { return (count == 0); }

	bool isFull() const { return (count == max_size); }


	bool peakFront(T& item) const {
		if (!isEmpty()) {
			item = front->getData();
			return true;
		}

		return false;
	}

	bool peakRear(T& item) const {
		if (!isEmpty()) {
			item = rear->getData();
			return true;
		}

		return false;
	}

	int getCount() const { return count; }

	bool enqueue(T item) {
		if (isFull()) {
			return false;
		}

		Node<T>* new_node = new Node<T>;
		new_node->setData(item);
		new_node->setNext(nullptr);

		if (isEmpty()) {
			rear = new_node;
			front = rear;
		}
		else {
			rear->setNext(new_node);
			rear = new_node;
		}

		count++;

		return true;
	}

	bool dequeue(T& item) {
		if (isEmpty()) {
			return false;
		}

		item = front->getData();
		Node<T>* temp = front;
		front = front->getNext();
		delete temp;

		count--;
		return true;
	}

	void clear() {
		Node<T>* node = front;
		Node<T>* temp;
		if (node) {
			while (node && node->getNext()) {
				temp = node;
				node = node->getNext();
				delete temp;
			}

			delete node;
		}

		front = nullptr;
		rear = nullptr;
	}

	void Print() const {
		Node<T>* node = front;
		if (node) {
			while (node && node->getNext()) {
				std::cout << "[ " << node->getData() << "]";
				node = node->getNext();
			}

			std::cout << "[ " << node->getData() << "]\n";
		}
	}

	~Queue() {
		this->clear();
	}
};