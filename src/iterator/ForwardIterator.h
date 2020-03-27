#ifndef SRC_FORWARDITERATOR_H
#define SRC_FORWARDITERATOR_H

#include <iostream>

/*
 * This is an in-order fashion iterator
 *
 * */

template<class Point, class Node>
class ForwardIterator : std::iterator<std::forward_iterator_tag, Point> {
 private:
  Node *current;

 public:
  ForwardIterator(Node *root) : current(root) {};

  bool operator!=(const ForwardIterator &toCompare) {}

  ForwardIterator &operator++(int _increment) {}

  Point operator*() const {}
};

#endif //SRC_FORWARDITERATOR_H
