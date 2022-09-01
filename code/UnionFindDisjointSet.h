/*
 * Union-Find Disjoint Set
 */

#include <vector>

class UnionFindDisjointSet
{
public:
   void initSet(int N)
   {
      pset_.assign(N, 0);
      for (int i = 0; i < N; ++i) {
         pset_[i] = i;
         pSetSize_[i] = 1;
      }
      numSets_ = N;
   }

   int findSet(int i)
   {
      return (pset_[i] == i) ? i : (pset_[i] = findSet(pset_[i]));
   }

   bool isSameSet(int i, int j)
   {
      return findSet(i) == findSet(j);
   }

   void unionSet(int i, int j)
   {
      int iRoot = findSet(i);
      int jRoot = findSet(j);
      pset_[iRoot] = jRoot;
      pSetSize_[jRoot] += pSetSize_[iRoot];
      numSets_--;
   }

   int numDisjointSets()
   {
      return numSets_;
   }

   int sizeOfSet(int i)
   {
      return pSetSize_[findSet(i)];
   }

private:
   std::vector<int> pset_;
   std::vector<int> pSetSize_;
   int numSets_;
};
