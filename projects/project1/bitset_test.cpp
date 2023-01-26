#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitset.hpp"

TEST_CASE( "Test bitset default construction", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "Test bitset construction with asString", "[bitset]" ) {
    Bitset b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE( "Test bitset construction size", "[bitset]" ) {
    Bitset b(64);
    std::string s(64, '0');
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
}

TEST_CASE( "Test bitset construction string", "[bitset]" ) {
    std::string s("00101110000011000001101000001");
    Bitset b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test bitset construction invalid string", "[bitset]" ) {
    std::string s("00101110000011002001101000001");
    Bitset b(s);
    REQUIRE_FALSE(b.good());
}

TEST_CASE( "Test set", "[bitset]" ) {
    std::string s("00010001");
    Bitset b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test set with default init", "[bitset]" ) {
    std::string s("00010001");
    Bitset b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test set with size init", "[bitset]" ) {
    std::string s("00010");
    Bitset b(5);
    b.set(3);
    REQUIRE(b.size() == 5);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test combined", "[bitset]" ) {
    std::string s((1<<15) + 3, '0');
    Bitset b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    for (int i = 1; i < (1<<10); i++) {
        b.set(i);
        b.reset(i + (1<<10));
        b.toggle(i + (1<<11));
        REQUIRE(b.good());
        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1<<10)));
        REQUIRE(((b.test(i + (1<<11)) == true && s.at(i + (1<<11)) == '0') || (b.test(i + (1<<11)) == false && s.at(i + (1<<11)) == '1')));
    }
}


//-----------my tests-----------
//@test : tests default constructor, size, and good
TEST_CASE( "Default Constructor success", "[bitset]" ) {
    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good() == true);
}

//@test : tests overload constructor, size, and good
TEST_CASE( "Overload Constructor fail", "[bitset]" ) {
    Bitset b(0);  
    REQUIRE(b.size() == 0);
    REQUIRE(b.good() == false);
}

//@test : tests string constructor, size, and good
TEST_CASE( "String Constructor fail", "[bitset]" ) {
    Bitset b("01010122");  
    REQUIRE(b.size() == 0);
    REQUIRE(b.good() == false);
}

//@test : tests destructor
/*
TEST_CASE( "Destructor fail", "[bitset]" ) {
    Bitset b;
    Bitset *copy = &b;
    b.~Bitset();
    REQUIRE(&b = *copy);
}
*/

//@test : tests set method
TEST_CASE( "Set method fail", "[bitset]" ) {
    Bitset b(6);
    b.set(9);
    REQUIRE(b.good() == false);
}

//@test : tests reset method
TEST_CASE( "Reset method fail", "[bitset]" ) {
    Bitset b(6);
    b.reset(6);
    REQUIRE(b.good() == false);
}

//@test : tests toggle method
TEST_CASE( "Toggle method fail", "[bitset]" ) {
    Bitset b(6);
    b.toggle(6);
    REQUIRE(b.good() == false);
}

//@test : tests test method
TEST_CASE( "Test method fail", "[bitset]" ) {
    Bitset b(6);
    REQUIRE(b.test(6) == false);
    REQUIRE(b.good() == false);
}

//@test : tests string print method
TEST_CASE( "String method success", "[bitset]" ) {
    Bitset b(6);
    b.toggle(0);
    b.toggle(2);
    b.toggle(4);
    REQUIRE(b.asString() == "101010");
}