#include "KdTree.h"
#include "../iterator/ForwardIterator.cpp"
#include <queue>

/**
 * Node structure
 *
 * @tparam Point
 */
template<class Point>
struct KdTree<Point>::Node {
  Point data;
  Node *left;
  Node *right;
};

/**
 * Check if the tree is empty
 *
 * @tparam Point
 * @return boolean
 */
template<class Point>
bool KdTree<Point>::empty() {
  return !this->root;
}

/**
 * Check if the point exists in the tree, to avoid duplicate data
 *
 * @tparam Point
 * @param point
 * @param ptr
 * @return boolean
 */
template<class Point>
bool KdTree<Point>::find(Point &point, KdTree<Point>::Node **&ptr, int dimension) {
  if (this->rank != point.size()) {
    throw std::invalid_argument("All points must have the same dimension");
  }

  int currentDimension = dimension % this->rank;

  while (*ptr != nullptr) {
    if (point == (*ptr)->data) {
      return true;
    }

    if (point[currentDimension] < (*ptr)->data[currentDimension]) {
      dimension++;
      currentDimension = dimension % this->rank;
      ptr = &((*ptr)->left);
      continue;
    }

    dimension++;
    currentDimension = dimension % this->rank;

    ptr = &((*ptr)->right);
  }

  return false;
}

/**
 * Insert a new point
 * Avoid duplicate data through find function
 *
 * @tparam Point
 * @param point
 * @return boolean
 */
template<class Point>
bool KdTree<Point>::insert(Point &point) {
  Node **ptr = &root;

  if (!this->rank) {
    this->rank = point.size();
  }

  if (!find(point, ptr, 0)) {
    Node *tmp = new Node{point, nullptr, nullptr};
    *ptr = tmp;
    return true;
  }

  return false;
}
