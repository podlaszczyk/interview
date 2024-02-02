#pragma once

#include <algorithm>
#include <complex>
#include <iostream>
#include <string>
#include <unordered_set>

std::unordered_set<std::string> generatePermutations(const std::string &text) {
  std::unordered_set<std::string> permutations;
  auto next = text;
  auto previous = text;

  permutations.insert(next);
  do
    permutations.insert(next);
  while (std::next_permutation(next.begin(), next.end()));

  do
    permutations.insert(previous);
  while (std::prev_permutation(previous.begin(), previous.end()));

  return permutations;
}

std::unordered_set<std::string>
generatePermutationsForWindow(const std::string &text, int windowLength) {
  std::unordered_set<std::string> permutations;

  std::string start;
  std::string t;
  std::string s;
  std::vector<std::string> basics;

  for (auto c : text) {
    s = std::string(windowLength, c);
    permutations.insert(s);
    basics.push_back(s);
  }
  if (windowLength == text.size()) {
    permutations.insert(text);
    basics.push_back(text);
  }
  if (windowLength > text.size()) {
    for (int k = 0; k < text.size(); ++k) {
      std::string s(windowLength, text[k]);
      int index = 0;
      for (auto c : text) {
        s[index] = c;
        index++;
      }
      permutations.insert(s);
      basics.push_back(s);
    }
  }

  // swap to make sure
  // that all possible texts for permutaion is used
  for (int swapIndex = 0; swapIndex < windowLength; ++swapIndex) {
    for (int i = 0; i < basics.size() - 1; ++i) {
      std::swap(basics[i][swapIndex], basics[i + 1][swapIndex]);
    }
    for (const auto &b : basics) {
      //      std::cout << b << "\n";
      auto newPermutations = generatePermutations(b);
      permutations.insert(newPermutations.begin(), newPermutations.end());
    }
    //    std::cout<< "\n";
  }
//  std::cout << "size " << permutations.size();
  return permutations;
}

std::pair<bool, std::unordered_set<std::string>>
isRingUnique(const std::string &ring, int frame) {
  std::unordered_set<std::string> permutations;

  if (ring.size() == frame) {
    permutations.insert(ring);
    return {true, permutations};
  }
  // add at the end of string frame-1 characters from start
  // simulate cyclural buffer
  auto ringExtendedWithFrame = ring + std::string(ring, 0, frame - 1);

  for (size_t i = 0; i < ring.size(); ++i) {
    std::string permutation = std::string(ringExtendedWithFrame, i, frame);

    if (auto [p, success] = permutations.insert(permutation); !success) {
      return {false, {}};
    }
  }
  //
  //
  //  for(auto p : permutations)
  //  {
  //    std::cout <<p <<"\n";
  //  }
  return {true, permutations};
}

std::pair<bool, std::unordered_set<std::string>>
isStrUnique(const std::string &str, int frame)
{
  std::unordered_set<std::string> permutations;

  for (size_t i = 0; i < str.size()-frame+1; ++i) {
    std::string permutation = std::string(str, i, frame);

    if (auto [p, success] = permutations.insert(permutation); !success) {
      return {false, {}};
    }
  }
  //
  //
  //  for(auto p : permutations)
  //  {
  //    std::cout <<p <<"\n";
  //  }
  return {true, permutations};
}

std::string determine_pattern(const std::string &text, int windowSize) {
  int stringLength = std::pow(text.size(), windowSize);
  auto allPossiblePermutation = generatePermutationsForWindow(text, windowSize);

//  std::vector<std::string> allPossiblePermutation;
//  for(auto chars : allPossiblePermutationHash)
//  {
//    allPossiblePermutation.push_back(chars);
//  }
//  std::sort(allPossiblePermutation.begin(), allPossiblePermutation.end());

  // build initial text from concatenated patterns with the same characters
  // e.g "aaa" + "bbb"

  std::string result =  std::string(windowSize, text[0]);
//  auto [b, perms] = isRingUnique(result, windowSize);
//  for(const auto& p : perms)
//  {
//    allPossiblePermutation.erase(p);
//  }


  auto perm = allPossiblePermutation.begin();
  while (!allPossiblePermutation.empty() &&
         perm != allPossiblePermutation.end()) {
    // most cases add windowpermutation
    const auto missingCharacters = stringLength - result.length();
    if (missingCharacters >= windowSize) {
      auto t = *perm;
      auto tempStr = result + t;
      auto [b, perms] = isRingUnique(tempStr, windowSize);
//      auto [b, perms] = isStrUnique(tempStr, windowSize);
      if (b) {
        result = tempStr;
        for (auto p : perms) {
          allPossiblePermutation.erase(p);
        }
        perm = allPossiblePermutation.begin();
      } else {
        perm++;
      }
    } else {
      auto ss = result.size();
      // add last missing characters part of existing possible permutations
      for (const auto &perm : allPossiblePermutation) {
        std::string tempStr = result + std::string(perm, 0, missingCharacters);
        auto [b, perms] = isRingUnique(tempStr, windowSize);
//        auto [b, perms] = isStrUnique(tempStr, windowSize);
        if (b) {
          result = tempStr;
          return result;
        }
      }
    }
  }
//  if (result.size() != stringLength) {
//    return {};
//  }
  return result;
}