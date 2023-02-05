#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Test Default Constructor", "[DynamicBag]"){
  DynamicBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty() == true);
}

TEST_CASE("Test Copy Constructor", "[DynamicBag]"){
  DynamicBag<int> b1;
  REQUIRE(b1.add(1) == true);
  DynamicBag<int> b2(b1);
  REQUIRE(b2.getCurrentSize() == 1);
}

TEST_CASE("Test Overload Operator", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  DynamicBag<int> b2 = b1;
  REQUIRE(b2.getCurrentSize() == 1);
}

TEST_CASE("Test Swap", "[DynamicBag]"){
  DynamicBag<int> b1;
  DynamicBag<int> b2;
  b2.add(1);
  b1.swap(b2);
  REQUIRE(b1.getCurrentSize() == 1);
}

TEST_CASE("Test Add", "[DynamicBag]"){
  DynamicBag<int> b1;
  REQUIRE(b1.add(1) == true);
  REQUIRE(b1.add(2) == true);
  REQUIRE(b1.add(3) == true);
  REQUIRE(b1.contains(1) == true);
  REQUIRE(b1.contains(2) == true);
  REQUIRE(b1.contains(3) == true);
  REQUIRE(b1.getCurrentSize() == 3);
}

TEST_CASE("Test Remove", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  b1.add(2);
  REQUIRE(b1.remove(1) == true);
  REQUIRE(b1.contains(1) == false);
  REQUIRE(b1.getCurrentSize() == 1);
}

TEST_CASE("Test checkEmpty", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  REQUIRE(b1.remove(1) == true);
  REQUIRE(b1.isEmpty() == true);
  REQUIRE(b1.getCurrentSize() == 0);
}

TEST_CASE("Test getSize", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  b1.add(2);
  b1.add(3);
  b1.add(4);
  REQUIRE(b1.getCurrentSize() == 4);
}

TEST_CASE("Test conatins", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  REQUIRE(b1.contains(1) == true);
  REQUIRE(b1.getCurrentSize() == 1);
}

TEST_CASE("Test clear", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  b1.add(2);
  b1.clear();
  REQUIRE(b1.getCurrentSize() == 0);
  REQUIRE(b1.isEmpty() == true);
}

TEST_CASE("Test frequency", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  b1.add(2);
  b1.add(1);
  b1.add(2);
  REQUIRE(b1.getFrequencyOf(2) == 2);
}


