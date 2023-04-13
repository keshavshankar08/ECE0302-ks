#include "binary_search_tree.hpp"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs.root;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}


template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(BinarySearchTree<KeyType, ItemType> rhs)
{
    swap(rhs);
    return *this;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::swap(BinarySearchTree<KeyType, ItemType>& rhs)
{
    std::swap(root, rhs.root);
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}


template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    //if the tree has elements already
    if(!isEmpty()){
        //search for they key
        Node<KeyType, ItemType> *insertionPoint = new Node<KeyType, ItemType>;
        Node<KeyType, ItemType> *postInsertionPoint = new Node<KeyType, ItemType>;
        search(key, insertionPoint, postInsertionPoint);

        //check for dupe after insertion point
        if(insertionPoint->key == key){
            return false;
        }

        //create insertion node with data
        Node<KeyType, ItemType> *insertionNode = new Node<KeyType, ItemType>;
        insertionNode->setMembers(key, item);

        //connect the pointers for new node to tree
        if(insertionPoint->key > key){
            insertionPoint->left = insertionNode;
        }
        else if(insertionPoint->key < key){
            insertionPoint->right = insertionNode;
        }
    }
    //if the tree is empty
    else{
        //create root with key and item
        root = new Node<KeyType, ItemType>;
        root->setMembers(key, item);
    }

    return true;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    // case, zero things in the tree
    if(isEmpty()){
        return false;
    }

    // case one thing in the tree
    if(root->left == 0 && root->right == 0){
        //remove it if it matches key
        if(root->key == key){
            root = 0;
            delete root;
            return true;
        }
        //doesnt match and only element
        else{
            return false;
        }
    }

    //find the key
    Node<KeyType, ItemType> *deletionNode, *parentNode;
    search(key, deletionNode, parentNode);
    
    //if key not found fail
    if(deletionNode->key != key){
        return false;
    }

    //flags
    bool rootNode, leftNode;

    //figure out if at root
    parentNode == 0 ? rootNode = false : rootNode = true;

    //figure out if removing left or right child
    if(rootNode == false){
        parentNode->left == deletionNode ? leftNode = true : leftNode = false;
    }

    //temp node for when parent deletion
    Node<KeyType,ItemType> *tempNode = new Node<KeyType,ItemType>;
    
    // case, item to delete has no children
    if(deletionNode->left == 0 && deletionNode->right == 0){
        //since its root node, there no longer are children
        if(rootNode){
            root = 0;
        }
        else if(leftNode){
            parentNode->left = 0;
        }
        else{
            parentNode->right = 0;
        }

        return true;
    }

    // case, item to delete has only a right child
    else if(deletionNode->left == 0 && deletionNode->right != 0){
        tempNode->setMembers(deletionNode->right->key, deletionNode->right->data);
        tempNode->setChildren(deletionNode->right->left, deletionNode->right->right);

        //if root, update
        if(rootNode){
            root = tempNode;
        }
        //update corresponding child
        else if(leftNode){
            parentNode->left = tempNode;
        }
        else{
            parentNode->right = tempNode;
        }

        return true;
    }

    // case, item to delete has only a left child
    else if(deletionNode->left != 0 && deletionNode->right == 0){
        tempNode->setMembers(deletionNode->left->key, deletionNode->left->data);
        tempNode->setChildren(deletionNode->left->left, deletionNode->left->right);

        //if root, update
        if(rootNode){
            root = tempNode;
        }
        //update corresponding child
        else if(leftNode){
            parentNode->left = tempNode;
        }
        else{
            parentNode->right = tempNode;
        }

        return true;
    }

    // case, item to delete has two children
    else if(deletionNode->left != 0 && deletionNode->right != 0){
        //find in order successor
        Node<KeyType,ItemType> *inorderSuccessor = new Node<KeyType,ItemType>;
        Node<KeyType,ItemType> *parentSuccessor = new Node<KeyType,ItemType>;
        inorder(deletionNode, inorderSuccessor, parentSuccessor);

        //move data to deletion node
        deletionNode->setMembers(inorderSuccessor->key, inorderSuccessor->data);

        //remove successor
        if(parentSuccessor->left == inorderSuccessor){
            delete inorderSuccessor;
            parentSuccessor->left = 0;
        }
        else if(parentSuccessor->right == inorderSuccessor){
            delete inorderSuccessor;
            parentSuccessor->right = 0;
        }

        return true;
    }

    delete deletionNode;
    return false; // default should never get here
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
    //make in the successor of curr
    if(curr->left == nullptr){
        in = curr;
        return;
    }

    //recursively call
    inorder(curr->left, in, curr);

}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int size) {
    // TODO: check for duplicate items in the input array

    // TODO: use the tree to sort the array items

    // TODO: overwrite input array values with sorted values
}