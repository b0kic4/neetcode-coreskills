// left side nodes needs to be less then the root node
// right side nodes needs to be bigger then the root node

// in order
// post order
// pre order

// operations that needs to be implemented:
// 1. Search in BST
// 2. Insertion in BST
// 3. Deletion in BST

#include <stdio.h>
#include <stdlib.h>

struct BinarySearchTree {
  int val;
  struct BinarySearchTree *left, *right;
};

// BST initialize
struct BinarySearchTree *initBST(int val) {
  struct BinarySearchTree *newBinaryNode =
      (struct BinarySearchTree *)malloc(sizeof(struct BinarySearchTree));

  newBinaryNode->val = val;
  newBinaryNode->left = newBinaryNode->right = NULL;

  return newBinaryNode;
}

// insertion
//
// we have used recursion in here because when
// we have only one root we are setting it accordingly
// left or right;
// but when we nodes in bst we need to go to the end to the left and insert the
// node, or to the end to the right and insert the node

struct BinarySearchTree *insert(struct BinarySearchTree *node, int val) {
  if (node == NULL) {
    return initBST(val);
  }

  if (val < node->val) {
    return insert(node->left, val);
  }

  if (val > node->val) {
    return insert(node->right, val);
  }

  return node;
}

// search

struct BinarySearchTree *search(struct BinarySearchTree *node, int val) {

  if (node == NULL || node->val == val) {
    return node;
  }

  if (node->val > val) {
    return search(node->left, val);
  }

  return search(node->right, val);
}

struct BinarySearchTree *minValueNode(struct BinarySearchTree *node) {
  // This function finds the node with the smallest value in the subtree.
  // It's used to find the in-order successor when the node to be deleted
  // has two children.
  struct BinarySearchTree *current = node;
  while (current && current->left != NULL) {
    current = current->left; // Go to the leftmost node (smallest value).
  }
  return current;
}

struct BinarySearchTree *deletion(struct BinarySearchTree *node, int val) {
  if (node == NULL)
    return node; // If the tree is empty or node not found, return NULL.

  // Step 1: Recursively find the node to be deleted.
  if (val < node->val) {
    // If the value to delete is less than the current node's value,
    // move to the left subtree.
    node->left = deletion(node->left, val);
  } else if (val > node->val) {
    // If the value to delete is greater than the current node's value,
    // move to the right subtree.
    node->right = deletion(node->right, val);
  } else {
    // Step 2: Node to be deleted is found (val == node->val).

    // Case 1: Node has no children (it's a leaf node).
    if (node->left == NULL && node->right == NULL) {
      // Free the node and return NULL, as it has no children.
      free(node);
      return NULL;
    }

    // Case 2: Node has only one child.
    if (node->left == NULL) { // Node has only a right child.
      // Save the right child and free the node.
      struct BinarySearchTree *temp = node->right;
      free(node);  // Free the node to be deleted.
      return temp; // Return the right child to take the node's place.
    } else if (node->right == NULL) { // Node has only a left child.
      // Save the left child and free the node.
      struct BinarySearchTree *temp = node->left;
      free(node);  // Free the node to be deleted.
      return temp; // Return the left child to take the node's place.
    }

    // Case 3: Node has two children.
    // We need to find the in-order successor (smallest node in the right
    // subtree).
    struct BinarySearchTree *temp = minValueNode(node->right);

    // Step 3: Replace the current node's value with the in-order successor's
    // value.
    node->val = temp->val;

    // Step 4: Delete the in-order successor from the right subtree.
    node->right = deletion(node->right, temp->val);
  }

  // Return the current node after deletion and updates.
  return node;
}

void inorder(struct BinarySearchTree *root) {
  if (root != NULL) {
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
  }
}

int main() {
  struct BinarySearchTree *root = NULL;

  // Insert nodes into the BST
  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 20);
  root = insert(root, 40);
  root = insert(root, 70);
  root = insert(root, 60);
  root = insert(root, 80);

  // Display in-order traversal
  printf("In-order traversal of the given tree: ");
  inorder(root);
  printf("\n");

  // Test Case 1: Delete leaf node (no children)
  printf("Delete 20 (leaf node)\n");
  root = deletion(root, 20);
  printf("In-order traversal after deletion: ");
  inorder(root);
  printf("\n");

  // Test Case 2: Delete node with one child
  printf("Delete 30 (node with one child)\n");
  root = deletion(root, 30);
  printf("In-order traversal after deletion: ");
  inorder(root);
  printf("\n");

  // Test Case 3: Delete node with two children
  printf("Delete 50 (node with two children)\n");
  root = deletion(root, 50);
  printf("In-order traversal after deletion: ");
  inorder(root);
  printf("\n");

  // Test Case 4: Delete root node (remaining nodes)
  printf("Delete 60 (new root node)\n");
  root = deletion(root, 60);
  printf("In-order traversal after deletion: ");
  inorder(root);
  printf("\n");

  return 0;
}
