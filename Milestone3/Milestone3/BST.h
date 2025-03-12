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
    void preorder(Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
    void postorder(Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }

    /// <summary>
    /// Recursively dig to find smallest node by visiting left
    /// Could put this into remove but seperated for visibility
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
    Node* findMin(Node* node)
    {
        while (node != nullptr && node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    bool deleteNode(Node*& node, const T& value)
    {
        //Base case, the if else below will return
        //this and recurse upwards with it if the 
        //searching didnt find a value that == it
        if (node == nullptr)
        {
            return false;
        }

        if (value < node->data)
        {
            return deleteNode(node->left, value);
        }
        else if (value > node->data)
        {
            return deleteNode(node->right, value);
        }


        // after searching for the node if not > or <, must be ==
        else
        {
            //empty left
            if (node->left == nullptr)
            {
                Node* temp = node->right;
                delete node;
                node = temp;
            }
            //empty right
            else if (node->right == nullptr)
            {
                Node* temp = node->left;
                delete node;
                node = temp;
            }
            else
            {
                //look for the smallest node in the RIGHT subtree to replace the 
                //deleted node, since all nodes in the LEFT subtree will still 
                //be smaller to it and all nodes in the new RIGHT tree will be 
                //larger than the replacement
                Node* minRight = findMin(node->right);
                node->data = minRight->data;
                return deleteNode(node->right, minRight->data);
            }
            return true;
        }
    }

    /// <summary>
    /// Destructor
    /// </summary>
    /// <param name="node"></param>
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
    void bstPreorder() const { preorder(root); }
    void bstPostorder() const { postorder(root); }
    bool bstDeleteNode(const T& value) { return deleteNode(root, value); }
};
#endif