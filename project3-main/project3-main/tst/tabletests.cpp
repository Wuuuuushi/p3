#include <Wordset.hpp>
#include <catch2/catch_amalgamated.hpp>
#include <convert.hpp>
#include <string>

namespace {
namespace proj3 = shindler::ics46::project3;

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.

TEST_CASE("Hash:dbc:Expect5553", "[Required][Hash]") {
    const static unsigned int BASE = 37;
    const static unsigned int MOD = 100000;
    auto hashValue = proj3::polynomialHashFunction("dbc", BASE, MOD);
    size_t shouldBe = 4 * BASE * BASE + 2 * BASE + 3;
    REQUIRE(hashValue == shouldBe);
}

TEST_CASE("Table:SingleInsert:ExpectInTableAndUnchangedCapacity",
          "[Required][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("dbc");
    REQUIRE(wordSet.contains("dbc"));
    REQUIRE(wordSet.capacity() == 11);
}

TEST_CASE("Table:MultiInsert:ExpectInTableAndUnchangedCapacity",
          "[Required][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    REQUIRE(wordSet.capacity() == 11);
}

// this test case is not required, in the sense
// that it is not a prerequisite to grading part 1.
// However, I am providing it in hopes that it helps
// you to test your code.
// The functionality is still needed for full credit!
TEST_CASE("Table:MultiInsertWithResize:ExpectInTableAndResizedTable",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    wordSet.insert("salsa");
    wordSet.insert("sloth");
    wordSet.insert("colossus");
    wordSet.insert("synergize");
    wordSet.insert("monday");
    wordSet.insert("tuesday");
    wordSet.insert("wednesday");
    wordSet.insert("thursday");
    wordSet.insert("friday");
    wordSet.insert("saturday");
    wordSet.insert("sunday");
    REQUIRE(wordSet.contains("monday"));
    REQUIRE(wordSet.contains("sunday"));
    REQUIRE(wordSet.capacity() == 23);
}

TEST_CASE("Table:MultiInsertWithResize:ExpectInTableAndResizedTableandERASE",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    wordSet.insert("salsa");
    wordSet.insert("sloth");
    wordSet.insert("colossus");
    wordSet.insert("synergize");
    wordSet.insert("monday");
    wordSet.insert("tuesday");
    wordSet.insert("wednesday");
    wordSet.insert("thursday");
    wordSet.insert("friday");
    wordSet.insert("saturday");
    wordSet.insert("sunday");
    wordSet.erase("monday");
    REQUIRE(!wordSet.contains("monday"));
    REQUIRE(wordSet.contains("sunday"));
    REQUIRE(wordSet.capacity() == 23);
}

}  // namespace
