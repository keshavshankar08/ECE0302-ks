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
	headPtr = nullptr;
	currentSize = 0;
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
	if(headPtr == nullptr){
		return true;
	}
	else{
		return false;
	}
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
	//if its empty
	if(isEmpty()){
		//create new node and set it as head
		headPtr = new Node<ItemType>(newItem);
		currentSize++;
	}
	else{
		//create new node, set item to newItem and its next to the current head
		Node<ItemType> *newPtr = new Node<ItemType>(newItem, headPtr);

		//update head and size
		headPtr = newPtr;
		currentSize++;
	}

	return true;
}  // end push

// TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const
{
	//if not empty, get top
	if(isEmpty() == false){
		return headPtr->getItem();
	}
	//else, throw error
	else{
		throw logic_error("error peek");
	}
}  // end peek

// TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	//if not empty
	if(isEmpty() == false){
		headPtr = headPtr->getNext();
		currentSize--;

		return true;
	}
	//if empty
	else{
		return false;
	}

}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
	//update head and size
	headPtr = nullptr;
	currentSize = 0;
}  // end clear

