#include "sorted_linked_list.hpp"
#include <stdexcept>

/**
 * @brief Construct a new Sorted Linked List< T>:: Sorted Linked List object
 * 
 * @tparam T 
 */
template <typename T>
SortedLinkedList<T>::SortedLinkedList(): LinkedList<T>()
{
}

/**
 * @brief Construct a new Sorted Linked List< T>:: Sorted Linked List object
 * 
 * @tparam T 
 * @param unsorted_list 
 */
template <typename T>
SortedLinkedList<T>::SortedLinkedList(LinkedList<T> unsorted_list) : LinkedList<T>(unsorted_list)
{
  //create blank array with same size as linked list
	T listCopy[unsorted_list.getLength()];

	//copy over elements from linked list to array
	for(int i = 0; i < unsorted_list.getLength(); i++){
		listCopy[i] = unsorted_list.getEntry(i);
	}

	//sort the array using quick sort algorithm
	int a, b, minPos; 
	int n = sizeof(listCopy)/sizeof(listCopy[0]); 

	//loop over array
  for(a = 0; a < n - 1; a++){
    minPos = a; 

    //loop over elements past current element
    for(b = a+1; b < n; b++){
      //set as min element if less than other elements
      if(listCopy[b] < listCopy[minPos]){
        minPos = b;
      }
    }

    //swap the vars at the positions
    if(minPos != a){
      int temp = listCopy[minPos]; 
      listCopy[minPos] = listCopy[a]; 
      listCopy[a] = temp; 
    }
  }

	//store items from array into the member linked list (which was created in constructor declaration)
	for(int i = 0; i < unsorted_list.getLength(); i++){
    LinkedList<T>::setEntry(i, listCopy[i]);
	} 
}

/**
 * @brief Construct a new Sorted Linked List< T>:: Sorted Linked List object
 * 
 * @tparam T 
 * @param x 
 */
template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> & x):
  LinkedList<T>(x)
{
}

/**
 * @brief overrides = operator
 * 
 * @tparam T 
 * @param x 
 * @return SortedLinkedList<T>& 
 */
template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(SortedLinkedList<T> x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

/**
 * @brief Destroy the Sorted Linked List< T>:: Sorted Linked List object
 * 
 * @tparam T 
 */
template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically
}

/**
 * @brief checks if list empty
 * 
 * @tparam T 
 * @return true 
 * @return false 
 */
template <typename T>
bool SortedLinkedList<T>::isEmpty() const noexcept
{
  return LinkedList<T>::isEmpty();
}

/**
 * @brief gets length of list
 * 
 * @tparam T 
 * @return std::size_t 
 */
template <typename T>
std::size_t SortedLinkedList<T>::getLength() const noexcept
{
  return LinkedList<T>::getLength();
}

/**
 * @brief inserts item are sorted position
 * 
 * @tparam T 
 * @param item 
 */
template <typename T>
void SortedLinkedList<T>::insert(const T& item)
{
  //var for position to insert
  int position = 0;

  //if list empty, insert item at start
  if(isEmpty()){
    LinkedList<T>::insert(position, item);
  }
  //else, elements already in list
  else{
    //loop until at correct insertion point
    while(position < getLength() && item > getEntry(position)){
      position++;
    }
    
    //insert element at point
    LinkedList<T>::insert(position, item);
  }
}

/**
 * @brief removes item in list
 * 
 * @tparam T 
 * @param item 
 */
template <typename T>
void SortedLinkedList<T>::remove(const T& item)
{
  //check if item exits
  bool exists = false;
  for(int i = 0; i < getLength(); i++){
    if(getEntry(i) == item){
      exists = true;
      break;
    }
  }

  //if list empty or item not in list, throw exception
  if(isEmpty() || exists == false){
    throw std::range_error("empty list in remove");
  }
  //else, it exists
  else{
    //loop until at element to delete
    int position = 0;//var for position to remove
    while(position < getLength()){
      //at item so break out
      if(getEntry(position) == item){
        break;
      }
      //keep looping
      else{
        position++;
      }
    }

    //remove element at position
    LinkedList<T>::remove(position);
  }
}

/**
 * @brief removes item at position
 * 
 * @tparam T 
 * @param position 
 */
template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
  //if list empty or position out of bounds, throw exception
  if(isEmpty() || position < 0 || position >= getLength()){
    throw std::range_error("empty list in removeAt");
  }
  else{
    //remove element at position
    LinkedList<T>::remove(position);
  }
}

/**
 * @brief clears list
 * 
 * @tparam T 
 */
template <typename T>
void SortedLinkedList<T>::clear()
{
  //clear all data
  LinkedList<T>::clear();
}

/**
 * @brief gets element at position
 * 
 * @tparam T 
 * @param position 
 * @return T 
 */
template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position) const
{
  //throw exception if empty or out of bounds
  if(isEmpty() || position < 0 || position >= getLength()){
    throw std::range_error("empty/out of bounds in getEntry");
  }
  //else just return the entry at a position
  else{
    return LinkedList<T>::getEntry(position);
  }
}

/**
 * @brief gets position of item
 * 
 * @tparam T 
 * @param item 
 * @return long int 
 */
template <typename T>
long int SortedLinkedList<T>::getPosition(const T& item)
{
  //check if item exits
  bool exists = false;
  for(int i = 0; i < getLength(); i++){
    if(getEntry(i) == item){
      exists = true;
      break;
    }
  }

  //throw exception if doesnt exist or empty list
  if(exists == false || isEmpty()){
    return -1;
    throw std::range_error("empty/doesn't exist of bounds in getEntry");
  }
  
  //step through until item found
  int position = 0;//position of item
  while(position < getLength() && item > getEntry(position)){
    position++;
  }

  return position;
}
