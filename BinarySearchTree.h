/*****************************************************************************
*    Brian Chairez                                                           *
*    Goal: Implementation of Binary Search Tree using dynamic nodes          *
*    Progess: Basic implementation and methods complete                      *
*****************************************************************************/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Node.cpp"

// Uses Binary Search Invariant for inserts. Not self-balancing.
template <class T>
class BinarySearchTree {
    private:
        Node<T>* root_;
        int size_;

        void insertNode_(const T& data);
        void deleteNode_(const T& data);
        Node<T>* copyPreOrder_(Node<T>* root);
        void deletePostOrder_(Node<T>* root);
    public:
        BinarySearchTree();
        BinarySearchTree(Node<T>*& root);
        BinarySearchTree(BinarySearchTree<T>& other);
        ~BinarySearchTree();
        T& operator=(const BinarySearchTree<T>& other);
        Node<T>* getRoot() const;
        bool insert(const T& data);
        bool erase(const T& data);
        void clear();
        bool contains(const T& data) const;
        bool empty() const;
        int size() const;
};

#endif