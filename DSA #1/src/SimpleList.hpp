//
//  SimpleList.h
//  
//
//  Created by scott on 4/3/17.
// Student Name:
// Zhekai Jin
// Class:
// Data structure and Algorithm I

#ifndef __SL_HPP
#define __SL_HPP

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class SimpleList {
public:
    // pure virtual function providing template for derived class to override;
	SimpleList (string name);
    //set the listname and constructrer to innitialize everthing;
    virtual void push(T d)=0;
    virtual T pop()=0;
    virtual int getSize() = 0;
    string listName;
protected:
    // set the three function as required and also a int size to trace the size;
    void insert_rear(T d);
    void insert_front(T d);
    T   remove_front();
    // three functions are all ensured to be constant time operation;
    int size;
private:
    //set up a new class node as required, one field to data and another to pointer point to nex node;
    class Node {
	public:
		Node(T d, Node * ptr) {
			this->data = d;
			this->next = ptr;
		}
        T data;
        Node * next;
    };
    // declare pointer point to front and rear of the linked list;
    Node * front, * rear;
};

// Derived classes, override push and pop for each stack and queue while set public getsize function allowed for later use;
template <typename T>
class Stack : public SimpleList<T> {
public:
    Stack(string name);
	void push (T d);
	T pop ();
	int getSize();
};

template <typename T>
class Queue : public SimpleList<T> {
public:
    Queue(string name);
	void push (T d);
	T pop ();
	int getSize();
};


//define all the functions declared;

/*simplelist constructer to initilize everthing, size to 0 and list's name with front and rear as nullprt since it is an empty list;*/
template <typename T>
SimpleList<T>::SimpleList (string name) {
	this->size = 0;
    this->listName = name;
    this->front = nullptr;
    this->rear = nullptr;
}


//insert from rear , basically push function for queue;
template <typename T>
void SimpleList<T>::insert_rear (T d) {
    //create a new node point to the null;
    Node* temp = new Node(d, nullptr);
    //if its an emptylist set the front and rear to the new node, otherwise just set rear to the new temp;
	if (this->size == 0) {
		this->rear = temp;
		this->front = temp;
	} else {
	    this->rear->next = temp;
	}
}

//function to insert from front which is the push funciton for stacks;
template <typename T>
void SimpleList<T>::insert_front(T d) {
    //create a new node and make front point to it
    Node* temp = new Node(d, this->front);
    this->front = temp;
}

//function to remove from front which is the pop funciton to both stack and queue;
template <typename T>
T   SimpleList<T>::remove_front () {
    //remove the front data(pop) by making the front point to the next node
    Node * temp = this->front;
    this->front = temp->next;
    T data = temp->data;
    // free the unused memory and return the data removed
    delete temp;
    return data;
}

//stack constructer;
template <typename T>
Stack<T>::Stack(string name) : SimpleList<T>(name) {
}

//stack push: insert from the front and increment the data;
template <typename T>
void Stack<T>::push(T d) {
    this->insert_front(d);
    this->size++;
}

//stack pop:remove from the front and decrement the size;
template <typename T>
T Stack<T>::pop() {
    this->size--;
    return this->remove_front();
}

//return the size(protected) for getsize();
template <typename T>
int Stack<T>::getSize () {
	return this->size;
}

//queue constructer;
template <typename T>
Queue<T>::Queue(string name) : SimpleList<T>(name) {
}

//queue push : insert from the end and increment the size;
template <typename T>
void Queue<T>::push(T d) {
    this->insert_rear(d);
    this->size++;
}

//queue pop: remove from the front and decrement the size;
template <typename T>
T Queue<T>::pop() {
    this->size--;
    return this->remove_front();
}

//return the size(protected) for getsize;
template <typename T>
int Queue<T>::getSize () {
	return this->size;
}

#endif
