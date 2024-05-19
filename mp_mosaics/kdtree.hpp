/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim]<second[curDim])
    {
      return true;
    }
    else if(first[curDim]>second[curDim])
    {
      return false;
    }
    else
    {
      return first<second;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double currentBestVal, potentialVal;
    for(int i=0; i<Dim; i++)
    {
      currentBestVal=currentBestVal+pow(currentBest[i]-target[i], 2);
      potentialVal=potentialVal+pow(potential[i]-target[i], 2);
    }
    if(potentialVal<currentBestVal)
    {
      return true;
    }
    else if(potentialVal>currentBestVal)
    {
      return false;
    }
    else
    {
      return potential<currentBest;
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    root=NULL;
    for(const Point<Dim>&point : newPoints)
    {
      sortedList.push_back(point);
    }
    size=0;
    int current, start, end;
    current=0;
    start=0;
    end=sortedList.size()-1;
    root=Helper(current, start, end);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::Helper(int current, int start, int end)
{
  int sizeList=sortedList.size();
  if(sortedList.empty()||start<0||end<0||start>end||start>=sizeList||end>=sizeList)
  {
    return NULL;
  }
  int dif=end-start;
  dif=dif+1;
  int midDif=dif/2;
  if(dif%2==0)
  {
    
  }
  else
  {
    midDif=midDif+1;
  }
  int mid=quickSelect(start, end, current, midDif);
  size++;
  KDTreeNode* subRoot=new KDTreeNode(sortedList[mid]);
  subRoot->right=Helper((current+1)%Dim, mid+1, end);
  subRoot->left=Helper((current+1)%Dim, start, mid-1);
  return subRoot;
}

template <int Dim>
int KDTree<Dim>::quickSelect(int start, int end, int current, int midDif)
{
  if(start==end)
  {
    return start;
  }
  int pivot=quickSelectHelper(start, end, current);
  int dif1=pivot-start;
  int dif2=midDif-1;
  int dif3=midDif-pivot;
  if(dif1==dif2)
  {
    return pivot;
  }
  if(dif1>dif2)
  {
    return quickSelect(start, pivot-1, current, midDif);
  }
    dif3=dif3-1;
    return quickSelect(pivot+1, end, current, dif3+start);
}

template <int Dim>
int KDTree<Dim>::quickSelectHelper(int start, int end, int current)
{
  Point<Dim> temp;
  Point<Dim> pivot=sortedList[end];
  int index=start-1;
  for(int i=start; i<end; i++)
  {
    if(smallerDimVal(sortedList[i], pivot, current))
    {
      index++;
      temp=sortedList[index];
      sortedList[index]=sortedList[i];
      sortedList[i]=temp;
    }
  }
  index++;
  temp=sortedList[end];
  sortedList[end]=sortedList[index];
  sortedList[index]=temp;
  return index;
  
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  this=new KDTree(other.sortedList);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(*this==rhs)
  {
    return *this;
  }
  else
  {
    this->size=rhs.size;
    Destroy(root);
    root=Destroy(rhs.root);
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  Destroy(root);
}

template <int Dim>
void KDTree<Dim>::Destroy(KDTreeNode* root)
{
  if(root==nullptr)
  {
    return;
  }
  else
  {
    Destroy(root->left);
    Destroy(root->right);
    delete root;
  }
}

template <int Dim>
int KDTree<Dim>::distance(const Point<Dim>& first, const Point<Dim>& second) const
{
  int x=0;
  for(int i=0; i<Dim; i++)
  {
    x=x+(first[i]-second[i])*(first[i]-second[i]);
  }
  return x;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return neighborHelper(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::neighborHelper(const Point<Dim>& query, KDTreeNode* root, int current) const
{
  if(root->left==NULL&&root->right==NULL)
  {
    return root->point;
  }
  int next=(current+1)%Dim;
  Point<Dim> curr=root->point;
  Point<Dim> potential=curr;
  bool ok=smallerDimVal(query, curr, current);
  if(ok && root->left!=NULL)
  {
    potential=neighborHelper(query, root->left, next);
  }
  else if(!ok && root->right!=NULL)
  {
    potential=neighborHelper(query, root->right, next);
  }

  if(shouldReplace(query, curr, potential))
  {
    curr=potential;
  }

  int radius = distance(query, curr);
  int radius2= (query[current] - root->point[current])*(query[current] - root->point[current]);
  if(radius2<=radius)
  {
    if(!ok && root->left!=NULL)
    {
      potential=neighborHelper(query, root->left, next);
      if(shouldReplace(query, curr, potential))
      {
        curr=potential;
      }
    }
    else if(ok && root->right!=NULL)
    {
      potential=neighborHelper(query, root->right, next);
      if(shouldReplace(query, curr, potential))
      {
        curr=potential; 
      }
    }
  }
  return curr;
}

