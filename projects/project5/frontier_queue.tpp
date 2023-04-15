#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() {
  //error if queue empty
  if(queue.empty()){
    throw std::logic_error("queue empty");
  }
  //if only 1 element in queue
  else if(queue.size() == 1){
    //just pop the one item
    State<T> first = queue.back();
    queue.pop_back();
    return first;
  }
  //if more than 1 element in queue
  else{
    //get copy of first and last element
    State<T> headCopy = queue.front();
    State<T> tailCopy = queue.back();

    //replace root with tail and delete tail
    queue.at(0) = tailCopy;
    queue.pop_back();

    //vars to keep track of swap vars
    int n = queue.size(), i = 0, parent = i, left = 2 * i + 1, right = 2 * i + 2;

    //while children not over size of list
    while(left < n && left > 0 && right < n){
      //if left child smaller, swap and set as new parent
      if(queue.at(left).getFCost() < queue.at(right).getFCost() && queue.at(left).getFCost() < queue.at(parent).getFCost()){
        swap(left, parent);
        parent = left;
      }
      //if right child smaller, swap and set as new parent
      else if(queue.at(right).getFCost() < queue.at(left).getFCost() && queue.at(right).getFCost() < queue.at(parent).getFCost()){
        swap(right, parent);
        parent = right;
      }
      //else, in order to break
      else{
        break;
      }

      //update vars for swap position
      i = parent;
      left = 2 * i + 1;
      right = 2 * i + 2;
    }

    //return popped element
    return headCopy;
  }
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {
  //create object with new data
  State<T> newState = {p, cost, heur};

  //case where queue empty
  if(empty()){
    queue.push_back(newState);
  }
  //else elements exist already
  else{
    //add state to last empty spot
    queue.push_back(newState);

    //vars for position of swap items
    int n = queue.size(), i = n - 1, parent = (i - 1) / 2;

    //loop until min at top
    while(queue.at(parent).getFCost() > queue.at(i).getFCost() && parent != 0){
      //swap elements and update position of new swap items
      swap(parent, i);
      i = parent;
      parent = (i - 1) / 2;
    }
  }

  return;
}

template <typename T>
bool frontier_queue<T>::empty() {
  return (queue.size() == 0);
}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) {
  //loop through queue
  for(int i = 0; i < queue.size(); i++){
    //if p in it, found
    if(queue.at(i).getValue() == p){
      return true;
    }
  }
  
  //else not found
  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {
  //loop through queue
  for(int i = 0; i < queue.size(); i++){
    //if element is p and cost is lower, replace it
    if(queue.at(i).getValue() == p && cost < queue.at(i).getPathCost()){
      queue.at(i).updatePathCost(cost);
    }
  }

  return;
}

//helper function to swap queue items
template <typename T>
void frontier_queue<T>::swap(int pos1, int pos2){
  State<T> temp = queue.at(pos1);
  queue.at(pos1) = queue.at(pos2);
  queue.at(pos2) = temp;
}


