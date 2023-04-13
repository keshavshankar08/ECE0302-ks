#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() {
  //error if queue empty
  if(queue.empty()){
    throw std::runtime_error("queue empty");
  }

  //get copy of front and back of queue
  State<T> rootCopy = queue.front();
  State<T> tailCopy = queue.back();

  //replace root with tail and delete tail
  queue.at(0) = tailCopy;
  queue.pop_back();

  //sort root to correct spot
  int pos = 1;
  //while not at end
  while((pos*2)-1 < queue.size()){
    //if left child < parent, swap
    if(queue.at((pos*2)-1).getFCost() < queue.at(pos-1).getFCost()){
      swap((pos*2)-1, pos-1);
    }
    //if right child < parent, swap
    else if(queue.at(pos*2).getFCost() < queue.at(pos-1).getFCost() && (pos*2) < queue.size()){
      swap(pos*2, pos-1);
    }
    else{
      return rootCopy;
    }
  }

  //return popped element
  return rootCopy;
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {
  //add new obj to end
  State<T> newState = {p, cost, heur};
  queue.push_back(newState);

  //sort new state to correct spot
  int pos = queue.size();
  //while not at root yet
  while(pos/2 >= 1){
    //if parent is greater than current, swap
    if(queue.at((pos/2)-1).getFCost() > queue.at(pos-1).getFCost()){
      swap((pos/2)-1, pos-1);
      pos /= 2;
    }
    //else its in the right spot already
    else{
      return;
    }
  }
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
    if(queue[i].getValue() == p){
      return true;
    }
  }
  
  //else not found
  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {
  for(int i = 0; i < queue.size(); i++){
    if(queue.at(i).getValue() == p && queue.at(i).getPathCost() > cost){
      queue.at(i).updatePathCost(cost);
      for(int j = i - 1; j >= 0; j--){
        if(i == 0){
          return;
        }
        else if(queue.at(j).getFCost() > queue.at(i).getFCost()){
          swap(i,j);
        }
      }
    }
  }

  return;
}

template <typename T>
void frontier_queue<T>::swap(int pos1, int pos2){
  State<T> temp = queue.at(pos1);
  queue.at(pos1) = queue.at(pos2);
  queue.at(pos2) = temp;
}


