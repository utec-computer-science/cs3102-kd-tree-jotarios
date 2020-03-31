#ifndef SRC_KDTREE_H
#define SRC_KDTREE_H

#include <vector>
#include<cmath>
#include <queue>
#include <limits>
#include <iostream>

template<class Point>
class KdTree {
  struct Node;

 private:
  Node *root = nullptr;
  int rank = 0;
  double bestDistance = std::numeric_limits<double>::infinity();
  Node *best;
  bool empty();
  bool find(Point &point, Node **&ptr, int dimension);
  double distance(Point &point, Point &query);
  Node *recursiveSearch(Point &query, Node *root, int dimension);

 public:
  bool insert(Point &point);
  Node *search(Point &query);
  void print();
  void print(Node *node);
};

#endif //SRC_KDTREE_H
