#include "Pattern.h"
#include "catch2/catch_template_test_macros.hpp"
#include "catch2/generators/catch_generators_all.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <unordered_set>

std::set<std::string> ab2 = {"aa", "ab", "ba", "bb"};
std::set<std::string> ab3 = {"aaa", "aba", "aab", "abb",
                             "baa", "bba", "bab", "bbb"};
std::set<std::string> abc2 = {"aa", "ab", "ba", "ac", "ca",
                              "cb", "cc", "bc", "bb"};
std::set<std::string> ab4 = {"aaaa", "bbbb", "aaab", "aaba", "abaa", "baaa",
                             "bbba", "bbab", "babb", "abbb", "aabb", "abba",
                             "bbaa", "baab", "abab", "baba"};

std::set<std::string> abc3 = {"aaa", "baa", "caa", "aba", "bba", "cba", "aab",
                              "bab", "cab", "abb", "bbb", "cbb", "abc", "bbc",
                              "cbc", "aca", "bca", "cca", "aac", "bac", "cac",
                              "acb", "bcb", "ccb", "acc", "bcc", "ccc"};

std::set<std::string> abc4 = {
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
TEST_CASE("Is ring unique aabcbbacc window size 2") {
  auto [b, permutations] = isRingUnique("aabcbbacc", 2);
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
TEST_CASE("Is ring unique aaaababbbbaabbab window size 4") {
  auto [b, permutations] = isRingUnique("aaaababbbbaabbab", 4);
  REQUIRE(true == b);
}
TEST_CASE("Is ring unique aaaababaabbbbabb window size 4") {
  auto [b, permutations] = isRingUnique("aaaababaabbbbabb", 4);
  REQUIRE(true == b);
}
TEST_CASE("Is ring unique aaaabbababbbbaab window size 4") {
  auto [b, permutations] = isRingUnique("aaaabbababbbbaab", 4);
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
TEST_CASE("Is ring unique aaccbcabb window size 3") {
  auto [b, permutations] = isRingUnique("aaccbcabb", 3);
  REQUIRE(true == b);
}

TEST_CASE("Is ring unique "
          "aaaabaaacaabbaabcaacbaaccababacabbbabbcabcbabccacacbbacbcaccbacccbbb"
          "bcbbccbcbcccc window size 4") {
  auto [b, permutations] =
      isRingUnique("aaaabaaacaabbaabcaacbaaccababacabbbabbcabcbabccacacbbacbcac"
                   "cbacccbbbbcbbccbcbcccc",
                   4);
  REQUIRE(true == b);
}
TEST_CASE("Is ring unique "
          "aaaaccccbccbbcccabccaabbabbbacbcbcacaccbabaccacbbaacaacbacabbcababcb"
          "bbcbaabcaaab"
          " window size 4") {
  auto [b, permutations] =
      isRingUnique("aaaaccccbccbbcccabccaabbabbbacbcbcacaccbabaccacbbaacaacbaca"
                   "bbcababcbbbcbaabcaaab",
                   4);
  REQUIRE(true == b);
}

const std::vector<std::string> dataABC4{
    "abcaacbccbaccabcbbbacbabaacaabccccbbcaccbc"
    "baabbbbcbcabbaaabacacababbccaaaacccacbb",
    "aaaacbbcbabbbbccbbaabcacbcabcbbbababccccac"
    "accabaacaabacabbcaaccbacccbcbccaaabbacb",
    "aaaacaacbabccabacbbaccccbccbbcbcaaababbccc"
    "acabbbbaaccaabcabcbacacbcbbbcaccbaabbab",
    "aaaacbbaccccaacacababccbacaabbcccbbbbcbabb"
    "abaabacbcbccaccabcbbcabbbaaccbcaaabcacb",
    "aaaabaaacaabbaabccbbcbcbacbcccacabcbbaccba"
    "babcacbaaccaacbbbbabbccabacaccccbcabbbc",
    "aaaabaccaccbaacbbbccabbacaaccccbcaaacacbab"
    "abbcbcbbabcbacbccbbcacabcccaabbbbaabcab",
    "aaaabcccabbbcbacaabaaccbbcaacbccacaccccbab"
    "baaacabacbbbbababcabcbcacbaabbccbcbbacc",
    "aaaaccbaabacbcbbcccaabccbcaacaaabbbcabcbab"
    "aacbbbbabcacaccacbacabbcbccababbaccccbb",
    "aaaacaabbaaabacbbbcbcbabccaccbcababaaccabbccbacabcbbcacacbccccbbabbbbacc"
    "caacbaabc",
    "aaaabacbbbcbcababbabcbbccacaaccaabbcaccccbacacbcccabccbbaccbcbaaacbabaac"
    "abbbbaabc",
    "aaaacbbaaccbcaabcaccacababaabbbabccccbbcbccabbcabcbbbbccbacaaabacbcbabba"
    "cccaacacb",
    "ccccbbcbcacbcbbacaaccbccaaabbbccbabacbbbbabbcabcbaaaacabbaababcaabcccaba"
    "acbaccaca",
    "ccccaaaabaaacaabbaabcaacbaaccababacabbbabbcabcbabccacacbbacbcaccbacccbbb"
    "bcbbccbcb"};

TEST_CASE("Unique Rings 81 characters abc 4") {

  for (const auto &str : dataABC4) {
    DYNAMIC_SECTION("VALUE IS " << str) {
      auto [b, permutations] = isRingUnique(str, 4);
      REQUIRE(true == b);
    }
  }
}

TEST_CASE("determine_pattern  abc 2") {
  const auto expected1 = "aabacbbcc";
  const auto expected2 = "ccaacbabb";
  const auto expected3 = "aaccbcabb";
  const auto expected4 = "aabcbbacc";
  const auto expected5 = "aacbccabb";
  const auto expected6 = "aabbacbcc";
  const auto expected7 = "aaccabcbb";
  const auto expected8 = "bbacaabcc";
  const auto expected9 = "bbcaccbaa";
  const auto expected10 = "ccaabacbb";
  std::vector<std::string> some_vec{expected1, expected2, expected3, expected4,
                                    expected5, expected6, expected7, expected8,
                                    expected9, expected10};

  const auto result = determine_pattern("abc", 2);
  REQUIRE_THAT(some_vec, Catch::Matchers::Contains(result));
}

TEST_CASE("determine_pattern  ab 3") {
  const auto expected1 = "aaababbb";
  const auto expected2 = "bbbabaaa";
  const auto expected3 = "aaabbbab";
  const auto expected4 = "aabbbaba";
  const auto expected5 = "bbabaaab";
  const auto expected6 = "bbbaaaba";
  std::vector<std::string> some_vec{expected1, expected2, expected3,
                                    expected4, expected5, expected6};
  const auto result = determine_pattern("ab", 3);
  REQUIRE_THAT(some_vec, Catch::Matchers::Contains(result));
}

TEST_CASE("determine_pattern  ab 4") {
  const auto expected1 = "aaaababbbbabaabb";
  const auto expected2 = "aaaabbabaababbbb";
  const auto expected3 = "abbbbababbaaaaba";
  const auto expected4 = "aaaababbbbaabbab";
  const auto expected5 = "aaaababaabbbbabb";
  const auto expected6 = "aaaabbababbbbaab";
  const auto expected7 = "bbbbaababaaaabba";
  const auto expected8 = "bbbbababbaaaabaa";
  const auto expected9 = "bbbbabaaaababbaa";
  const auto expected10 = "bbbbaaaabaabbaba";
  std::vector<std::string> some_vec{expected1, expected2, expected3, expected4,
                                    expected5, expected6, expected7, expected8,
                                    expected9, expected10};
  const auto result = determine_pattern("ab", 4);
  REQUIRE_THAT(some_vec, Catch::Matchers::Contains(result));
}

TEST_CASE("determine_pattern abc 4") {
  const auto result = determine_pattern("abc", 4);
  std::cout << "res.size " << result.size();
  REQUIRE_THAT(dataABC4, Catch::Matchers::Contains(result));
  REQUIRE(result.size() == 81);
}
