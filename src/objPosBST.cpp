#include "objPosBST.h"

#include <iostream>
using namespace std;

objPosBST::objPosBST()
{
    root = nullptr;
}

objPosBST::~objPosBST()
{
    deleteTree(root);
    root = nullptr;
}

void objPosBST::deleteTree(const TNode* thisNode)
{
	if(thisNode != NULL)
	{
		deleteTree(thisNode->left);
		deleteTree(thisNode->right);
		delete thisNode;
	}

	// Post-Order Traversal will always process the leaf nodes first,
	// then progress hierarchically back towards the root.
	// Proper deletion sequence
}

void objPosBST::deleteTree()
{
    deleteTree(root);
    root = nullptr;
}

bool objPosBST::isEmptyTree() const
{
    return (root == NULL);
}

bool objPosBST::isLeaf(const TNode *thisNode) const
{
    return (thisNode != NULL && thisNode->left == NULL && thisNode->right == NULL);
}


void objPosBST::printTree(const TNode* thisNode) const  // private recursive
{
    if(thisNode != NULL)
    {
        objPos temp;

        printTree(thisNode->left);
        temp = thisNode->data; // print data
        cout << temp.getPF() << temp.getNum() << " ";
        printTree(thisNode->right);
    }
}

void objPosBST::printTree() const  // public interface
{    
    if(root == NULL)
    {
        cout << "[Enpty]";
        return;
    }

    //cout << "[Binary Search Tree Printout]" << endl;
    printTree(root);
    //cout << "[End of Binary Search Tree Printout]" << endl;
}

bool objPosBST::isInTree(const objPos& thisPos, const TNode* thisNode) const
{
    if(thisNode == NULL)     
        return false;
    else
    {
        objPos temp = thisNode->data;
        if(thisPos.getPF() < temp.getPF()) // The left half
            return isInTree(thisPos, thisNode->left);
        else if(thisPos.getPF() > temp.getPF()) // the right half
            return isInTree(thisPos, thisNode->right);
        else
            return true;
    }    
}

bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root);
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode* &thisNode)
{
    if(thisNode == NULL)
        thisNode = new TNode(thisPos);
    else
    {
        objPos temp = thisNode->data;
        if(thisPos.getPF() < temp.getPF()) // The left half
            insert(thisPos, thisNode->left);
        else if(thisPos.getPF() > temp.getPF()) // the right half
            insert(thisPos, thisNode->right);
        else // if found, add up the number
            thisNode->data.setNum(thisNode->data.getNum() + thisPos.getNum());
    }
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root);
}


const TNode* objPosBST::findMin(const TNode* thisNode) const
{
	if(thisNode == NULL)		// Empty Sub-tree
		return NULL;

	while(thisNode->left != NULL)  // Traverse
		thisNode = thisNode->left;

	return thisNode;			// Return min node
}


void objPosBST::remove(const objPos &thisPos, TNode* &thisNode)
{
	if(thisNode == NULL)
		return;

    objPos temp = thisNode->data;

	if(thisPos.getPF() < temp.getPF())  // find the node in the tree using binary search
		remove(thisPos, thisNode->left);
	else if(thisPos.getPF() > temp.getPF())
		remove(thisPos, thisNode->right);

	// Case 3 - Delete node with 2 children (Method 1)
	else if(thisNode->left != NULL && thisNode->right != NULL)
	{
		thisNode->data = findMin(thisNode->right)->data;
		remove(thisNode->data, thisNode->right);
	}

	// Case 1 and 2 both handled here.  Think about how
	else
	{
		TNode* oldNode = thisNode;
		thisNode = (thisNode->left != NULL)? thisNode->left : thisNode->right;
		delete oldNode;
	}
}

void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root);
}

bool objPosBST::findGreater(const int numThreshold, const TNode* thisNode) const
{
    if(thisNode == NULL)     
        return false;
    
    objPos temp = thisNode->data;

    bool leftTh = findGreater(numThreshold, thisNode->left);
    bool rightTh = findGreater(numThreshold, thisNode->right);
    bool currTh = temp.getNum() >= numThreshold;

    return leftTh || rightTh || currTh;

}

bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root);
}
