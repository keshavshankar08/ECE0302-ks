#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("Test Default Constructor", "[DynamicBag]"){
  LimitedSizeBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty() == true);
}

TEST_CASE("Test Add", "[DynamicBag]"){
  LimitedSizeBag<int> b1;
  REQUIRE(b1.add(1) == true);
  REQUIRE(b1.add(2) == true);
  REQUIRE(b1.add(3) == true);
  REQUIRE(b1.contains(1) == true);
  REQUIRE(b1.contains(2) == true);
  REQUIRE(b1.contains(3) == true);
  REQUIRE(b1.getCurrentSize() == 3);
}

TEST_CASE("Test Remove", "[DynamicBag]"){
  LimitedSizeBag<int> b1;
  b1.add(1);
  b1.add(2);
  REQUIRE(b1.remove(1) == true);
  REQUIRE(b1.contains(1) == false);
  REQUIRE(b1.getCurrentSize() == 1);
}

TEST_CASE("Test checkEmpty", "[DynamicBag]"){
  LimitedSizeBag<int> b1;
  b1.add(1);
  REQUIRE(b1.remove(1) == true);
  REQUIRE(b1.isEmpty() == true);
  REQUIRE(b1.getCurrentSize() == 0);
}

TEST_CASE("Test getSize", "[DynamicBag]"){
  LimitedSizeBag<int> b1;
  b1.add(1);
  b1.add(2);
  b1.add(3);
  b1.add(4);
  REQUIRE(b1.getCurrentSize() == 4);
}

TEST_CASE("Test contains", "[DynamicBag]"){
  LimitedSizeBag<int> b1;
  b1.add(1);
  REQUIRE(b1.contains(1) == true);
  REQUIRE(b1.getCurrentSize() == 1);
}

TEST_CASE("Test clear", "[DynamicBag]"){
  LimitedSizeBag<int> b1;
  b1.add(1);
  b1.add(2);
  b1.clear();
  REQUIRE(b1.getCurrentSize() == 0);
  REQUIRE(b1.isEmpty() == true);
}

TEST_CASE("Test frequency", "[DynamicBag]"){
  LimitedSizeBag<int> b1;
  b1.add(1);
  b1.add(2);
  b1.add(1);
  b1.add(2);
  REQUIRE(b1.getFrequencyOf(2) == 2);
}

TEST_CASE("Test maxsize", "[DynamicBag]"){
  LimitedSizeBag<int> b1;
  for(int i = 0; i < 100; i++){
    REQUIRE(b1.add(1) == TRUE);
  }
  REQUIRE(b1.getCurrentSize() == 100);
  REQUIRE(b1.add(1) == false);
}