#pragma once
#include <iostream>
using namespace std;

template<typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		Node<T>* temp = head;
		while(temp != nullptr) {
			std::cout << temp->data << std::endl;
			temp = temp->next;
		}
		temp = nullptr;
	}
	void printReverse() const {
		Node<T>* temp = tail;
		while(temp != nullptr) {
			std::cout << temp->data << std::endl;
			temp = temp->prev;
		}
		temp = nullptr;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node<T>* getHead() {
		return head;
	}
	const Node<T>* getHead() const {
		return head;
	}
	Node<T>* getTail() {
		return tail;
	}
	const Node<T>* getTail() const {
		return tail;
	}

	// Insertion
	void AddHead(const T& data) {
		if(count == 0) {
			Node<T>* newNode = new Node<T>();
			newNode->data = data;
			head = newNode;
			tail = newNode;
			head->next = nullptr;
			head->prev = nullptr;
			newNode = nullptr;
			count++;
		}
		else {
			Node<T>* newNode = new Node<T>();
			newNode->data = data;
			newNode->prev = nullptr;
			newNode->next = head;
			head->prev = newNode;
			head = head->prev;
			newNode = nullptr;
			count++;
		}
	}
	void AddTail(const T& data) {
		if(count == 0) {
			Node<T>* newNode = new Node<T>();
			newNode->data = data;
			head = newNode;
			tail = newNode;
			head->next = nullptr;
			head->prev = nullptr;
			newNode = nullptr;
			count++;
		}
		else {
			Node<T>* newNode = new Node<T>();
			newNode->data = data;
			newNode->prev = tail;
			newNode->next = nullptr;
			tail->next = newNode;
			tail = tail->next;
			count++;
		}
	}

	// Removal
	bool RemoveHead() {
		if(head == nullptr) {
			return false;
		}
		if(head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
			count = 0;
			return true;
		}
		else {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
			count--;
			return true;
		}
	}
	bool RemoveTail() {
		if(tail == nullptr) {
			return false;
		}
		if(head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
			count = 0;
			return true;
		}
		else {
			Node<T>* temp = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete temp;
			temp = nullptr;
			return true;
		}
	}
	void Clear() {
		while(head != nullptr) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if(this == &other) {
			return *this;
		}
		while(head != nullptr) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
		tail = nullptr;
		count = other.count;
		head = other.head;
		tail = other.tail;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if(this == &rhs) {
			return *this;
		}
		while(head != nullptr) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
		tail = nullptr;
		Node<T>* temp = rhs.head;
		if(temp == nullptr) {
			head = nullptr;
			tail = nullptr;
			return *this;
		}

		head = new Node<T>();
		head->data = temp->data;
		head->prev = nullptr;
		head->next = nullptr;
		temp = temp->next;
		if(temp == nullptr) {
			tail = head;
			return *this;
		}
		tail = new Node<T>();
		tail->data = temp->data;
		tail->prev = head;
		tail->next = nullptr;
		head->next = tail;
		temp = temp->next;
		while(temp != nullptr) {
			Node<T>* new_node = new Node<T>();
			new_node->data = temp->data;
			new_node->prev = tail;
			new_node->next = nullptr;
			tail->next = new_node;
			tail = tail->next;
			new_node = nullptr;
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list) {
		this->count = list.count;
		Node<T>* temp = list.head;
		if(temp == nullptr) {
			head = nullptr;
			tail = nullptr;
			return;
		}

		this->head = new Node<T>();
		head->data = temp->data;
		head->prev = nullptr;
		head->next = nullptr;
		temp = temp->next;
		if(temp == nullptr) {
			tail = head;
			return;
		}
		this->tail = new Node<T>();
		tail->data = temp->data;
		tail->prev = head;
		tail->next = nullptr;
		head->next = tail;
		temp = temp->next;
		while(temp != nullptr) {
			Node<T>* new_node = new Node<T>();
			new_node->data = temp->data;
			new_node->prev = tail;
			new_node->next = nullptr;
			tail->next = new_node;
			tail = tail->next;
			new_node = nullptr;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		count = other.count;
		head = other.head;
		tail = other.tail;
		other.count = 0;
		other.head = nullptr;
		other.tail = nullptr;
	}
	~LinkedList() {
		count = 0;
		while(head != nullptr) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
		tail = nullptr;
	}

private:
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};


