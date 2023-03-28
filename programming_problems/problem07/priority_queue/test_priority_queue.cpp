#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "sorted_list.hpp"
#include "priority_queue.hpp"

TEST_CASE("Testing Priority Queue", "[priority queue]") {
  typedef SortedList<int, List<int>> SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;

  //testing highest element at end
  for(int i = 0; i < 50; i++){
    pq.add(i+1);
  }
  REQUIRE(pq.peek() == 50);

  //testing removed items from top
  for(int j = 0; j < 5; j++){
    pq.remove();
  }
  REQUIRE(pq.peek() == 45);

  //clear priority queue and check empty
  for(int k = 0; k < 45; k++){
    pq.remove();
  }
  REQUIRE(pq.isEmpty());
}
