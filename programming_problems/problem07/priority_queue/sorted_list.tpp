#include "sorted_list.hpp"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
  // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> & x)
{
  plist = x.plist; // use copy assignment to implement copy construction
}

template <typename T, typename L>
SortedList<T, L>& SortedList<T, L>::operator=(SortedList<T, L> x)
{
  plist = x.plist;
  return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
  // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty() const noexcept
{
  return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength() const noexcept
{
  return plist.getLength();
}

template <typename T, typename L>
void SortedList<T, L>::insert(const T& item)
{
  //var for position to insert
  int position = 0;

  //if list empty, insert item at start
  if(isEmpty()){
    plist.List<T>::insert(position, item);
  }
  //else, elements already in list
  else{
    //loop until at correct insertion point
    while(position < getLength() && item > getEntry(position)){
      position++;
    }
    
    //insert element at point
    plist.List<T>::insert(position, item);
  }
}

template <typename T, typename L>
void SortedList<T, L>::remove(const T& item)
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
    plist.List<T>::remove(position);
  }
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
  plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
  plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position) const
{
  return plist.getEntry(position);
}

template <typename T, typename L>
long int SortedList<T, L>::getPosition(const T& newValue)
{
  //check if item exits
  bool exists = false;
  for(int i = 0; i < getLength(); i++){
    if(getEntry(i) == newValue){
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
  while(position < getLength() && newValue > getEntry(position)){
    position++;
  }

  return position;
}
