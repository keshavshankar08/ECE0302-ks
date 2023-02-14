#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE("Deafult constructor test", "[ArrayList]" ) {
  LinkedList<int> list;
  REQUIRE(list.getLength() == 0);
  REQUIRE(list.isEmpty() == true);
}

TEST_CASE("Copy constructor test", "[ArrayList]" ) {
  LinkedList<int> list;
  list.insert(0,1);
  LinkedList<int> list2(list);
  REQUIRE(list2.getLength() == 1);
}

TEST_CASE("Copy assignment test", "[ArrayList]" ) {
  LinkedList<int> list;
  list.insert(0,1);
  LinkedList<int> list2;
  list2 = list;
  REQUIRE(list2.getLength() == 1);
}

TEST_CASE("Remove end test", "[ArrayList]" ) {
  LinkedList<int> list;
  list.insert(0,1);
  list.remove(0);
  REQUIRE(list.isEmpty() == true);
}

TEST_CASE("Get entry test", "[ArrayList]" ) {
  LinkedList<int> list;
  list.insert(0,1);
  list.insert(1,2);
  REQUIRE(list.getEntry(0) == 1);
  REQUIRE(list.getEntry(1) == 2);
}

TEST_CASE("Set entry test", "[ArrayList]" ) {
  LinkedList<int> list;
  list.insert(0,1);
  list.setEntry(0,2);
  REQUIRE(list.getEntry(0) == 2);
}

TEST_CASE("Insert test", "[ArrayList]" ) {
  LinkedList<int> list;
  list.insert(0,1);
  list.insert(1,1);
  REQUIRE(list.getEntry(0) == 1);
  REQUIRE(list.getEntry(1) == 1);
}

TEST_CASE("Remove test", "[ArrayList]" ) {
  LinkedList<int> list;
  list.insert(0,1);
  list.insert(1,2);
  list.remove(0);
  REQUIRE(list.getEntry(0) == 2);
}