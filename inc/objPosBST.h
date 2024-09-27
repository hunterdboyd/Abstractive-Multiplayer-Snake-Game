#ifndef OBJPOSTREE_H
#define OBJPOSTREE_H

#include "objPos.h"

class objPos;

class TNode
{
    public:
        objPos data;
        TNode *left;
        TNode *right;

        TNode(const objPos &thisPos)
        {
            data = thisPos;
            left = nullptr;
            right = nullptr;
        }
};

// This tree is sorted using Prefix
class objPosBST
{
    private:
        TNode *root;

        // Private Recursive Functions
        void deleteTree(const TNode* thisNode);
        
        void printTree(const TNode* thisNode) const;        
        bool isInTree(const objPos& thisPos, const TNode* thisNode) const;
        void insert(const objPos &thisPos, TNode* &thisNode);
        void remove(const objPos &thisPos, TNode* &thisNode);
        const TNode* findMin(const TNode* thisNode) const;
        bool findGreater(const int numThreshold, const TNode* thisNode) const;


    public:
        objPosBST();
        ~objPosBST();

        bool isEmptyTree() const;

        void printTree() const;
        bool isInTree(const objPos &thisPos) const;
        void insert(const objPos &thisPos);
        void remove(const objPos &thisPos);

        bool isLeaf(const TNode *thisNode) const;
        void deleteTree();

        // Additional Feature - find if any object with Num greater than
        // threshold value
        bool findGreater(const int numThreshold) const;
};

#endif