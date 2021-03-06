/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  while(head_!= NULL){
      ListNode *temp = head_;
      head_ = head_->next;
      delete temp;
      temp = NULL;
    }
  head_ = NULL;
  tail_ = NULL;
  }

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if(head_ != NULL){
    ListNode* p = new ListNode(ndata);
    head_->prev = p;
    p->next = head_;
    p->prev = NULL;
    head_ = p;
  }
  else{
    head_ = new ListNode(ndata);
    head_->next = NULL;
    head_->prev = NULL;
    tail_ = head_;
  }
  length_ = length_ + 1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if(head_ != NULL){
    ListNode *p = new ListNode(ndata);
    p->next = NULL;
    p->prev = tail_;
    tail_->next = p;
    tail_ = p;
  }
  else{
    head_ = new ListNode(ndata);
    head_->next = NULL;
    head_->prev = NULL;
    tail_ = head_;
  }
  length_ = length_ + 1;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  ListNode* temp1 = startPoint;
  ListNode* temp2 = endPoint;
  if(startPoint == NULL || endPoint == NULL || startPoint == endPoint){   //A null or single node list
    return;
  }
  while(temp1 != temp2){
    ListNode* hold1 = temp1->prev;  //Series of ListNodes that preserve desired pointer addresses
    ListNode* hold2 = temp1->next;
    ListNode* hold3 = temp2->prev;
    ListNode* hold4 = temp2->next;
    if(temp1->next == temp2){   // Takes pointers that point to each other in the wrong order
      temp2->next = temp1;
      temp2->prev = hold1;
      temp1->prev = temp2;
      temp1->next = hold4;
      if(hold1 != NULL)
        hold1->next = temp2;
      if(hold4 != NULL)
        hold4->prev = temp1;
      break;
    }
    temp1->next = hold4;  //General case
    temp1->prev = hold3;
    temp2->next = hold2;
    temp2->prev = hold1;
    if(hold1 != NULL)     //Edge case of the head_ node
      hold1->next = temp2;
    hold2->prev = temp2;
    hold3->next = temp1;
    if(hold4 != NULL)     //Edge case of tail_ node
      hold4->prev = temp1;
    temp1 = hold2;
    temp2 = hold3;
  }
  temp1 = startPoint;   //Redefines pointers given outside function
  startPoint = endPoint;  //Basically head_ = tail_
  endPoint = temp1;       //tail_ = head_
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n){
  /// @todo Graded in MP3.1
  ListNode* startPoint = head_;
  int count = 0;
  while(count <= length_){
    ListNode* endPoint = startPoint;
    if((count+n) > length_){   //Edge case where n > # of elements remaining
      reverse(startPoint, tail_);
      if(count == 0){          //Edge case where n > length_
        tail_ = endPoint;
        head_ = startPoint;
      }
      break;
    }
    for(int i=1; i<n; i++){   //Loops through n nodes
      endPoint = endPoint->next;  //Updates endPoint node to node n away
    }
    reverse(startPoint, endPoint);   //Reverse desired endpoints
    if(count == 0)                //Sets new head node
      head_ = startPoint;
    if(startPoint == tail_)     //If you get to tail, it breaks (edge case)
        break;
    startPoint = endPoint->next;  //Advances the pointer to the next set
    if(startPoint == NULL)
      break;
    count = count +n;
  }
  startPoint = head_;
  while(startPoint != NULL){
    if(startPoint ->next == NULL)
      tail_ = startPoint;
    startPoint = startPoint->next;
  }

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if(head_ == NULL){
    return;
  }
  ListNode *temp1 = head_;
  ListNode * temp2 = temp1->next;
  while(temp2 !=NULL && temp2 != tail_){
    temp1->next = temp2->next;
    temp1->next->prev = temp1;
    tail_->next = temp2;
    temp2->prev = tail_;
    temp2->next = NULL;
    tail_ = temp2;
    temp1 = temp1->next;
    temp2 = temp1->next;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.

  //Possible edge cases
  //Negative integer
  //0
  //1

  return NULL;
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if(splitPoint == 0)
    return start;

  if (start == NULL || start->next == NULL){
    return start;
  }

  while(splitPoint != 1){
    start = start->next;
    splitPoint--;
  }

  ListNode*temp = start->next;
  start->next = NULL;
  temp->prev = NULL;
  return temp;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode *merger = NULL;
  ListNode *temp = first;
  ListNode *header = NULL;
  ListNode *holder = NULL;
  ListNode *equalTemp = NULL;

  if(first == NULL){    //Empty list cases
    return second;
  }
  if(second == NULL)
    return first;


  if(temp->data < second->data){   //These ifs give head value
    merger = temp;
    header = temp;
    temp = temp->next;
  }
  if(temp != NULL){
    if(second->data < temp->data && header == NULL){
      merger= second;
      header = second;
      second = second->next;
    }
  }
  if(temp != NULL && second != NULL){
    if(temp->data == second->data && header ==NULL){
      holder = temp->next;
      merger = temp;
      merger->next = second;
      merger = second;
      merger->prev = temp;
      header = temp;
      second = second->next;
      temp = holder;
    }
  }

while(second != NULL || temp!= NULL)
  while(second != NULL || temp!= NULL){  //If second list empty, just returns first
    if(temp == NULL){
      holder = merger;
      merger->next = second;
      merger = second;
      merger->prev = holder;
      second = second->next;
      break;
    }
    if(second == NULL){
      holder = merger;
      merger->next = temp;
      merger = temp;
      merger->prev = holder;
      temp = temp->next;
      break;
    }
    if(temp->data < second->data){
      holder = merger;
      merger->next = temp;
      merger = temp;
      merger->prev = holder;
      temp = temp->next;
      break;
    }
    if(second->data < temp->data){
      holder = merger;
      merger->next = second;
      merger = second;
      merger->prev = holder;
      second = second->next;
      break;
    }
    if(temp->data == second->data){
      equalTemp = temp->next;
      holder = merger;
      merger->next = temp;
      merger = temp;
      merger->prev = holder;
      holder = merger;
      merger->next = second;
      merger = second;
      merger->prev = holder;
      temp = equalTemp;
      second = second->next;
      break;
    }
  }
  first = header;
  return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1){
    return start;
  }
  int half = chainLength/2;
  ListNode* list1 = start;
  ListNode* list2 = split(list1, half);
  list1 = mergesort(list1, half);
  list2 = mergesort(list2, chainLength - half);

  list1 = merge(list1, list2);
  return list1;
}
