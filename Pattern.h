#pragma once

#include <algorithm>
#include <complex>
#include <iostream>
#include <random>
#include <set>
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

std::set<std::string>
generatePermutationsForWindow(const std::string &text, int windowLength) {
  std::set<std::string> permutations;

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
      auto newPermutations = generatePermutations(b);
      permutations.insert(newPermutations.begin(), newPermutations.end());
    }
  }
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

  return {true, permutations};
}

std::pair<bool, std::unordered_set<std::string>>
isStrUnique(const std::string &str, int frame) {
  std::unordered_set<std::string> permutations;

  for (size_t i = 0; i < str.size() - frame + 1; ++i) {
    std::string permutation = std::string(str, i, frame);

    if (auto [p, success] = permutations.insert(permutation); !success) {
      return {false, {}};
    }
  }

  return {true, permutations};
}

std::string determine_pattern(const std::string &text, int windowSize) {
  int stringLength = std::pow(text.size(), windowSize);
  const auto nonModifiableAllPossiblePermutations =
      generatePermutationsForWindow(text, windowSize);
  auto allPossiblePermutation = nonModifiableAllPossiblePermutations;

  std::random_device rd;

  // Choose a random mean between 0 and size
  std::default_random_engine e(rd());
  std::default_random_engine e1(rd());
  std::default_random_engine e2(rd());
  std::default_random_engine e3(rd());
  std::uniform_int_distribution<int> uniform_dist(0, text.size() - 1);
  auto pos = uniform_dist(e);
  auto pos1 = uniform_dist(e1);
  auto pos2 = uniform_dist(e2);
  auto pos3 = uniform_dist(e3);

  std::string lastPattern(windowSize, text[text.size() - 1]);
  std::string start(windowSize, text[1]);
  if(text.size()==3)
  {
    start = std::string(windowSize, text[2]);
  }
  //  start = "aaaabaaa";
  int group10 = 0;
  int group20 = 0;
  int group30 = 0;
  int group40 = 0;
  int group50 = 0;
  int group60 = 0;
  int group70 = 0;

  std::vector<std::string> potentialStarts;
//  start = "aaaabaaacaab";
  std::string result;
  int repeat = 0;
  int totalCounter = 0;
  while (result.size() != stringLength) {
    auto iter = allPossiblePermutation.begin();
    for (int count = 0; count < repeat; ++count) {
      iter++;
    }
    std::string s = *iter;
    //    auto result = start ;
    result = start + s;
    auto perm = allPossiblePermutation.begin();
    while (!allPossiblePermutation.empty() &&
           perm != allPossiblePermutation.end()) {
      const auto missingCharacters = stringLength - result.length();
      if (missingCharacters >= windowSize) {
        auto t = *perm;
        e = std::default_random_engine(rd());
        e1 = std::default_random_engine(rd());
        e2 = std::default_random_engine(rd());
        e3 = std::default_random_engine(rd());
        pos = uniform_dist(e);
        pos1 = uniform_dist(e1);
        pos2 = uniform_dist(e2);
        pos3 = uniform_dist(e3);
        t[0] = text[pos];
        t[1] = text[pos1];
        t[2] = text[pos2];
        t[3] = text[pos3];
        auto tempStr = result + t;
        auto [b, perms] = isRingUnique(tempStr, windowSize);
        if (b) {
          result = tempStr;
          allPossiblePermutation.erase(t);
          //          for (const auto &p : perms) {
          //            allPossiblePermutation.erase(p);
          //          }
          perm = allPossiblePermutation.begin();
        } else {
          perm++;
        }
      } else {
        // add last missing characters part of existing possible permutations
        for (const auto &perm : allPossiblePermutation) {
          std::string tempStr =
              result + std::string(perm, 0, missingCharacters);
          auto [b, perms] = isRingUnique(tempStr, windowSize);
          if (b) {
            result = tempStr;
            return result;
          }
        }
        perm = allPossiblePermutation.end();
      }
    }
    allPossiblePermutation = nonModifiableAllPossiblePermutations;
    if (result.size() == stringLength) {
      return result;
    } else {
      auto rSize = result.size();
      if (10 < rSize && rSize < 20) {
        group10++;
      } else if (20 < rSize && rSize < 30) {
        group20++;
      } else if (30 < rSize && rSize < 40) {
        group30++;
      } else if (40 < rSize && rSize < 50) {
        group40++;
      } else if (50 < rSize && rSize < 60) {
        group50++;
      } else if (60 < rSize && rSize < 70) {
        group60++;
        potentialStarts.push_back(result);
      } else if (70 < rSize && rSize < 80) {
        group70++;
        potentialStarts.push_back(result);
      }
      std::cout << result << " size: " << result.size() << "\n";
    }
    ++repeat;
    if (repeat == stringLength) {
      repeat = 0;
    }
    if (totalCounter == 10000) {

      std::cout << "10+: " << group10 << "\n";
      std::cout << "20+: " << group20 << "\n";
      std::cout << "30+: " << group30 << "\n";
      std::cout << "40+: " << group40 << "\n";
      std::cout << "50+: " << group50 << "\n";
      std::cout << "60+: " << group60 << "\n";
      std::cout << "70+: " << group70 << "\n";
      for (const auto &pot : potentialStarts) {
        std::cout << pot << "\n";
      }
      break;
    }
    totalCounter++;
  }
}