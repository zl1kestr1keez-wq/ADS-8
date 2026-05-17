// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct TreeNode {
    T data;
    int repeats;
    TreeNode* leftChild;
    TreeNode* rightChild;

    explicit TreeNode(const T& value)
        : data(value), repeats(1), leftChild(nullptr), rightChild(nullptr) {}
  };

  TreeNode* rootNode;

  TreeNode* addNode(TreeNode* currentNode, const T& value) {
    if (currentNode == nullptr) {
      return new TreeNode(value);
    }

    if (value < currentNode->data) {
      currentNode->leftChild = addNode(currentNode->leftChild, value);
    } else if (value > currentNode->data) {
      currentNode->rightChild = addNode(currentNode->rightChild, value);
    } else {
      currentNode->repeats++;
    }

    return currentNode;
  }

  int calcDepth(TreeNode* currentNode) const {
    if (currentNode == nullptr) {
      return -1;
    }

    int leftHeight = calcDepth(currentNode->leftChild);
    int rightHeight = calcDepth(currentNode->rightChild);

    return 1 + std::max(leftHeight, rightHeight);
  }

  TreeNode* findNode(TreeNode* currentNode, const T& value) const {
    if (currentNode == nullptr || currentNode->data == value) {
      return currentNode;
    }

    if (value < currentNode->data) {
      return findNode(currentNode->leftChild, value);
    }

    return findNode(currentNode->rightChild, value);
  }

  void collectPairs(TreeNode* currentNode,
                    std::vector<std::pair<T, int>>& items) const {
    if (currentNode == nullptr) {
      return;
    }

    collectPairs(currentNode->leftChild, items);
    items.push_back(std::make_pair(currentNode->data, currentNode->repeats));
    collectPairs(currentNode->rightChild, items);
  }

  void deleteSubtree(TreeNode* currentNode) {
    if (currentNode == nullptr) {
      return;
    }

    deleteSubtree(currentNode->leftChild);
    deleteSubtree(currentNode->rightChild);
    delete currentNode;
  }

 public:
  BST() : rootNode(nullptr) {}

  ~BST() {
    deleteSubtree(rootNode);
  }

  void insert(const T& value) {
    rootNode = addNode(rootNode, value);
  }

  int depth() const {
    return calcDepth(rootNode);
  }

  int search(const T& value) const {
    TreeNode* foundNode = findNode(rootNode, value);
    if (foundNode == nullptr) {
      return 0;
    }
    return foundNode->repeats;
  }

  std::vector<std::pair<T, int>> getAllElements() const {
    std::vector<std::pair<T, int>> result;
    collectPairs(rootNode, result);
    return result;
  }

  bool empty() const {
    return rootNode == nullptr;
  }
};

#endif  // INCLUDE_BST_H_
