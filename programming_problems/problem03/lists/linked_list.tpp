#include "linked_list.hpp"

/**
 * @brief Construct a new Linked List< T>:: Linked List object
 * 
 * @tparam T 
 */
template <typename T>
LinkedList<T>::LinkedList()
{
  head = nullptr;
  size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  
}

/**
 * @brief Construct a new Linked List< T>:: Linked List object
 * 
 * @tparam T 
 * @param x 
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  head = x.head;
  size = x.size;
}

/**
 * @brief euqal override operator
 * 
 * @tparam T 
 * @param x 
 * @return LinkedList<T>& 
 */
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x);
  return *this;
}

/**
 * @brief swap nodes
 * 
 * @tparam T 
 * @param x 
 */
template <typename T>
void LinkedList<T>::swap(LinkedList& x) 
{
  std::swap(head,x.head);
  std::swap(size,x.size);
}

/**
 * @brief check if list empty
 * 
 * @tparam T 
 * @return true 
 * @return false 
 */
template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  if(size != 0){
    return false;
  }
  else{
    return true;
  }
}

/**
 * @brief get length of list
 * 
 * @tparam T 
 * @return std::size_t 
 */
template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return size;
}

/**
 * @brief add item to list
 * 
 * @tparam T 
 * @param position 
 * @param item 
 * @return true 
 * @return false 
 */
template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  //if invalid position
  if(position < 0 || position > size){
    return false;
  }
  //if valid and no items yet
  else if(position == 0 && size == 0){
    //create new node
    Node<T>* newNode = new Node<T>(item);
    //set as head
    head = newNode;
    size++;
    return true;
  }
  //if valid and inserting at 0
  else if(position == 0 && size > 0){
    //create new node
    Node<T>* tempNode = head;
    Node<T>* newNode = new Node<T>(item);
    newNode->setNext(tempNode->getNext());
    head = newNode;
    size++;
    return true;
  }
  //if valid and inserting elsewhere
  else{
    //create new node
    Node<T>* newNode = new Node<T>(item);
    Node<T>* tempNode = head;
    //loop till at position
    for(int i = 0; i < position - 1; i++){
      tempNode = tempNode->getNext();
    }
    //set previous head and head of new node
    newNode->setNext(tempNode->getNext());
    tempNode->setNext(newNode);
    size++;
    return true;
  }
}

/**
 * @brief remove item from list
 * 
 * @tparam T 
 * @param position 
 * @return true 
 * @return false 
 */
template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  //if invalid position
  if(position < 0 || position > size){
    return false;
  }
  else if(position == 0 && size == 0){
    return false;
  }

  //if valid and removing first element
  if(position == 0){
    Node<T>* tempNode = head;
    head = tempNode->getNext();
    delete tempNode;
    size--;
    return true;
  }
  //if valid and removing other elements
  else{
    Node<T>* tempNode = head;
    //loop till at position
    for(int i = 0; i < position - 1; i++){
      tempNode = tempNode->getNext();
    }
    //once at position, delete node
    Node<T>* deletionNode = tempNode->getNext();//create deletion point
    tempNode->setNext(deletionNode->getNext());//connect temp node next to 1 after deletion node
    delete deletionNode;
    size--;
    return true;
  }
}

/**
 * @brief clear nodes
 * 
 * @tparam T 
 */
template <typename T>
void LinkedList<T>::clear()
{
  Node<T> *temp = new Node<T>;
  head = temp; 
  size = 0;
}

/**
 * @brief get an item of node
 * 
 * @tparam T 
 * @param position 
 * @return T 
 */
template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //if valid position
  if(position >= 0 && position < size){
    Node<T>* tempNode = head;

    //loop till at position
    for(int i = 0; i < position; i++){
      tempNode = tempNode->getNext();
    }

    //once at position, get node
    return tempNode->getItem();
  }
  else{
    return T();
  }
}

/**
 * @brief set an item of node
 * 
 * @tparam T 
 * @param position 
 * @param newValue 
 */
template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //if valid position
  if(position >= 0 && position < size){
    Node<T>* tempNode = head;

    //loop till at position
    for(int i = 0; i < position; i++){
      tempNode = tempNode->getNext();
    }

    //once at position, set node
    tempNode->setItem(newValue);
  }
}
