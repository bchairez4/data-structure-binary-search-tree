#include "BinarySearchTree.h"

/*****************************************************************************
    Constructors/ Destructor
*****************************************************************************/
template <class T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr), size_(0) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(Node<T>*& root) : root_(nullptr), size_(0) {
    root_ = copyPreOrder_(root);
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>& other) : root_(nullptr), size_(0) {
    root_ = copyPreOrder_(other.root_);
    size_ = other.size_;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear();
}

/*****************************************************************************
    Operator Overloading 
*****************************************************************************/
template <class T>
T& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other) {
    root_ = copyPreOrder_(other.root_);
    size_ = other.size_;
}

/*****************************************************************************
    Node/Data Manipulation
*****************************************************************************/
template <class T>
bool BinarySearchTree<T>::insert(const T& data) {
    if (contains(data)) {
        return false;
    }

    insertNode_(data);
    ++size_;
    return true;
}

template <class T>
bool BinarySearchTree<T>::erase(const T& data) {
    if (!contains(data)) {
        return false;
    }

    deleteNode_(data);
    --size_;
    return true;
}

template <class T>
void BinarySearchTree<T>::clear() {
    deletePostOrder_(root_);
    root_ = nullptr;
    size_ = 0;
}

/*****************************************************************************
    Node/Data Observation
*****************************************************************************/
template <class T>
Node<T>* BinarySearchTree<T>::getRoot() const {
    return root_;
}

template <class T>
bool BinarySearchTree<T>::contains(const T& data) const {
    if (empty()) {
        return false;
    }

    Node<T>* curr_node = root_;
    while (curr_node != nullptr) {
        if (data < curr_node->getData()) {
            curr_node = curr_node->getLeft();
        }
        else if (data > curr_node->getData()) {
            curr_node = curr_node->getRight();
        }
        else if (data == curr_node->getData() ){
            return true;
        }
    }

    return false;
}

template <class T>
bool BinarySearchTree<T>::empty() const {
    return size_ == 0;
}

template <class T>
int BinarySearchTree<T>::size() const {
    return size_;
}

/*****************************************************************************
    Private Functions
*****************************************************************************/
// Assumes the node does not already exist
template <class T>
void BinarySearchTree<T>::insertNode_(const T& data) {
    Node<T>* parent = nullptr;
    Node<T>* child = root_;

    //Look for where the node SHOULD be
    while (child != nullptr) {
        parent = child; 
        if (data < child->getData()) {
            child = child->getLeft();
        }
        else {
            child = child->getRight();
        }
    }

    //Handle child node creation
    child = new Node<T>(parent, data, nullptr, nullptr);

    //Handle parent pointer
    if (parent == nullptr) {
        root_ = child;
    }
    else if (data < parent->getData()) {
        parent->setLeft(child);
    }
    else {
        parent->setRight(child);
    }

}

// Assumes the node actually exists
template <class T>
void BinarySearchTree<T>::deleteNode_(const T& data) {
    Node<T>* parent = nullptr;
    Node<T>* child = root_;

    //Look for where the node is
    while (child->getData() != data) {
        parent = child; 
        if (data < child->getData()) {
            child = child->getLeft();
        }
        else {
            child = child->getRight();
        }
    }

    //CASE 1: node has 0 children
    if (child->getLeft() == nullptr && child->getRight() == nullptr) {
        delete child;
        //If you're deleting the root, update the root pointer
        if (parent == nullptr) {
            root_ = nullptr;
            return;
        }

        //update parent's left/right pointer
        if (data < parent->getData()) {
            parent->setLeft(nullptr);
        }
        else {
            parent->setRight(nullptr);
        }

        return;
    }

    //CASE 2: node has 2 children, have to find inorder successor to replace the node then delete successsor
    if (child->getLeft() != nullptr && child->getRight() != nullptr) {
        //go right once then left all the way down to find inorder successor
        Node<T>* successor = child;
        successor = successor->getRight();
        while (successor->getLeft() != nullptr) {
            successor = successor->getLeft();
        }

        //Node gets overwritten not deleted
        child->setData(successor->getData());

        //if successor has 1 child; will always be on the right
        if (successor->getRight() != nullptr) { //1 child
            //change the successors child's parent pointer
            successor->getRight()->setParent(successor->getParent());

            //change the successors parent's left/right pointer
            if (successor->getRight()->getData() < successor->getParent()->getData()) {
                successor->getParent()->setLeft(successor->getRight());
            }
            else {
                successor->getParent()->setRight(successor->getRight());
            }

            delete successor;
            return;
        }
        else {  //successor has 0 children
            if (successor->getData() < successor->getParent()->getData()) {
                successor->getParent()->setLeft(nullptr);
            }
            else if (successor->getData() > successor->getParent()->getData()){
                successor->getParent()->setRight(nullptr);
            }
            else {
                successor->getParent()->setRight(nullptr);
            }

            delete successor;
            return;
        }
    }
    //CASE 3: node has 1 child
    else {
        //Locate the one child, aka grandchild
        Node<T>* grandchild = nullptr;
        if (child->getLeft() != nullptr) {
            grandchild = child->getLeft();
        }
        else {
            grandchild = child->getRight();
        }

        //If you're deleting the root, update root pointer
        if (parent == nullptr) {
            root_ = grandchild;
            grandchild->setParent(nullptr);
            delete child;
            return;
        }

        //update grandchild's parent pointer
        grandchild->setParent(parent);

        //update parent's left/right pointer
        if (grandchild->getData() < parent->getData()) {
            parent->setLeft(grandchild);
        }
        else {
            parent->setRight(grandchild);
        }

        delete child;
    }
}

template <class T>
Node<T>* BinarySearchTree<T>::copyPreOrder_(Node<T>* root) {
    Node<T>* new_root = nullptr;
    if (root != nullptr) {
        new_root = new Node<T>;
        new_root->setParent(root->getParent());
        new_root->setData(root->getData());
        ++size_;
        new_root->setLeft(copyPreOrder_(root->getLeft()));
        new_root->setRight(copyPreOrder_(root->getRight()));
    }
    else {
        return nullptr;
    }

    return new_root;
}

template <class T>
void BinarySearchTree<T>::deletePostOrder_(Node<T>* root) {
    if (root != nullptr) {
        deletePostOrder_(root->getLeft());
        deletePostOrder_(root->getRight());
        delete root;
        --size_;
    }
}