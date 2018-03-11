#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  pngbfs = png;
  startbfs = start;
  tolerancebfs = tolerance;
  q.enqueue(start);
  for(i=0; i<png.width; i++){
    for(j=0; j<png.height; j++){
      list[i][j] = 0;
    }
  }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(startbfs);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  if(point.x < pngdfs.width_){      //Might have to be pngdfs.width_ -1
    Point right(point.x+1, point.y);
    q.enqueue(right);
  }
  if(point.y < pngdfs.height_){
    Point down(point.x, point.y+1);
    q.enqueue(down);
  }
  if(point.x > 0){
    Point left(point.x-1, point.y);
    q.enqueue(left);
  }
  if(point.y > 0){
    Point up(point.x, point.y -1);
    q.enqueue(up);
  }

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point top = q.front();
  while(list[top.x][top.y] == 1){
    q.dequeue();
    top = q.front()
  }
  list[top.x][top.y] = 1;
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return true;
}
