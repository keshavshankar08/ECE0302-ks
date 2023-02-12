#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList() {
  arr = new T[0];
  size = 0;
}

template <typename T>
ArrayList<T>::~ArrayList() {

}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs){
  arr = rhs.arr;
  size = rhs.size;
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList rhs){
  swap(rhs);
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList& rhs) {
  std::swap(arr,rhs.arr);
  std::swap(size,rhs.size);
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept {
  if(size != 0 && arr != nullptr){
    return false;
  }
  else{
    return true;
  }
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept {
  return size;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){
  //flag for success
  bool flag = false;

  //if position valid, continue
  if((position == 0 && size == 0) || (position < size)){
    //store old size
    int oldPos = size;

    //update size, create temp array
    size++;
    T* arrCopy = new T[size];

    //loop to fill new array
    for(int i = 0; i < size; i++){
      if(i == position){
        *(arrCopy + i) = item;
        i++;
      }
      *(arrCopy + i) = *(arr + oldPos);
    }

    //update array
    arr = arrCopy;

    //update flag
    if(arr[position] == item){
      flag = true;
    }
  }

  return flag;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position){
  bool flag = false;
  if((position == 0 && size == 0) || (position < size)){
    flag = true;
  } 

  //if position valid
  if(flag == true){
    //store old size
    int oldPos = size;
    
    //update size, create temp array
    size--;
    T* arrCopy = new T[size];

    //track position of new arr
    int curPos = 0;

    //loop and copy elements except position
    for(int i = 0; i < oldPos; i++){
      if(i != position){
        *(arrCopy + curPos) = *(arr + i);
        curPos++;
      }
    }
  }

  return flag;
}

template <typename T>
void ArrayList<T>::clear() {
  //create new 
  T* arrCopy = new T[0];
  size = 0;
  arr = arrCopy;
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
  return *(arr + position);
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
  if((position == 0 && size == 0) || (position < size)){
    *(arr + position) = newValue;
  }
}