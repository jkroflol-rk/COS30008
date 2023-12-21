
// COS30008, Problem Set 4, Problem 3, 2022

#pragma once

#include "BinarySearchTree.h"

#include <stack>

template<typename T>
class BinarySearchTreeIterator
{
private:
    
    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    using BTNStack = std::stack<BTreeNode>;

    const BSTree& fBSTree;		// binary search tree
    BTNStack fStack;			// DFS traversal stack
    
    void pushLeft( BTreeNode aNode )
    {
        while (aNode != &BNode::NIL)
        {
            fStack.push(aNode);
            aNode = aNode->left;
        }
    }
    
public:
    
    using Iterator = BinarySearchTreeIterator<T>;
    
    BinarySearchTreeIterator( const BSTree& aBSTree ) : fBSTree(aBSTree), fStack()
    {
        pushLeft(aBSTree.fRoot);
    }

    const T& operator*() const
    {
        return fStack.top()->key;
    }
    Iterator& operator++()
    {
        BTreeNode currentNode = fStack.top();
        fStack.pop();

        if (currentNode->right != &BNode::NIL)
        {
            pushLeft(currentNode->right);
        }

        return *this;
    }
    Iterator operator++(int)
    {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }
    bool operator==( const Iterator& aOtherIter ) const
    {
        return fStack == aOtherIter.fStack && &fBSTree == &aOtherIter.fBSTree;
    }
    bool operator!=( const Iterator& aOtherIter ) const
    {
        return !(*this == aOtherIter);
    }
    
    Iterator begin() const
    {
        Iterator b_iter = *this;
        b_iter.fStack = BTNStack();
        b_iter.pushLeft(b_iter.fBSTree.fRoot);
        return b_iter;
    }
    Iterator end() const
    {
        Iterator e_iter = *this;
        e_iter.fStack = BTNStack();
        return e_iter;
    }
};
