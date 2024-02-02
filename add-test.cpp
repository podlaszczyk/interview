#include <catch2/catch_test_macros.hpp>

#include "Pattern.h"
#include <unordered_set>

std::unordered_set<std::string> ab2 = {"aa", "ab", "ba", "bb"};
std::unordered_set<std::string> ab3 = {"aaa", "aba", "aab", "abb",
                                       "baa", "bba", "bab", "bbb"};
std::unordered_set<std::string> abc2 = {"aa", "ab", "ba", "ac", "ca",
                                        "cb", "cc", "bc", "bb"};
std::unordered_set<std::string> ab4 = {
    "aaaa", "bbbb", "aaab", "aaba", "abaa", "baaa", "bbba", "bbab",
    "babb", "abbb", "aabb", "abba", "bbaa", "baab", "abab", "baba"};

std::unordered_set<std::string> abc3 = {
    "aaa", "baa", "caa", "aba", "bba", "cba", "aab", "bab", "cab",
    "abb", "bbb", "cbb", "abc", "bbc", "cbc", "aca", "bca", "cca",
    "aac", "bac", "cac", "acb", "bcb", "ccb", "acc", "bcc", "ccc"};

std::unordered_set<std::string> abc4 = {
    "aaaa", "baaa", "caaa", "abaa", "bbaa", "cbaa", "aaba", "baba", "caba",
    "aaab", "baab", "caab", "acaa", "bcaa", "ccaa", "aaca", "baca", "caca",
    "aaac", "baac", "caac", "abba", "bbba", "cbba", "abab", "bbab", "cbab",
    "aabb", "babb", "cabb", "acca", "bcca", "ccca", "acac", "bcac", "ccac",
    "aacc", "bacc", "cacc", "abbc", "bbbc", "cbbc", "abcb", "bbcb", "cbcb",
    "acbb", "bcbb", "ccbb", "aabc", "babc", "cabc", "aacb", "bacb", "cacb",
    "abac", "bbac", "cbac", "abca", "bbca", "cbca", "acba", "bcba", "ccba",
    "acab", "bcab", "ccab", "abcc", "bbcc", "cbcc", "acbc", "bcbc", "ccbc",
    "accb", "bccb", "cccb", "accc", "bccc", "cccc", "abbb", "bbbb", "cbbb"};

TEST_CASE("Generate permutations for baa ") {
  std::unordered_set<std::string> baaPermutation = {"aba", "baa", "aab"};
  const auto result = generatePermutations("baa");
  REQUIRE(baaPermutation == result);
}

TEST_CASE("Generate permutations for abc ") {
  std::unordered_set<std::string> abcPermutation = {"abc", "acb", "bac",
                                                    "bca", "cab", "cba"};
  const auto result = generatePermutations("abc");
  REQUIRE(abcPermutation == result);
}

TEST_CASE("Generate permutations window for ab 2") {
  const auto result = generatePermutationsForWindow("ab", 2);
  REQUIRE(result == ab2);
}

TEST_CASE("Generate permutations window for abc 2") {
  const auto result = generatePermutationsForWindow("abc", 2);
  REQUIRE(result == abc2);
}

TEST_CASE("Generate permutations window for ab 3") {
  const auto result = generatePermutationsForWindow("ab", 3);
  REQUIRE(result == ab3);
}

TEST_CASE("Generate permutations window for ab 4") {
  const auto result = generatePermutationsForWindow("ab", 4);
  REQUIRE(result == ab4);
}

TEST_CASE("Generate permutations window for abc 3") {
  const auto result = generatePermutationsForWindow("abc", 3);
  REQUIRE(result == abc3);
}

TEST_CASE("Generate permutations window for abc 4") {
  const auto result = generatePermutationsForWindow("abc", 4);
  REQUIRE(abc4.size() == 81); // to make sure that verification data is correct
  REQUIRE(result == abc4);
}

TEST_CASE("Is str unique aabbab window size 2") {
  auto [b, permutations] = isStrUnique("aabbab", 2);
  REQUIRE(false == b);
}

