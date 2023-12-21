
// COS30008, Problem Set 4, Problem 1, 2022

#pragma once

#include <stdexcept>
#include <algorithm>

template<typename T>
struct BinaryTreeNode
{
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    
    T key;
    BTreeNode left;
    BTreeNode right;
    
    static BNode NIL;
    
    const T& findMax() const
    {
        if ( empty() )
        {
            throw std::domain_error( "Empty tree encountered." );
        }
        
        return right->empty() ? key : right->findMax();
    }

    const T& findMin() const
    {
        if ( empty() )
        {
            throw std::domain_error( "Empty tree encountered." );
        }
        
        return left->empty() ? key : left->findMin();
    }

    bool remove( const T& aKey, BTreeNode aParent )
    {
        BTreeNode x = this;
        BTreeNode y = aParent;

        while ( !x->empty() )
        {
            if ( aKey == x->key )
            {
                break;
            }

            y = x;                                      // new parent
            
            x = aKey < x->key ? x->left : x->right;
        }

        if ( x->empty() )
        {
            return false;                               // delete failed
        }
        
        if ( !x->left->empty() )
        {
            const T& lKey = x->left->findMax();         // find max to left
            x->key = lKey;
            x->left->remove( lKey, x );
        }
        else
        {
            if ( !x->right->empty() )
            {
                const T& lKey = x->right->findMin();    // find min to right
                x->key = lKey;
                x->right->remove( lKey, x );
            }
            else
            {
                if ( y != &NIL )                        // y can be NIL
                {
                    if ( y->left == x )
                    {
                        y->left = &NIL;
                    }
                    else
                    {
                        y->right = &NIL;
                    }
                }
                
                delete x;                               // free deleted node
            }
        }

        return true;
    }

    // PS4 starts here
    
    BinaryTreeNode() : key(T()), left(&NIL), right(&NIL) {}
    BinaryTreeNode(const T& aKey) : key(aKey), left(&NIL), right(&NIL) {}
    BinaryTreeNode(T&& aKey) : key(std::move(aKey)), left(&NIL), right(&NIL) {}

    ~BinaryTreeNode()
    {
        if (!left->empty())
        {
            delete left;
        }
        if (!right->empty())
        {
            delete right;
        }
    }
    
    bool empty() const
    {
        return this == &NIL;
    }
    bool leaf() const
    {
        return left->empty() && right->empty();
    }
    size_t height() const
    {
	    if (empty())
	    {
            throw domain_error("Empty tree encountered");
	    }
        if (leaf())
        {
            return 0;
        }

        size_t lheight, rheight;

        if (left->empty())
        {
            lheight = 0;
        }
        else
        {
            lheight = left->height();
        }

        if (right->empty())
        {
            rheight = 0;
        }
        else
        {
            rheight = right->height();
        }

        return max(lheight, rheight) + 1;
    }

    bool insert( const T& aKey )
    {
        BTreeNode copy = this;
        BTreeNode temp = &NIL;

        while ( !copy->empty() )
        {
            temp = copy;

            if (aKey == copy->key)
            {
                return false;
            }

            if (aKey < copy->key)
            {
                copy = copy->left;
            }
            else
            {
                copy = copy->right;
            }
        }

        BTreeNode node = new BinaryTreeNode<T>(aKey);

        if ( temp->empty() )
        {
            return false;
        }
        else
        {
	        if (aKey < temp->key)
	        {
                temp->left = node;
	        }
            else
            {
                temp->right = node;
            }
        }

        return true;
    }
};

template<typename T>
BinaryTreeNode<T> BinaryTreeNode<T>::NIL;
