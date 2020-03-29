#ifndef SRC_KDTREE_H
#define SRC_KDTREE_H

#include <vector>
#include "../iterator/ForwardIterator.h"

template<class Point>
class KdTree {
  struct Node;

 private:
  Node *root = nullptr;
  int rank = 0;
  bool empty();
  bool find(Point &point, Node **&ptr, int dimension);

 public:
  bool insert(Point &point);
  bool search(Point &point);
  void print();
  ForwardIterator<Point, Node> begin();
  ForwardIterator<Point, Node> end();
};

#endif //SRC_KDTREE_H
