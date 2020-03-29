#include <iostream>
#include "container/KdTree.cpp"

int main() {
  std::cout << "K-d Tree implementation" << std::endl;

  // Example 01
  std::vector<std::vector<int>> example1 = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19}};

  // Example 02
  std::vector<std::vector<int>> example2 = {{5, 25}, {15, 55}, {30, 40}, {35, 20}, {50, 50}};

  // Example 03
  std::vector<std::vector<int>> example3 = {{7, 2}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {2, 3}};

  // Example 04
  std::vector<std::vector<int>> example4 = {{30, 40}, {5, 25}, {10, 12}, {70, 70}, {50, 30}, {35, 45}};

  KdTree<std::vector<int>> tree;

  for (std::vector<int> &element : example1) {
    tree.insert(element);
  }

  tree.print();

  return 0;
}
