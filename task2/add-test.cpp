#include "DeterminePattern.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <cmath>
#include <unordered_set>

namespace determinePattern
{

TEST_CASE("Generate permutations for window")
{
    SECTION("window size 2")
    {
        SECTION("ab")
        {
            const auto result = generatePermutationsForWindow("ab", 2);
            const std::set<std::string> ab2{"aa", "ab", "ba", "bb"};

            REQUIRE(result == ab2);
        }
        SECTION("abc")
        {
            const auto result = generatePermutationsForWindow("abc", 2);
            const std::set<std::string> abc2 = {"aa", "ab", "ba", "ac", "ca", "cb", "cc", "bc", "bb"};

            REQUIRE(result == abc2);
        }
    }
    SECTION("window size 3")
    {
        SECTION("ab3")
        {
            const auto result = generatePermutationsForWindow("ab", 3);
            const std::set<std::string> ab3 = {"aaa", "aba", "aab", "abb", "baa", "bba", "bab", "bbb"};

            REQUIRE(result == ab3);
        }
        SECTION("abc3")
        {
            const auto result = generatePermutationsForWindow("abc", 3);
            const std::set<std::string> abc3 = {"aaa", "baa", "caa", "aba", "bba", "cba", "aab", "bab", "cab",
                                                "abb", "bbb", "cbb", "abc", "bbc", "cbc", "aca", "bca", "cca",
                                                "aac", "bac", "cac", "acb", "bcb", "ccb", "acc", "bcc", "ccc"};
            REQUIRE(result == abc3);
        }
        SECTION("abcd 3")
        {
            const auto result = generatePermutationsForWindow("abcd", 3);
            std::set<std::string> abcPermutation{"aaa", "aab", "aac", "aad", "aba", "abb", "abc", "abd", "aca", "acb", "acc", "acd", "ada",
                                                 "adb", "adc", "add", "baa", "bab", "bac", "bad", "bba", "bbb", "bbc", "bbd", "bca", "bcb",
                                                 "bcc", "bcd", "bda", "bdb", "bdc", "bdd", "caa", "cab", "cac", "cad", "cba", "cbb", "cbc",
                                                 "cbd", "cca", "ccb", "ccc", "ccd", "cda", "cdb", "cdc", "cdd", "daa", "dab", "dac", "dad",
                                                 "dba", "dbb", "dbc", "dbd", "dca", "dcb", "dcc", "dcd", "dda", "ddb", "ddc", "ddd"};

            REQUIRE(result.size() == static_cast<size_t>(4 * 4 * 4));
            REQUIRE(abcPermutation == result);
        }
    }
    SECTION("window size 4")
    {
        SECTION("ab4")
        {
            const auto result = generatePermutationsForWindow("ab", 4);
            const std::set<std::string> ab4 = {"aaaa",
                                               "bbbb",
                                               "aaab",
                                               "aaba",
                                               "abaa",
                                               "baaa",
                                               "bbba",
                                               "bbab",
                                               "babb",
                                               "abbb",
                                               "aabb",
                                               "abba",
                                               "bbaa",
                                               "baab",
                                               "abab",
                                               "baba"};
            REQUIRE(result == ab4);
        }
        SECTION("abc4")
        {
            const std::set<std::string> abc4 = {"aaaa", "baaa", "caaa", "abaa", "bbaa", "cbaa", "aaba", "baba", "caba", "aaab", "baab",
                                                "caab", "acaa", "bcaa", "ccaa", "aaca", "baca", "caca", "aaac", "baac", "caac", "abba",
                                                "bbba", "cbba", "abab", "bbab", "cbab", "aabb", "babb", "cabb", "acca", "bcca", "ccca",
                                                "acac", "bcac", "ccac", "aacc", "bacc", "cacc", "abbc", "bbbc", "cbbc", "abcb", "bbcb",
                                                "cbcb", "acbb", "bcbb", "ccbb", "aabc", "babc", "cabc", "aacb", "bacb", "cacb", "abac",
                                                "bbac", "cbac", "abca", "bbca", "cbca", "acba", "bcba", "ccba", "acab", "bcab", "ccab",
                                                "abcc", "bbcc", "cbcc", "acbc", "bcbc", "ccbc", "accb", "bccb", "cccb", "accc", "bccc",
                                                "cccc", "abbb", "bbbb", "cbbb"};
            const auto result = generatePermutationsForWindow("abc", 4);
            // to make sure that verification data is correct
            REQUIRE(abc4.size() == 81);
            REQUIRE(result == abc4);
        }
    }
    SECTION("window size 5")
    {
        const auto result = generatePermutationsForWindow("abc", 5);

        REQUIRE(result.size() == static_cast<size_t>(3 * 3 * 3 * 3 * 3));
    }
}

TEST_CASE("Is string unique")
{
    SECTION("aabbab, 2; is not unique")
    {
        auto [b, permutations] = isStrUnique("aabbab", 2);
        REQUIRE(false == b);
    }
    SECTION("aaabba, 3; is unique")
    {
        auto [b, permutations] = isStrUnique("aaabba", 3);
        REQUIRE(true == b);
    }
    SECTION("long strings")
    {
        SECTION(
            "aaaacccbacaabcccaacaccbcabbbcbccacababbccbbcacbabaacbbbbaabbaccabc"
            "aaabacbcbba is unique")
        {
            auto [b, permutations] = isStrUnique(
                "aaaacccbacaabcccaacaccbcabbbcbccacababb"
                "ccbbcacbabaacbbbbaabbaccabcaaabacbcbba",
                4);
            REQUIRE(true == b);
        }
        SECTION(
            "aaaacccbacaabcccaacaccbcabbbcbccacababbccbbcacbabaacbbbbaabbaccabcaa"
            "abacbcbbacccc is not unique")
        {
            auto [b, permutations] = isStrUnique(
                "aaaacccbacaabcccaacaccbcabbbcbccacababbccbbcacbabaacbbbbaabb"
                "accabcaaabacbcbbacccc",
                4);
            REQUIRE(false == b);
        }
        SECTION("aaaabaacaabbaabcaacbabcbaccbbbccacccbccbcccc is not unique")
        {
            auto [b, permutations] = isStrUnique("aaaabaacaabbaabcaacbabcbaccbbbccacccbccbcccc", 4);
            REQUIRE(false == b);
        }
    }
}

// NOLINTNEXTLINE
TEST_CASE("Is ring unique")
{
    SECTION("window 2")
    {
        SECTION("aabbab not unique")
        {
            auto [b, permutations] = isRingUnique("aabbab", 2);
            REQUIRE(false == b);
        }

        SECTION("aabb unique")
        {
            auto [b, permutations] = isRingUnique("aabb", 2);
            REQUIRE(true == b);
        }

        SECTION("aabbca not unique")
        {
            auto [b, permutations] = isRingUnique("aabbca", 2);
            REQUIRE(false == b);
        }
        SECTION("aabbac unique")
        {
            auto [b, permutations] = isRingUnique("aabbac", 2);
            REQUIRE(true == b);
        }
        SECTION("aabcbbacc unique")
        {
            auto [b, permutations] = isRingUnique("aabcbbacc", 2);
            REQUIRE(true == b);
        }

        SECTION("aabbaccc not unique")
        {
            auto [b, permutations] = isRingUnique("aabbaccc", 2);
            REQUIRE(false == b);
        }
        SECTION("aa unique")
        {
            auto [b, permutations] = isRingUnique("aa", 2);
            REQUIRE(true == b);
        }
        SECTION("aba unique")
        {
            auto [b, permutations] = isRingUnique("aba", 2);
            REQUIRE(true == b);
        }
    }
    SECTION("window 3")
    {
        SECTION("aaa")
        {
            auto [b, permutations] = isRingUnique("aaa", 3);
            REQUIRE(true == b);
        }

        SECTION("aaabba not unique")
        {
            auto [b, permutations] = isRingUnique("aaabba", 3);
            REQUIRE(false == b);
        }
        SECTION("aabbbaba unique")
        {
            auto [b, permutations] = isRingUnique("aabbbaba", 3);
            REQUIRE(true == b);
        }
        SECTION("aaccbcabb unique")
        {
            auto [b, permutations] = isRingUnique("aaccbcabb", 3);
            REQUIRE(true == b);
        }
    }
    SECTION("window 4")
    {
        SECTION("aaaababbbbabaabb unique")
        {
            auto [b, permutations] = isRingUnique("aaaababbbbabaabb", 4);
            REQUIRE(true == b);
        }
        SECTION("aaaabbabaababbbb unique")
        {
            auto [b, permutations] = isRingUnique("aaaabbabaababbbb", 4);
            REQUIRE(true == b);
        }
        SECTION("abbbbababbaaaaba unique")
        {
            auto [b, permutations] = isRingUnique("abbbbababbaaaaba", 4);
            REQUIRE(true == b);
        }
        SECTION("aaaababbbbaabbab unique")
        {
            auto [b, permutations] = isRingUnique("aaaababbbbaabbab", 4);
            REQUIRE(true == b);
        }
        SECTION("aaaababaabbbbabb unique")
        {
            auto [b, permutations] = isRingUnique("aaaababaabbbbabb", 4);
            REQUIRE(true == b);
        }
        SECTION("aaaabbababbbbaab unique")
        {
            auto [b, permutations] = isRingUnique("aaaabbababbbbaab", 4);
            REQUIRE(true == b);
        }
        SECTION(
            "aaaabaaacaabbaabcaacbaaccababacabbbabbcabcbabccacacbbacbcaccbacccbbb"
            "bcbbccbcbcccc unique")
        {
            auto [b, permutations] = isRingUnique(
                "aaaabaaacaabbaabcaacbaaccababacabbbabbcabcbabccacacbbacbcac"
                "cbacccbbbbcbbccbcbcccc",
                4);
            REQUIRE(true == b);
        }
        SECTION(
            "aaaaccccbccbbcccabccaabbabbbacbcbcacaccbabaccacbbaacaacbacabbcababcb"
            "bbcbaabcaaab unique")
        {
            auto [b, permutations] = isRingUnique(
                "aaaaccccbccbbcccabccaabbabbbacbcbcacaccbabaccacbbaacaacbaca"
                "bbcababcbbbcbaabcaaab",
                4);
            REQUIRE(true == b);
        }
        SECTION("Unique Rings 81 characters abc 4")
        {
            const std::vector<std::string> dataABC4{
                "abcaacbccbaccabcbbbacbabaacaabccccbbcaccbcbaabbbbcbcabbaaabacacababbccaaaacccacbb",
                "aaaacbbcbabbbbccbbaabcacbcabcbbbababccccacaccabaacaabacabbcaaccbacccbcbccaaabbacb",
                "aaaacaacbabccabacbbaccccbccbbcbcaaababbcccacabbbbaaccaabcabcbacacbcbbbcaccbaabbab",
                "aaaacbbaccccaacacababccbacaabbcccbbbbcbabbabaabacbcbccaccabcbbcabbbaaccbcaaabcacb",
                "aaaabaaacaabbaabccbbcbcbacbcccacabcbbaccbababcacbaaccaacbbbbabbccabacaccccbcabbbc",
                "aaaabaccaccbaacbbbccabbacaaccccbcaaacacbababbcbcbbabcbacbccbbcacabcccaabbbbaabcab",
                "aaaabcccabbbcbacaabaaccbbcaacbccacaccccbabbaaacabacbbbbababcabcbcacbaabbccbcbbacc",
                "aaaaccbaabacbcbbcccaabccbcaacaaabbbcabcbabaacbbbbabcacaccacbacabbcbccababbaccccbb",
                "aaaacaabbaaabacbbbcbcbabccaccbcababaaccabbccbacabcbbcacacbccccbbabbbbacccaacbaabc",
                "aaaabacbbbcbcababbabcbbccacaaccaabbcaccccbacacbcccabccbbaccbcbaaacbabaacabbbbaabc",
                "aaaacbbaaccbcaabcaccacababaabbbabccccbbcbccabbcabcbbbbccbacaaabacbcbabbacccaacacb",
                "ccccbbcbcacbcbbacaaccbccaaabbbccbabacbbbbabbcabcbaaaacabbaababcaabcccabaacbaccaca",
                "ccccaaaabaaacaabbaabcaacbaaccababacabbbabbcabcbabccacacbbacbcaccbacccbbbbcbbccbcb",
                "bbbbaaaabaabbababbbcaaacaabcabacabbcbaacbabcbbacbbccaaccabccbaccbcacacbcbcccacccc",
                "aaaacccbaaabaabbaacaabcaacbababbbabcbacabacbbaccabbcabccacacbcaccbbbbcbbccbcbcccc",
            };

            for (const auto& str : dataABC4) {
                DYNAMIC_SECTION("VALUE IS " << str)
                {
                    auto [b, permutations] = isRingUnique(str, 4);
                    REQUIRE(true == b);
                }
            }
        }
    }
    SECTION("window 5")
    {
        auto [b, permutations] = isRingUnique("aaaaabbabbaaabaabababbbaabbbbabb", 5);
        REQUIRE(false == b);
    }
    SECTION("window 6")
    {
        auto [b, permutations] = isRingUnique(
            "ddddddaaaaaabaaaaacaaaaadaaaabbaaaabcaaaabdaaaacbaaaaccaaaacdaaaadbaaaadcaaaaddaaababaaabacaaabadaaabbbaaabbcaaabbdaaabcbaaabc"
            "caaabcdaaabdbaaabdcaaabddaaacabaaacacaaacadaaacbbaaacbcaaacbdaaaccbaaacccaaaccdaaacdbaaacdcaaacddaaadabaaadacaaadadaaadbbaaadb"
            "caaadbdaaadcbaaadccaaadcdaaaddbaaaddcaaadddaabaabaacaabaadaababbaababcaababdaabacbaabaccaabacdaabadbaabadcaabaddaabbabaabbacaa"
            "bbadaabbbbaabbbcaabbbdaabbcbaabbccaabbcdaabbdbaabbdcaabbddaabcabaabcacaabcadaabcbbaabcbcaabcbdaabccbaabcccaabccdaabcdbaabcdcaa"
            "bcddaabdabaabdacaabdadaabdbbaabdbcaabdbdaabdcbaabdccaabdcdaabddbaabddcaabdddaacaacaadaacabbaacabcaacabdaacacbaacaccaacacdaacad"
            "baacadcaacaddaacbabaacbacaacbadaacbbbaacbbcaacbbdaacbcbaacbccaacbcdaacbdbaacbdcaacbddaaccabaaccacaaccadaaccbbaaccbcaaccbdaaccc"
            "baaccccaacccdaaccdbaaccdcaaccddaacdabaacdacaacdadaacdbbaacdbcaacdbdaacdcbaacdccaacdcdaacddbaacddcaacdddaadaadabbaadabcaadabdaa"
            "dacbaadaccaadacdaadadbaadadcaadaddaadbabaadbacaadbadaadbbbaadbbcaadbbdaadbcbaadbccaadbcdaadbdbaadbdcaadbddaadcabaadcacaadcadaa"
            "dcbbaadcbcaadcbdaadccbaadcccaadccdaadcdbaadcdcaadcddaaddabaaddacaaddadaaddbbaaddbcaaddbdaaddcbaaddccaaddcdaadddbaadddcaaddddab"
            "ababacababadababbbababbcababbdababcbababccababcdababdbababdcababddabacacabacadabacbbabacbcabacbdabaccbabacccabaccdabacdbabacdc"
            "abacddabadacabadadabadbbabadbcabadbdabadcbabadccabadcdabaddbabaddcabadddabbabbabcabbabdabbacbabbaccabbacdabbadbabbadcabbaddabb"
            "bacabbbadabbbbbabbbbcabbbbdabbbcbabbbccabbbcdabbbdbabbbdcabbbddabbcacabbcadabbcbbabbcbcabbcbdabbccbabbcccabbccdabbcdbabbcdcabb"
            "cddabbdacabbdadabbdbbabbdbcabbdbdabbdcbabbdccabbdcdabbddbabbddcabbdddabcabcabdabcacbabcaccabcacdabcadbabcadcabcaddabcbacabcbad"
            "abcbbbabcbbcabcbbdabcbcbabcbccabcbcdabcbdbabcbdcabcbddabccacabccadabccbbabccbcabccbdabcccbabccccabcccdabccdbabccdcabccddabcdac"
            "abcdadabcdbbabcdbcabcdbdabcdcbabcdccabcdcdabcddbabcddcabcdddabdabdacbabdaccabdacdabdadbabdadcabdaddabdbacabdbadabdbbbabdbbcabd"
            "bbdabdbcbabdbccabdbcdabdbdbabdbdcabdbddabdcacabdcadabdcbbabdcbcabdcbdabdccbabdcccabdccdabdcdbabdcdcabdcddabddacabddadabddbbabd"
            "dbcabddbdabddcbabddccabddcdabdddbabdddcabddddacacacadacacbbacacbcacacbdacaccbacacccacaccdacacdbacacdcacacddacadadacadbbacadbca"
            "cadbdacadcbacadccacadcdacaddbacaddcacadddacbacbaccacbacdacbadbacbadcacbaddacbbadacbbbbacbbbcacbbbdacbbcbacbbccacbbcdacbbdbacbb"
            "dcacbbddacbcadacbcbbacbcbcacbcbdacbccbacbcccacbccdacbcdbacbcdcacbcddacbdadacbdbbacbdbcacbdbdacbdcbacbdccacbdcdacbddbacbddcacbd"
            "ddaccaccacdaccadbaccadcaccaddaccbadaccbbbaccbbcaccbbdaccbcbaccbccaccbcdaccbdbaccbdcaccbddacccadacccbbacccbcacccbdaccccbaccccca"
            "ccccdacccdbacccdcacccddaccdadaccdbbaccdbcaccdbdaccdcbaccdccaccdcdaccddbaccddcaccdddacdacdadbacdadcacdaddacdbadacdbbbacdbbcacdb"
            "bdacdbcbacdbccacdbcdacdbdbacdbdcacdbddacdcadacdcbbacdcbcacdcbdacdccbacdcccacdccdacdcdbacdcdcacdcddacddadacddbbacddbcacddbdacdd"
            "cbacddccacddcdacdddbacdddcacddddadadadbbadadbcadadbdadadcbadadccadadcdadaddbadaddcadadddadbadbadcadbaddadbbbbadbbbcadbbbdadbbc"
            "badbbccadbbcdadbbdbadbbdcadbbddadbcbbadbcbcadbcbdadbccbadbcccadbccdadbcdbadbcdcadbcddadbdbbadbdbcadbdbdadbdcbadbdccadbdcdadbdd"
            "badbddcadbdddadcadcaddadcbbbadcbbcadcbbdadcbcbadcbccadcbcdadcbdbadcbdcadcbddadccbbadccbcadccbdadcccbadccccadcccdadccdbadccdcad"
            "ccddadcdbbadcdbcadcdbdadcdcbadcdccadcdcdadcddbadcddcadcdddaddaddbbbaddbbcaddbbdaddbcbaddbccaddbcdaddbdbaddbdcaddbddaddcbbaddcb"
            "caddcbdaddccbaddcccaddccdaddcdbaddcdcaddcddadddbbadddbcadddbdadddcbadddccadddcdaddddbaddddcadddddbbbbbbcbbbbbdbbbbccbbbbcdbbbb"
            "dcbbbbddbbbcbcbbbcbdbbbcccbbbccdbbbcdcbbbcddbbbdbcbbbdbdbbbdccbbbdcdbbbddcbbbdddbbcbbcbbdbbcbccbbcbcdbbcbdcbbcbddbbccbcbbccbdb"
            "bccccbbcccdbbccdcbbccddbbcdbcbbcdbdbbcdccbbcdcdbbcddcbbcdddbbdbbdbccbbdbcdbbdbdcbbdbddbbdcbcbbdcbdbbdcccbbdccdbbdcdcbbdcddbbdd"
            "bcbbddbdbbddccbbddcdbbdddcbbddddbcbcbcbdbcbcccbcbccdbcbcdcbcbcddbcbdbdbcbdccbcbdcdbcbddcbcbdddbccbccbcdbccbdcbccbddbcccbdbcccc"
            "cbccccdbcccdcbcccddbccdbdbccdccbccdcdbccddcbccdddbcdbcdbdcbcdbddbcdcbdbcdcccbcdccdbcdcdcbcdcddbcddbdbcddccbcddcdbcdddcbcddddbd"
            "bdbdccbdbdcdbdbddcbdbdddbdcbdcbddbdccccbdcccdbdccdcbdccddbdcdccbdcdcdbdcddcbdcdddbddbddcccbddccdbddcdcbddcddbdddccbdddcdbddddc"
            "bdddddccccccdccccddcccdcdcccdddccdccdcddccddcdccddddcdcdcdddcddc",
            6);
        REQUIRE(true == b);

    }
}

TEST_CASE("Determine pattern ")
{
    SECTION("window 2")
    {
        SECTION("abc 2")
        {
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
            const auto expected11 = "bbaabcacc";
            std::vector<std::string> expectedVec{expected1,
                                                 expected2,
                                                 expected3,
                                                 expected4,
                                                 expected5,
                                                 expected6,
                                                 expected7,
                                                 expected8,
                                                 expected9,
                                                 expected10,
                                                 expected11};

            const auto result = determinePattern::determinePattern("abc", 2);
            REQUIRE_THAT(expectedVec, Catch::Matchers::Contains(result));
        }
    }
    SECTION("window 3")
    {
        SECTION("ab 3")
        {
            const auto expected1 = "aaababbb";
            const auto expected2 = "bbbabaaa";
            const auto expected3 = "aaabbbab";
            const auto expected4 = "aabbbaba";
            const auto expected5 = "bbabaaab";
            const auto expected6 = "bbbaaaba";
            std::vector<std::string> expectedVec{expected1, expected2, expected3, expected4, expected5, expected6};
            const auto result = determinePattern::determinePattern("ab", 3);
            REQUIRE_THAT(expectedVec, Catch::Matchers::Contains(result));
        }
        SECTION("abcd 3")
        {
            const std::string inputString{"abcd"};
            const auto windowLength = 3;
            const auto result = determinePattern::determinePattern(inputString, windowLength);
            WARN(result);
            const auto [b, perms] = isRingUnique(result, windowLength);
            REQUIRE(true == b);
            REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
        }
    }
    SECTION("window 4")
    {
        SECTION("ab 4")
        {
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
            const auto expected11 = "aaaababaabbabbbb";
            std::vector<std::string> expectedVec{expected1,
                                                 expected2,
                                                 expected3,
                                                 expected4,
                                                 expected5,
                                                 expected6,
                                                 expected7,
                                                 expected8,
                                                 expected9,
                                                 expected10,
                                                 expected11};
            const auto result = determinePattern::determinePattern("ab", 4);
            REQUIRE_THAT(expectedVec, Catch::Matchers::Contains(result));
        }

        SECTION("abc 4")
        {
            const std::vector<std::string> dataABC4{
                "abcaacbccbaccabcbbbacbabaacaabccccbbcaccbcbaabbbbcbcabbaaabacacababbccaaaacccacbb",
                "aaaacbbcbabbbbccbbaabcacbcabcbbbababccccacaccabaacaabacabbcaaccbacccbcbccaaabbacb",
                "aaaacaacbabccabacbbaccccbccbbcbcaaababbcccacabbbbaaccaabcabcbacacbcbbbcaccbaabbab",
                "aaaacbbaccccaacacababccbacaabbcccbbbbcbabbabaabacbcbccaccabcbbcabbbaaccbcaaabcacb",
                "aaaabaaacaabbaabccbbcbcbacbcccacabcbbaccbababcacbaaccaacbbbbabbccabacaccccbcabbbc",
                "aaaabaccaccbaacbbbccabbacaaccccbcaaacacbababbcbcbbabcbacbccbbcacabcccaabbbbaabcab",
                "aaaabcccabbbcbacaabaaccbbcaacbccacaccccbabbaaacabacbbbbababcabcbcacbaabbccbcbbacc",
                "aaaaccbaabacbcbbcccaabccbcaacaaabbbcabcbabaacbbbbabcacaccacbacabbcbccababbaccccbb",
                "aaaacaabbaaabacbbbcbcbabccaccbcababaaccabbccbacabcbbcacacbccccbbabbbbacccaacbaabc",
                "aaaabacbbbcbcababbabcbbccacaaccaabbcaccccbacacbcccabccbbaccbcbaaacbabaacabbbbaabc",
                "aaaacbbaaccbcaabcaccacababaabbbabccccbbcbccabbcabcbbbbccbacaaabacbcbabbacccaacacb",
                "ccccbbcbcacbcbbacaaccbccaaabbbccbabacbbbbabbcabcbaaaacabbaababcaabcccabaacbaccaca",
                "ccccaaaabaaacaabbaabcaacbaaccababacabbbabbcabcbabccacacbbacbcaccbacccbbbbcbbccbcb",
                "bbbbaaaabaabbababbbcaaacaabcabacabbcbaacbabcbbacbbccaaccabccbaccbcacacbcbcccacccc",
                "aaaacccbaaabaabbaacaabcaacbababbbabcbacabacbbaccabbcabccacacbcaccbbbbcbbccbcbcccc",
            };

            const auto result = determinePattern::determinePattern("abc", 4);
            REQUIRE_THAT(dataABC4, Catch::Matchers::Contains(result));
            REQUIRE(result.size() == 81);
            WARN(result);
        }
        SECTION(".xO 4")
        {
            const std::string inputString{".xO"};
            const auto windowLength = 4;
            const auto result = determinePattern::determinePattern(inputString, windowLength);
            const auto [b, perms] = isRingUnique(result, windowLength);
            REQUIRE(true == b);
            REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
            WARN(result);
        }
    }
}

TEST_CASE("Window size less than 2 throws")
{
    REQUIRE_THROWS_WITH(determinePattern::determinePattern("abc", 0), "window size must not be < 2");
}

TEST_CASE("ab 5")
{
    const std::string inputString{"ab"};
    const auto windowLength = 5;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("ab 6")
{
    const std::string inputString{"ab"};
    const auto windowLength = 6;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("ab 7")
{
    const std::string inputString{"ab"};
    const auto windowLength = 7;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("ab 8")
{
    const std::string inputString{"ab"};
    const auto windowLength = 8;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("ab 9")
{
    const std::string inputString{"ab"};
    const auto windowLength = 9;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("ab 10")
{
    const std::string inputString{"ab"};
    const auto windowLength = 10;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("ab 11")
{
    const std::string inputString{"ab"};
    const auto windowLength = 11;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("ab 3")
{
    const auto expected1 = "aaababbb";
    const auto expected2 = "bbbabaaa";
    const auto expected3 = "aaabbbab";
    const auto expected4 = "aabbbaba";
    const auto expected5 = "bbabaaab";
    const auto expected6 = "bbbaaaba";
    std::vector<std::string> expectedVec{expected1, expected2, expected3, expected4, expected5, expected6};
    const auto result = determinePattern::determinePattern("ab", 3);
    REQUIRE_THAT(expectedVec, Catch::Matchers::Contains(result));
}

TEST_CASE("abc 5")
{
    const std::string inputString{"abc"};
    const auto windowLength = 5;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("abcd 4")
{
    const std::string inputString{"abcd"};
    const auto windowLength = 4;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("abcd 3")
{
    const std::string inputString{"abcd"};
    const auto windowLength = 3;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("abcde 2")
{
    const std::string inputString{"abcde"};
    const auto windowLength = 2;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("abcde 3")
{
    const std::string inputString{"abcde"};
    const auto windowLength = 3;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

//long cases

TEST_CASE("abcdef 3")
{
    const std::string inputString{"abcdef"};
    const auto windowLength = 3;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("abcdef 4")
{
    const std::string inputString{"abcdef"};
    const auto windowLength = 4;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("abcd 5")
{
    const std::string inputString{"abcd"};
    const auto windowLength = 5;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("abcde 4")
{
    const std::string inputString{"abcde"};
    const auto windowLength = 4;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

TEST_CASE("abc 6")
{
    const std::string inputString{"abc"};
    const auto windowLength = 6;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}

// took a looong time,
TEST_CASE("long abcd 6")
{
    const std::string inputString{"abcd"};
    const auto windowLength = 6;
    const auto result = determinePattern::determinePattern(inputString, windowLength);
    const auto [b, perms] = isRingUnique(result, windowLength);
    REQUIRE(true == b);
    REQUIRE(result.size() == std::pow(inputString.size(), windowLength));
    WARN(result);
}
} // namespace determinePattern

//check for long sequences
