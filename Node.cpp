#include "Node.h"

/*****************************************************************************
    Constructors/ Destructor
*****************************************************************************/
template <class T>
Node<T>::Node() : parent_(nullptr), data_(T()), left_(nullptr), right_(nullptr) {}

template <class T>
Node<T>::Node(Node<T>* parent, const T& data, Node<T>* left, Node<T>* right) : parent_(parent), data_(data), left_(left), right_(right) {}

template <class T>
Node<T>::Node(const Node<T>*& other) : parent_(other->parent_), data_(other->data_), left_(other->left_), right_(other->right_) {}

template <class T>
Node<T>::~Node() {
    parent_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
}

/*****************************************************************************
    Operator Overload
*****************************************************************************/
template <class T>
T& Node<T>::operator=(const Node<T>*& other) {
    parent_ = other->parent_;
    data_ = other->data_;
    left_ = other->left_;
    right_ = other->right_;
}

/*****************************************************************************
    Data Observation
*****************************************************************************/
template <class T>
Node<T>* Node<T>::getParent() const {
    return parent_;
}

template <class T>
T Node<T>::getData() const {
    return data_;
}

template <class T>
Node<T>* Node<T>::getLeft() const {
    return left_;
}

template <class T>
Node<T>* Node<T>::getRight() const {
    return right_;
}

/*****************************************************************************
    Data Modification
*****************************************************************************/
template <class T>
void Node<T>::setParent(Node<T>* parent) {
    parent_ = parent;
}

template <class T>
void Node<T>::setData(T data) {
    data_ = data;
}

template <class T>
void Node<T>::setLeft(Node<T>* left) {
    left_ = left;
}

template <class T>
void Node<T>::setRight(Node<T>* right) {
    right_ = right;
}