#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  pngdfs = png;
  startdfs = start;
  tolerancedfs = tolerance;
  s.push(start);
  for(i=0; i<png.width; i++){
    for(j=0; j<png.height; j++){
      list[i][j] = 0;
    }
  }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */  
  ImageTraversal* traversal = new ImageTraversal();
  return ImageTraversal::Iterator(*traversal, startdfs);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  if(point.x < pngdfs.width_-1){
    Point right(point.x+1, point.y);
    if(right != )
      s.push(right);
  }
  if(point.y < pngdfs.height_ -1){
    Point down(point.x, point.y+1);
    s.push(down);
  }
  if(point.x > 0){
    Point left(point.x-1, point.y);
    s.push(left);
  }
  if(point.y > 0){
    Point up(point.x, point.y -1);
    s.push(up);
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point top = s.top();
  while(list[top.x][top.y] == 1){
    s.pop();
    top = s.top()
  }
  list[top.x][top.y] = 1;
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return s.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if(s.empty())
    return true;
  else
    return false;
}
