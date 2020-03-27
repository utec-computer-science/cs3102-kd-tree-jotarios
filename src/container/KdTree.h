#ifndef SRC_KDTREE_H
#define SRC_KDTREE_H

#include <vector>
#include "../iterator/ForwardIterator.h"

template<class Point>
class KdTree {
  struct Node;

 private:
  Node *root;
  bool empty();

 public:
  bool insert(Point &element);
  bool search(Point &element);
  void print();
  ForwardIterator<Point, Node> begin();
  ForwardIterator<Point, Node> end();
};

#endif //SRC_KDTREE_H
