# Tree Traversal Techniques

<img src="https://media.geeksforgeeks.org/wp-content/uploads/20230531175409/tree-traversal.webp" alt= “Hello” width="512" height="256">

A Tree Data Structure can be traversed in following ways:
1. Depth First Search or DFS
   - Inorder Traversal `(left -> root -> right)`
   - Preorder Traversal `(root -> left -> right)`
   - Postorder Traversal `(left -> right -> root)`
2. Level Order Traversal or Breadth First Search or BFS
3. Boundary Traversal
4. Diagonal Traversal

# Inorder Traversal: O(N)
Algorithm Inorder (tree)
1. Traverse the left subtree, i.e., call `Inorder(left->subtree)`
2. Visit the root
3. Traverse the right subtree, i.e., call `Inorder(right->subtree)`

# Preorder Traversal: O(N)
Algorithm Preorder(tree)
1. Visit the root
2. Traverse the left subtree, i.e., call `Preorder(left->subtree)`
3. Traverse the right subtree, i.e., call `Preorder(right->subtree)` 

# Postorder Traversal: O(N)
Algorithm Postorder(tree)
1. Traverse the left subtree, i.e., call `Postorder(left->subtree)`
2. Traverse the right subtree, i.e., call `Postorder(right->subtree)`
3. Visit the root
