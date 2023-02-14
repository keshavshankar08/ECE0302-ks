#include "array_list.hpp"

/**
 * @brief Construct a new Array List< T>:: Array List object
 * 
 * @tparam T 
 */
template <typename T>
ArrayList<T>::ArrayList() {
  arr = new T[0];
  size = 0;
}
/**
 * @brief Destroy the Array List< T>:: Array List object
 * 
 * @tparam T 
 */
template <typename T>
ArrayList<T>::~ArrayList() {

}
/**
 * @brief Construct a new Array List< T>:: Array List object
 * 
 * @tparam T 
 * @param rhs 
 */
template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs){
  arr = rhs.arr;
  size = rhs.size;
}

/**
 * @brief override equal operator
 * 
 * @tparam T 
 * @param rhs 
 * @return ArrayList<T>& 
 */
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList rhs){
  swap(rhs);
  return *this;
}

/**
 * @brief swap elements
 * 
 * @tparam T 
 * @param rhs 
 */
template <typename T>
void ArrayList<T>::swap(ArrayList& rhs) {
  std::swap(arr,rhs.arr);
  std::swap(size,rhs.size);
}

/**
 * @brief check if empty
 * 
 * @tparam T 
 * @return true 
 * @return false 
 */
template <typename T>
bool ArrayList<T>::isEmpty() const noexcept {
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
std::size_t ArrayList<T>::getLength() const noexcept {
  return size;
}

/**
 * @brief insert item to list
 * 
 * @tparam T 
 * @param position 
 * @param item 
 * @return true 
 * @return false 
 */
template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){
  //if position invalid, return false
  if(position < 0 || position > size){
    return false;
  }
  //if position valid, continue
  else{
    //update size, create temp array
    size++;
    T* arrCopy = new T[size];

    //loop and copy elements
    for(int i = 0; i < size; i++){
      if(i < position){
        *(arrCopy + i) = *(arr + i);
      }
      else if(i == position){
        *(arrCopy + i) = item;
      }
      else{
        *(arrCopy + i) = *(arr + i - 1);
      }
    }

    //update array
    arr = arrCopy;

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
bool ArrayList<T>::remove(std::size_t position){
  //if position invalid, return false
  if(position < 0 || position > size){
    return false;
  }
  //if position valid, continue
  else{
    //update size, create temp array
    size--;
    T* arrCopy = new T[size];

    //loop and copy elements
    for(int i = 0; i < size; i++){
      if(i < position){
        *(arrCopy + i) = *(arr + i);
      }
      else{
        *(arrCopy + i) = *(arr + i + 1);
      }
    }

    //update array
    arr = arrCopy;

    return true;
  }
}

/**
 * @brief clear elements
 * 
 * @tparam T 
 */
template <typename T>
void ArrayList<T>::clear() {
  //create new 
  T* arrCopy = new T[0];
  size = 0;
  arr = arrCopy;
}

/**
 * @brief get item from list
 * 
 * @tparam T 
 * @param position 
 * @return T 
 */
template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
  if((position >= 0) && (position < size)){
    return *(arr + position);
  }
  else{
    return T();
  }
}

/**
 * @brief set item in list
 * 
 * @tparam T 
 * @param position 
 * @param newValue 
 */
template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
  if((position >= 0) && (position < size)){
    *(arr + position) = newValue;
  }
}