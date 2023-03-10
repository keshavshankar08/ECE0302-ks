#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

TEST_CASE( "Test adding a non-allowable word", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE("test recursion", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);
}

TEST_CASE("test number", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.number() == 2);
}

TEST_CASE("test clear", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	b.clear();
	REQUIRE(b.number() == 0);
}


TEST_CASE("test add2", "[FindPalindrome]"){
	FindPalindrome b;
	std::vector<std::string> test;
	test.push_back("a");
	test.push_back("AA");
	test.push_back("AaA");
	REQUIRE(b.add(test));
	REQUIRE(b.number() == 6);
}

TEST_CASE("test cut1", "[FindPalindrome]"){
	FindPalindrome b;
	std::vector<std::string> test;
	test.push_back("a");
	test.push_back("AA");
	test.push_back("AaA");
	REQUIRE(b.cutTest1(test));
}

TEST_CASE("test cut2", "[FindPalindrome]"){
	FindPalindrome b;
	std::vector<std::string> test, test2;
	test.push_back("a");
	test.push_back("AA");
	test.push_back("AaA");
	test2.push_back("a");
	test2.push_back("AA");
	REQUIRE(b.cutTest2(test, test2));
}




