#ifndef BST_H
#define BST_H

#include <iostream>

template <typename T>
class BinarySearchTree
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;


    /// <summary>
    /// Recurses to the bottom until it finds a node with no children, but
    /// the value is still > or <, which means it's time to add a new node
    /// </summary>
    /// <param name="node">Reference to a pointer</param>
    /// <param name="value"></param>
    void insert(Node*& node, const T& value)
    {
        //base case
        if (node == nullptr)
        {
            node = new Node(value);
        }
        else if (value < node->data)
        {
            insert(node->left, value);
        }
        else if (value > node->data)
        {
            insert(node->right, value);
        }
    }

    const T* search(Node* node, const T& value) const
    {
        if (node == nullptr)
        {
            //If we get here, that means the search went all the way down, checked the 
            //value of the bottom node, and determine that the value was still > or < to it
            //but there were no more left or right pointers, so the value doesnt exist
            return nullptr;
        }
        if (node->data == value)
        {
            //returns a pointer to the data by taking the address of node->data 
            // and returning a pointer to it. 
            return &(node->data);
        }
        //condensing the if/else into a ternary operator. If the value to look for is
        //less than the current node, move to the current node's left, else, etc.
        //Similar to insert
        return value < node->data ? search(node->left, value) : search(node->right, value);
    }

    void inorder(Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    void destroy(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { destroy(root); }

    void bstInsert(const T& value) { insert(root, value); }
    const T* bstSearch(const T& value) const { return search(root, value); }
    void bstInorder() const { inorder(root); }
};
#endif