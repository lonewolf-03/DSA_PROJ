#pragma once


template <class type>
class Node {
private:
	type data;
	Node<type>* next_node;
public:
	Node() : data(type()), next_node(nullptr) {
	}

	type getData() { return data; }
	Node<type>* getNext() { return next_node; }
	void setData(type data) { this->data = data; }
	void setNext(Node<type>* next_node) { this->next_node = next_node; }


};