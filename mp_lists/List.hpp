/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_=0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1

  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);

}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode *temp=head_;
  while(temp!=NULL)
  {
    ListNode *temp2=temp->next;
    delete temp;
    temp=temp2;
  }
  tail_=NULL;
  head_=NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if(head_==NULL&&tail_==NULL)
  {
    head_=newNode;
    tail_=newNode;
    length_++;
  }
  else
  {
    head_->prev=newNode;
    newNode->next=head_;
    newNode->prev=NULL;
    head_=head_->prev;
    length_++;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode *newNode=new ListNode(ndata);
  if(head_==NULL&&tail_==NULL)
  {
    head_=newNode;
    tail_=newNode;
    length_++;
  }
  else
  {
    tail_->next=newNode;
    newNode->next=NULL;
    newNode->prev=tail_;
    tail_=newNode;
    length_++;
  }
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(start==NULL||start->next==NULL||splitPoint==0||splitPoint>=length_)
  {
    return start;
  }
  
  ListNode * curr = start;

  for (int i = 0; i < splitPoint; i++) {
    if(curr->next!=NULL)
    {
      curr = curr->next;
    }
    else
    {
      return start;
    }
  }

  if (curr != NULL) {
      tail_=curr->prev;
      curr->prev->next = NULL;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* temp=head_;
  ListNode* temp2[3];
  ListNode* temp3;
  int x=0;
  while((x<length_-length_%3)&&(temp!=NULL))
  {
    for(int i=0; i<3; i++)
    {
      temp2[i]=temp;
      temp=temp->next;
      x++;
    }
    if(temp2[0]==head_)
    {
      head_=temp2[1];
    }
    else
    {
      temp2[0]->prev->next=temp2[1];
    }
    if(temp2[2]!=tail_)
    {
      temp2[2]->next->prev=temp2[0];
    }
    temp2[0]->next=temp2[2]->next;
    temp3=temp2[0]->prev;
    temp2[0]->prev=temp2[2];
    temp2[1]->prev=temp3;
    temp2[2]->next=temp2[0];
  }
  tail_=head_;
  while(tail_->next!=NULL)
  {
    tail_=tail_->next;
  }
  

}


/**
 * Reverses the current List.
 */
template <typename T>
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
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if(startPoint==endPoint||startPoint==NULL||endPoint==NULL)
  {
    return;
  }
  ListNode* curr, *temp, *left, *right, *start, *end;
  left = startPoint->prev;
  right = endPoint->next;
  start = startPoint;
  end = endPoint;

  curr = startPoint;
  temp = NULL;

  while(curr != endPoint){
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }
  curr->next = curr->prev;
  curr->prev = left;
  startPoint->next = right;
  if(left != NULL){
    left->next = endPoint;
  }
  else{
    head_ = endPoint;
  }

  if(right != NULL){
    right->prev = startPoint;
  }
  else{
    tail_ = startPoint;
  }


  startPoint = end;
  endPoint = start;

  return;
  /// @todo Graded in MP3.2
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n<=1) 
  {
    return;
  }
  if(n>=length_)
  {
    reverse (head_, tail_);
    return;
  }
  ListNode *temp = head_;
  while(temp !=NULL)
 {
   ListNode *temp2 = temp;
   for (int i = 1; i<n; i++) 
   {
     if (temp==tail_) 
     {
       reverse(temp2, tail_);
       return;
     } 
     else 
     {
      temp = temp->next;
     }
   }
   reverse(temp2, temp);
   temp = temp->next;

 }
  

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
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
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first==NULL)
  {
    return second;
  }
  if(second==NULL)
  {
    return first;
  }
  ListNode *temp;
  ListNode *temp2;
  if(first->data<second->data)
  {
    temp=first;
    first=first->next;
  }
  else
  {
    temp=second;
    second=second->next;
  }
  temp2=temp;
  while(first!=NULL&&second!=NULL)
  {
    if(first->data<second->data)
    {
      temp->next=first;
      first->prev=temp;
      first=first->next;
    }
    else
    {
      temp->next=second;
      second->prev=temp;
      second=second->next;
    }
    temp=temp->next;
  }
  if(first!=NULL&&second==NULL)
  {
    temp->next=first;
    first->prev=temp;
    first=first->next;
    temp=temp->next;
  }
  else if(first==NULL&&second!=NULL)
  {
    temp->next=second;
    second->prev=temp;
    second=second->next;
    temp=temp->next;
  }
  return temp2;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength==0)
  {
    return NULL;
  }
  if(chainLength==1)
  {
    return start;
  }
  int x=chainLength/2;
  int rest=chainLength-x;
  ListNode *temp=split(start, x);
  ListNode *temp2=mergesort(start, x);
  ListNode *temp3=mergesort(temp, rest);
  return merge(temp2, temp3);
}
