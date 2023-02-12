#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE("Deafult constructor test", "[ArrayList]" ) {
  ArrayList<int> list;
  REQUIRE(list.getLength() == 0);
  REQUIRE(list.isEmpty() == true);
}

TEST_CASE("Destructor test", "[ArrayList]" ) {
  ArrayList<int> list;
  REQUIRE(list.getLength() == 0);
}

TEST_CASE("Copy constructor test", "[ArrayList]" ) {
  ArrayList<int> list;
  list.insert(0,1);
  ArrayList<int> list2(list);
  REQUIRE(list2.getLength() == 1);
}

TEST_CASE("Copy assignment test", "[ArrayList]" ) {
  ArrayList<int> list;
  list.insert(0,1);
  ArrayList<int> list2;
  list2 = list;
  REQUIRE(list2.getLength() == 1);
}

TEST_CASE("Remove test", "[ArrayList]" ) {
  ArrayList<int> list;
  list.insert(0,1);
  list.remove(0);
  REQUIRE(list.isEmpty() == true);
}

TEST_CASE("Get entry test", "[ArrayList]" ) {
  ArrayList<int> list;
  list.insert(0,1);
  REQUIRE(list.getEntry(0) == 1);
}

TEST_CASE("Set entry test", "[ArrayList]" ) {
  ArrayList<int> list;
  list.insert(0,1);
  list.setEntry(0,2);
  REQUIRE(list.getEntry(0) == 2);
}