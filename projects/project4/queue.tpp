#include "queue.hpp"

template <typename T, typename L>
void Queue<T,L>::enqueue(const T& item)
{
  internal_list.insert(0, item);
}

template <typename T, typename L>
void Queue<T,L>::dequeue()
{
  if(isEmpty()){
    throw std::range_error("queue is empty in dequeue");
  }
  internal_list.remove(internal_list.getLength() - 1);
}

template <typename T, typename L>
T Queue<T,L>::peekFront()
{
  if(isEmpty()){
    throw std::range_error("queue is empty in dequeue");
  }
  return internal_list.getEntry(internal_list.getLength() - 1);
}

template <typename T, typename L>
bool Queue<T,L>::isEmpty() const
{
  return internal_list.isEmpty();
}

