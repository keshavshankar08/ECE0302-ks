#include "limited_size_bag.hpp"

/**
 * @brief Construct a new Limited Size Bag< T>:: Limited Size Bag object
 * 
 * @tparam T 
 */
template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() {
  bagArr = new T[0];
  size = 0;
}
  
/**
 * @brief add param to object array
 * 
 * @tparam T 
 * @param item 
 * @return true 
 * @return false 
 */
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  //if at max size
  if(size == maxsize){
    return false;
  }

  //create new array with 1 larger size
  T* bagArrCopy = new T[size+1];
  size++;

  //copy over elements from old array
  for(int i = 0; i < size - 1; i++){
    *(bagArrCopy + i) = *(bagArr + i);
  }

  //set last element to item
  *(bagArrCopy + size - 1) = item;

  //set old array to new array
  bagArr = bagArrCopy;

  //check if last added element is item
  if(*(bagArrCopy + size - 1) == item){
    return true;
  }
  else{
    return false;
  }
}

/**
 * @brief remove all param from object array
 * 
 * @tparam T 
 * @param item 
 * @return true 
 * @return false 
 */
template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  //flag for if item found
  bool flag = false;
  for(int j = 0; j < size; j++){
    if(*(bagArr + j) == item){
      flag = true;
      break;
    }
  }

  //remove element if exists
  if(flag == true){
    //create copy array
    T* bagArrCopy = new T[size-1];

    //position of copy array
    int currPos = 0;

    //flag when passed first occurance
    bool passedFirstOccurance = false;

    //loop through original array
    for(int i = 0; i < size; i++){
      //if not item, add to copy array
      if(*(bagArr + i) != item){
        *(bagArrCopy + currPos) = *(bagArr + i);
        currPos++;
      }
      //if item, but first occurance of it, skip iteration
      else if(*(bagArr + i) == item && passedFirstOccurance == false){
        passedFirstOccurance = true;
      }
      //if item, but not first occurance, add to copy array
      else if(*(bagArr + i) == item && passedFirstOccurance == true){
        *(bagArrCopy + currPos) = *(bagArr + i);
        currPos++;
      }
    }

    //set old array to new array and change size
    bagArr = bagArrCopy;
    size -= 1;
  }

  return flag;
}

/**
 * @brief check if object array empty
 * 
 * @tparam T 
 * @return true 
 * @return false 
 */
template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  if(size != 0 && bagArr != nullptr){
    return false;
  }
  else{
    return true;
  }
}

/**
 * @brief get size of object array
 * 
 * @tparam T 
 * @return std::size_t 
 */
template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return size;
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
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

/**
 * @brief clear object array
 * 
 * @tparam T 
 */
template<typename T>
void LimitedSizeBag<T>::clear(){
  //create new 
  T* bagArrCopy = new T[0];
  size = 0;
  bagArr = bagArrCopy;
}

/**
 * @brief get number of occurances of param
 * 
 * @tparam T 
 * @param item 
 * @return std::size_t 
 */
template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
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
