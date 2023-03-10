//  Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

// TODO: Implement the constructor here
template<class ItemType>
Stack<ItemType>::Stack() : headPtr(nullptr) 
{
	
}  // end default constructor

// TODO: Implement the destructor here
template<class ItemType>
Stack<ItemType>::~Stack()
{
	while(isEmpty() == false){
		pop();
	}
}  // end destructor

// TODO: Implement the isEmpty method here
template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	return headPtr == nullptr;
}  // end isEmpty

// TODO: Implement the size method here
template<class ItemType>
int Stack<ItemType>::size() const
{
	return currentSize;
}  // end size

// TODO: Implement the push method here
template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType> *newPtr = new Node<ItemType> (newItem, headPtr);
	headPtr = newPtr;
	newPtr = nullptr;
	currentSize++;
	return true;
}  // end push

// TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const
{
	if(isEmpty() == false){
		return headPtr->getItem();
	}
	else{
		throw logic_error("error1");
		return headPtr->getItem();
	}
}  // end peek

// TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	bool flag = false;
	if(isEmpty() == false){
		Node<ItemType> *deletePtr = headPtr;
		headPtr = headPtr->getNext();

		deletePtr->setNext(nullptr);
		delete deletePtr;
		deletePtr = nullptr;

		flag = true;
		currentSize--;
	}

	return flag;
}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
	Node<ItemType> *ptr = headPtr;

	while(ptr != NULL){
		ptr = headPtr;
		ptr = headPtr->getNext();
		delete ptr;
		headPtr = ptr;
	}
	
	currentSize = 0;
}  // end clear

