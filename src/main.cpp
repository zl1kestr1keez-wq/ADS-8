// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& wordTree, const char* fileName);
void printFreq(BST<std::string>& wordTree);

int main() {
  BST<std::string> analysisTree;

  makeTree(analysisTree, "src/war_peace.txt");

  std::cout << "Tree depth: " << analysisTree.depth() << std::endl;
  std::cout << "\nWord descending:\n";
  std::cout << "--------------------------------\n";

  printFreq(analysisTree);

}
