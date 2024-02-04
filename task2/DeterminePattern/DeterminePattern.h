#pragma once

#include <set>
#include <string>
#include <unordered_set>

namespace determinePattern
{
std::unordered_set<std::string> generatePermutations(const std::string& text);
std::set<std::string> generatePermutationsForWindow(const std::string& text, int windowLength);
std::pair<bool, std::unordered_set<std::string>> isRingUnique(const std::string& ring, int frame);
std::pair<bool, std::unordered_set<std::string>> isStrUnique(const std::string& str, int frame);
std::string determinePattern(const std::string& text, int windowSize);

void validateInputs(int windowSize);
bool isResultMaximumLength(size_t stringLength, const std::string& result);
std::string getNextStartingPermutation(const std::set<std::string>& nonModifiableAllPossiblePermutations, int repeat);
bool hasPossiblePermutationAvailable(const std::set<std::string>& allPossiblePermutation,
                                     const std::set<std::string>::iterator& availablePermutation);
std::string getStartingText(const std::string& text, int windowSize,
                                              uint expectedStringLength,
                                              const std::string& nextStartingPermutation);
int resetRepeatCounter(const size_t& expectedStringLength, int repeat);
} // namespace determinePattern
