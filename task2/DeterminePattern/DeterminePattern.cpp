#include "DeterminePattern.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <vector>

std::set<std::string> determinePattern::generatePermutationsForWindow(const std::string& text, int windowLength)
{
    const auto expectedStringLength = static_cast<size_t>(std::pow(text.size(), windowLength));

    std::set<std::string> permutations;

    std::vector<std::string> subtexts(text.size());

    for (int i = 0; i < text.size(); ++i) {
        subtexts[i].push_back(text[i]);
    }

    while (subtexts.size() != expectedStringLength) {
        std::vector<std::string> extendedSubtexts;
        for (const auto& subtext : subtexts) {
            for (const auto& character : text) {
                auto newText = subtext + character;
                extendedSubtexts.push_back(newText);
            }
        }
        subtexts = extendedSubtexts;
    }
    permutations.insert(subtexts.begin(), subtexts.end());
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
    // simulate circular buffer
    auto ringExtendedWithFrame = ring + std::string(ring, 0, frame - 1);

    auto slides = ringExtendedWithFrame | std::views::slide(frame);

    //    for debug purposes
    //    auto print_subrange = [](std::ranges::viewable_range auto&& r) {
    //        std::cout << '[';
    //        for (int pos{}; auto elem : r)
    //            std::cout << (pos++ ? " " : "") << elem;
    //        std::cout << "] ";
    //    };
    //    std::ranges::for_each(slides, print_subrange);
    //    std::cout << '\n';

    bool allUnique = std::ranges::all_of(slides, [&](const auto& slide) {
        return permutations.insert(std::string(slide.begin(), slide.end())).second;
    });
    if (allUnique) {
        return {true, permutations};
    }
    return {false, {}};
}

std::pair<bool, std::unordered_set<std::string>> determinePattern::isStrUnique(const std::string& str, int frame)
{
    std::unordered_set<std::string> permutations;

    auto slides = str | std::views::slide(frame);
    bool allUnique = std::ranges::all_of(slides, [&](const auto& slide) {
        return permutations.insert(std::string(slide.begin(), slide.end())).second;
    });
    if (allUnique) {
        return {true, permutations};
    }
    return {false, {}};
}

std::string determinePattern::determinePattern(const std::string& text, int windowSize)
{
    validateInputs(windowSize);
    const auto expectedStringLength = static_cast<size_t>(std::pow(text.size(), windowSize));
    const auto nonModifiableAllPossiblePermutations = generatePermutationsForWindow(text, windowSize);
    auto allPossiblePermutation = nonModifiableAllPossiblePermutations;

    std::string result;
    int repeat = 0;
    while (isResultMaximumLength(expectedStringLength, result)) {
        const auto nextStartingPermutation = getNextStartingPermutation(nonModifiableAllPossiblePermutations, repeat);
        result = getStartingText(text, windowSize, expectedStringLength, nextStartingPermutation);

        allPossiblePermutation = nonModifiableAllPossiblePermutations;
        auto availablePermutation = allPossiblePermutation.begin();
        while (hasPossiblePermutationAvailable(allPossiblePermutation, availablePermutation)) {
            const auto missingCharacters = expectedStringLength - result.length();
            if (missingCharacters > expectedStringLength) {
                throw std::logic_error("buffer overfow");
            }
            if (missingCharacters > windowSize) {
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
        repeat = resetRepeatCounter(expectedStringLength, repeat);
        repeat++;
    }
    return {};
}

int determinePattern::resetRepeatCounter(const size_t& expectedStringLength, int repeat)
{
    if (repeat == expectedStringLength - 1) {
        repeat = 0;
    }
    return repeat;
}

std::string determinePattern::getStartingText(const std::string& text,
                                              int windowSize,
                                              uint expectedStringLength,
                                              const std::string& nextStartingPermutation)
{
    const std::string start(windowSize, text[0]);
    const std::string last(windowSize, text[text.size() - 1]);

    if (expectedStringLength > windowSize * 3) {
        std::string result = last + start + nextStartingPermutation;
        return result;
    }
    std::string result = start + nextStartingPermutation;
    return result;
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
