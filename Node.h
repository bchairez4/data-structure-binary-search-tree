#ifndef NODE_H
#define NODE_H

// CONSIDER CHANGING THE NODE TO HOLD A std::pair<K, V> data TO EMULATE KEY VALUE PAIRS TO FORMALY EMULATE A MAP INSTEAD OF T data

template <class T>
class Node {
    private:
        Node<T>* parent_;
        T data_;
        Node<T>* left_;
        Node<T>* right_;
    public:
        Node();
        Node(Node<T>* parent, const T& data, Node<T>* left, Node<T>* right);
        Node(const Node<T>*& other);
        ~Node();
        T& operator=(const Node<T>*& other);
        T getData() const;
        Node<T>* getParent() const;
        Node<T>* getLeft() const;
        Node<T>* getRight() const;
        void setParent(Node<T>* parent); 
        void setData(T data);
        void setLeft(Node<T>* left);
        void setRight(Node<T>* right);
};

#endif