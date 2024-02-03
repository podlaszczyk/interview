#include "DeterminePattern.h"

#include <cmath>
#include <stdexcept>
#include <vector>

std::unordered_set<std::string> determinePattern::generatePermutations(const std::string& text)
{
    std::unordered_set<std::string> permutations;
    auto next = text;
    auto previous = text;

    permutations.insert(next);
    do {
        permutations.insert(next);
    } while (std::next_permutation(next.begin(), next.end()));

    do {
        permutations.insert(previous);
    } while (std::prev_permutation(previous.begin(), previous.end()));

    return permutations;
}

std::set<std::string> determinePattern::generatePermutationsForWindow(const std::string& text, int windowLength)
{
    std::set<std::string> permutations;

    std::vector<std::string> basics;

    for (const auto& character : text) {
        const auto permutation = std::string(windowLength, character);
        permutations.insert(permutation);
        basics.push_back(permutation);
    }
    if (windowLength == text.size()) {
        permutations.insert(text);
        basics.push_back(text);
    }
    if (windowLength > text.size()) {
        for (int k = 0; k < text.size(); ++k) {
            std::string str(windowLength, text[k]);
            int index = 0;
            for (const auto& character : text) {
                str[index] = character;
                index++;
            }
            permutations.insert(str);
            basics.push_back(str);
        }
    }

    // swap to make sure
    // that all possible texts for permutation is used
    for (int swapIndex = 0; swapIndex < windowLength; ++swapIndex) {
        for (int i = 0; i < basics.size() - 1; ++i) {
            std::swap(basics[i][swapIndex], basics[i + 1][swapIndex]);
        }
        for (const auto& basic : basics) {
            auto newPermutations = generatePermutations(basic);
            permutations.insert(newPermutations.begin(), newPermutations.end());
        }
    }
    return permutations;
}

std::pair<bool, std::unordered_set<std::string>> determinePattern::isRingUnique(const std::string& ring, int frame)
{
    std::unordered_set<std::string> permutations;

    if (ring.size() == frame) {
        permutations.insert(ring);
        return {true, permutations};
    }
    // add at the end of string frame-1 characters from start
    // simulate cyclural buffer
    auto ringExtendedWithFrame = ring + std::string(ring, 0, frame - 1);

    for (size_t i = 0; i < ring.size(); ++i) {
        const auto permutation = std::string(ringExtendedWithFrame, i, frame);

        if (auto [p, success] = permutations.insert(permutation); !success) {
            return {false, {}};
        }
    }

    return {true, permutations};
}

std::pair<bool, std::unordered_set<std::string>> determinePattern::isStrUnique(const std::string& str, int frame)
{
    std::unordered_set<std::string> permutations;

    for (size_t i = 0; i < str.size() - frame + 1; ++i) {
        const auto permutation = std::string(str, i, frame);

        if (auto [p, success] = permutations.insert(permutation); !success) {
            return {false, {}};
        }
    }

    return {true, permutations};
}

std::string determinePattern::determinePattern(const std::string& text, int windowSize)
{
    validateInputs(windowSize);
    const auto expectedStringLength = static_cast<size_t>(std::pow(text.size(), windowSize));
    const auto nonModifiableAllPossiblePermutations = generatePermutationsForWindow(text, windowSize);
    auto allPossiblePermutation = nonModifiableAllPossiblePermutations;

    const std::string start(windowSize, text[0]);

    std::string result;
    int repeat = 0;
    while (isResultMaximumLength(expectedStringLength, result)) {
        const auto nextStartingPermutation = getNextStartingPermutation(nonModifiableAllPossiblePermutations, repeat);
        result = start + nextStartingPermutation;

        allPossiblePermutation = nonModifiableAllPossiblePermutations;
        auto availablePermutation = allPossiblePermutation.begin();
        while (hasPossiblePermutationAvailable(allPossiblePermutation, availablePermutation)) {
            const auto missingCharacters = expectedStringLength - result.length();
            if (missingCharacters >= windowSize) {
                auto candidate = *availablePermutation;

                auto tempStr = result + candidate;
                auto [boolean, perms] = isStrUnique(tempStr, windowSize);
                if (boolean) {
                    result = tempStr;
                    allPossiblePermutation.erase(candidate);
                    availablePermutation = allPossiblePermutation.begin();
                }
                else {
                    availablePermutation++;
                }
            }
            else {
                // add last missing characters part of existing possible permutations
                for (const auto& perm : allPossiblePermutation) {
                    const auto tempStr = result + std::string(perm, 0, missingCharacters);
                    auto [boolean, perms] = isRingUnique(tempStr, windowSize);
                    if (boolean) {
                        result = tempStr;
                        return result;
                    }
                }
                break;
            }
        }
        if (result.size() == expectedStringLength) {
            return result;
        }
        if (repeat == expectedStringLength) {
            repeat = 0;
        }
        repeat++;
    }
    return {};
}

bool determinePattern::hasPossiblePermutationAvailable(const std::set<std::string>& allPossiblePermutation,
                                                       const std::set<std::string>::iterator& availablePermutation)
{
    return !allPossiblePermutation.empty() && availablePermutation != allPossiblePermutation.end();
}

std::string determinePattern::getNextStartingPermutation(const std::set<std::string>& nonModifiableAllPossiblePermutations, int repeat)
{
    auto permIterator = nonModifiableAllPossiblePermutations.begin();
    for (int count = 0; count < repeat; ++count) {
        permIterator++;
    }
    auto permutation = *permIterator;
    return permutation;
}

bool determinePattern::isResultMaximumLength(size_t stringLength, const std::string& result)
{
    return result.size() != stringLength;
}

void determinePattern::validateInputs(int windowSize)
{
    if (windowSize < 2) {
        throw std::invalid_argument("window size must not be < 2");
    }
}
