#pragma once
template <class type>
class Node {
private:
	type val;
	Node<type>* next;
public:
	Node(): val(type()), next(null) {
	}

	type getData() { return data; }
	Node<type>* getNext() { return next_node; }
	void setData(type data) { this->data = data; }
	void setNext(Node<type>* next_node) { this->next_node = next_node; }


};