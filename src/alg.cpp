// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& wordTree, const char* fileName) {
  std::ifstream inputFile(fileName);
  if (!inputFile) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string currentWord;
  int symbolCode;

  while ((symbolCode = inputFile.get()) != EOF) {
    if ((symbolCode >= 'A' && symbolCode <= 'Z') ||
        (symbolCode >= 'a' && symbolCode <= 'z')) {
      currentWord += static_cast<char>(
          std::tolower(static_cast<unsigned char>(symbolCode)));
    } else {
      if (!currentWord.empty()) {
        wordTree.insert(currentWord);
        currentWord.clear();
      }
    }
  }

  if (!currentWord.empty()) {
    wordTree.insert(currentWord);
  }

  inputFile.close();
}

void printFreq(BST<std::string>& wordTree) {
  std::vector<std::pair<std::string, int>> wordStats = wordTree.getAllElements();

  std::sort(wordStats.begin(), wordStats.end(),
            [](const std::pair<std::string, int>& firstItem,
               const std::pair<std::string, int>& secondItem) {
              if (firstItem.second != secondItem.second) {
                return firstItem.second > secondItem.second;
              }
              return firstItem.first < secondItem.first;
            });

  for (const auto& entry : wordStats) {
    std::cout << entry.first << " : " << entry.second << "\n";
  }

  std::ofstream outputFile("result/freq.txt");
  if (!outputFile) {
    std::cout << "Cannot open result/freq.txt for writing!" << std::endl;
    return;
  }

  for (const auto& entry : wordStats) {
    outputFile << entry.first << " : " << entry.second << "\n";
  }

  outputFile.close();
}