TEST_CASE("Is str unique aaabba window size 3") {
  auto [b, permutations] = isStrUnique("aaabba", 3);
  REQUIRE(true == b);
}
TEST_CASE("Is str unique "
          "aaaacccbacaabcccaacaccbcabbbcbccacababbccbbcacbabaacbbbbaabbaccabcaa"
          "abacbcbba window size 4") {
  auto [b, permutations] = isStrUnique("aaaacccbacaabcccaacaccbcabbbcbccacababb"
                                       "ccbbcacbabaacbbbbaabbaccabcaaabacbcbba",
                                       4);
  REQUIRE(true == b);
}
TEST_CASE("Is str unique "
          "aaaacccbacaabcccaacaccbcabbbcbccacababbccbbcacbabaacbbbbaabbaccabcaa"
          "abacbcbbacccc window size 4") {
  auto [b, permutations] =
      isStrUnique("aaaacccbacaabcccaacaccbcabbbcbccacababbccbbcacbabaacbbbbaabb"
                  "accabcaaabacbcbbacccc",
                  4);
  REQUIRE(false == b);
}
TEST_CASE("Is str unique aaaabaacaabbaabcaacbabcbaccbbbccacccbccbcccc window "
          "size 4") {
  auto [b, permutations] =
      isStrUnique("aaaabaacaabbaabcaacbabcbaccbbbccacccbccbcccc", 4);
  REQUIRE(false == b);
}

TEST_CASE("Is ring unique aabbab window size 2") {
  auto [b, permutations] = isRingUnique("aabbab", 2);
  REQUIRE(false == b);
}

TEST_CASE("Is ring unique aabb window size 2") {
  auto [b, permutations] = isRingUnique("aabb", 2);
  REQUIRE(true == b);
}

TEST_CASE("Is ring unique aabbca window size 2") {
  auto [b, permutations] = isRingUnique("aabbca", 2);
  REQUIRE(false == b);
}
TEST_CASE("Is ring unique aabbac window size 2") {
  auto [b, permutations] = isRingUnique("aabbac", 2);
  REQUIRE(true == b);
}

TEST_CASE("Is ring unique aabbaccc window size 2") {
  auto [b, permutations] = isRingUnique("aabbaccc", 2);
  REQUIRE(false == b);
}
TEST_CASE("Is ring unique aaaababbbbabaabb window size 4") {
  auto [b, permutations] = isRingUnique("aaaababbbbabaabb", 4);
  REQUIRE(true == b);
}
TEST_CASE("Is ring unique aaaabbabaababbbb window size 4") {
  auto [b, permutations] = isRingUnique("aaaabbabaababbbb", 4);
  REQUIRE(true == b);
}
TEST_CASE("Is ring unique abbbbababbaaaaba window size 4") {
  auto [b, permutations] = isRingUnique("abbbbababbaaaaba", 4);
  REQUIRE(true == b);
}
TEST_CASE("Is ring unique aa window size 2") {
  auto [b, permutations] = isRingUnique("aa", 2);
  REQUIRE(true == b);
}
TEST_CASE("Is ring unique aba window size 2") {
  auto [b, permutations] = isRingUnique("aba", 2);
  REQUIRE(true == b);
}

TEST_CASE("Is ring unique aaa window size 3") {
  auto [b, permutations] = isRingUnique("aaa", 3);
  REQUIRE(true == b);
}

TEST_CASE("Is ring unique aaabba window size 3") {
  auto [b, permutations] = isRingUnique("aaabba", 3);
  REQUIRE(false == b);
}
TEST_CASE("Is ring unique aabbbaba window size 3") {
  auto [b, permutations] = isRingUnique("aabbbaba", 3);
  REQUIRE(true == b);
}

TEST_CASE("determine_pattern  ab 3") {
  const auto expected1 = "aaababbb";
  const auto expected2 = "bbbabaaa";
  const auto expected3 = "aaabbbab";
  const auto expected4 = "aabbbaba";

  const auto result = determine_pattern("ab", 3);
  auto match = (expected1 == result || expected2 == result ||
                expected3 == result || expected4 == result);

  REQUIRE(true == match);
}

TEST_CASE("determine_pattern  ab 4") {
  const auto expected1 = "aaaababbbbabaabb";
  const auto expected2 = "aaaabbabaababbbb";
  const auto expected3 = "abbbbababbaaaaba";

  const auto result = determine_pattern("ab", 4);
  auto match =
      (expected1 == result || expected2 == result || expected3 == result);

  REQUIRE(true == match);
}

TEST_CASE("determine_pattern abc 4") {
  const auto result = determine_pattern("abc", 4);
  std::cout << "res.size " << result.size();
  REQUIRE("" == result);
}