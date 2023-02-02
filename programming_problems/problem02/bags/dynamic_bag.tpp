#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() {
    bagArr = new T[0];
    size = 0;
}
  

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag& x){

}
    
template<typename T>
DynamicBag<T>::~DynamicBag(){}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> x)
{  
  return *this;
}

template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x){}


template<typename T>
bool DynamicBag<T>::add(const T& item)
{
  //create new array with 1 larger size
  T* bagArrCopy = new T[size+1];
  size++;

  //set last element to item
  *(bagArrCopy + size) = item;

  //copy over elements from old array
  for(int i = 0; i < size-1; i++){
    *(bagArrCopy + i) = *(bagArr + i);
  }

  //set old array to new array
  *bagArr = *bagArrCopy;

  //check if last added element is item
  if(*(bagArrCopy + size) == item){
    return true;
  }
  else{
    return false;
  }
}


template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  //flag for if found
  bool flag = false;

  //count number occurances of item
  int numOccurances = 0;
  for(int i = 0; i < size; i++){
    //if found, increment count and set flag to true
    if(*(bagArr + i) == item){
      flag = true;
      numOccurances++;
    }
  }

  //create new array with new size
  T* bagArrCopy = new T[size-numOccurances];
  size -= numOccurances;

  //copy over elements that aren't the item
  int currItem = 0;
  for(int j = 0; j < size; j++){
    if(*(bagArr + j) == item){
      *(bagArrCopy + currItem) = *(bagArr + j);
      currItem++;
    }
  }

  //set old array to new array
  *bagArr = *bagArrCopy;

  return flag;
}


template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  return false;
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return size;
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  //flag for occurance
  bool flag = false;

  //loop over entire array
  for(int i = 0; i < size; i++){
    //if found, set flag true
    if(*(bagArr + i) == item){
      flag = true;
    }
  }
  return flag;
}

template<typename T>
void DynamicBag<T>::clear(){}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  //count number occurances of item
  int numOccurances = 0;
  for(int i = 0; i < size; i++){
    //if found, increment count and set flag to true
    if(*(bagArr + i) == item){
      numOccurances++;
    }
  }
  return numOccurances;
};
