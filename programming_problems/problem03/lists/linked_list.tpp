#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  head = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  head = x.head;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList& x) 
{
  std::swap(head,x.head);
}

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

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  //flag for success
  bool flag = false;
  if((position == 0 && size == 0) || (position < size)){
    Node<T>* arr = new Node<T>;

    //when size is 0 (first element being added)
    if(head == nullptr){
      size++;
      arr.setItem(item);
      head = arr;
    }
    //when size > 1 already (already elements exist)
    else{
      size++;
      //loop till at position
      arr = head;
      for(int i = 0; i < position; i++){
        arr.next();
      }

      //once at position, add new node
      Node<T>* newNode = new Node<T>;
      arr.setNext(newNode);//set last element to new node
      newNode.setItem(item);//set new node
      newNode.setNext(arr.getNext());//set new 
    }

    flag = true;

  }

  return flag;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  //flag for success
  bool flag = false;
  if(size > 0 && position < size){
    Node<T>* arr = new Node;
    size--;

    //loop till at position
    arr = head;
    for(int i = 0; i < position; i++){
      arr.next();
    }

    //once at position, remove node
    arr.setNext(arr.next().next());//set element after deleted one as next
    arr.next();
    newNode.setItem(nullptr);//delete next node

    flag = true;

  }

  return flag;
}

template <typename T>
void LinkedList<T>::clear()
{
  T* temp = new T[0];
  head = temp; 
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  if(size > 0 && position < size){
    Node<T>* arr = new Node;

    //loop till at position
    arr = head;
    for(int i = 0; i < position + 1; i++){
      arr.next();
    }

    //once at position, get node
    return arr.getItem();
  }
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  if(size > 0 && position < size){
    Node<T>* arr = new Node;

    //loop till at position
    arr = head;
    for(int i = 0; i < position + 1; i++){
      arr.next();
    }

    //once at position, get node
    return arr.getItem();
  }
}
