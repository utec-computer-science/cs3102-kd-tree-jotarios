#include "KdTree.h"

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

/**
 * Use a euclidean function to calculate the distance between two points
 *
 * @tparam Point
 * @param point
 * @param query
 * @return
 */
template<class Point>
double KdTree<Point>::distance(Point &point, Point &query) {
  double sum = 0.0;
  double distance;

  auto begin = point.begin();
  auto end = point.end();
  auto beginQuery = query.begin();

  while (begin != end) {
    distance = (*begin++) - (*beginQuery++);
    sum += distance * distance;
  }

  return sum > 0.0 ? std::sqrt(sum) : 0.0;
}

/**
 * Use a recursive search to find the NN to the query point.
 *
 * @tparam Point
 * @param query
 * @param node
 * @param dimension
 * @return
 */
template<class Point>
typename KdTree<Point>::Node *KdTree<Point>::recursiveSearch(Point &query, Node *node, int dimension) {
  if (node == nullptr || this->distance(node->data, query) > bestDistance) {
    return nullptr;
  }

  double distance = this->distance(node->data, query);

  if (distance < bestDistance) {
    bestDistance = distance;
    best = node;
  }

  dimension++;
  this->recursiveSearch(query, node->left, dimension % rank);
  this->recursiveSearch(query, node->right, dimension % rank);

  return best;
}

/**
 * Search the NN to the query point
 *
 * @tparam Point
 * @param query
 * @return
 */
template<class Point>
typename KdTree<Point>::Node *KdTree<Point>::search(Point &query) {
  if (this->empty()) {
    std::cout << "No results found. No points are available." << std::endl;
    return nullptr;
  }

  return this->recursiveSearch(query, this->root, 0);
}

/**
 * Print a node
 *
 * @tparam Point
 * @param node
 */
template<class Point>
void KdTree<Point>::print(Node *node) {
  std::cout << "(";

  for (auto init = node->data.begin(); init < (node->data.end() - 1); init++) {
    std::cout << *init << ", ";
  }

  std::cout << *(node->data.end() - 1) << ")" << std::endl;
}

/**
 * Level print of the Kd Tree
 *
 * @tparam Point
 */
template<class Point>
void KdTree<Point>::print() {
  std::queue<Node *> q;
  Node *node;

  q.push(this->root);

  while (!q.empty()) {
    node = q.front();
    q.pop();

    this->print(node);

    if (node->left != nullptr)
      q.push(node->left);

    if (node->right != nullptr)
      q.push(node->right);
  };
}
