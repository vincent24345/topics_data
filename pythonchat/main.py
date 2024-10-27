class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1

class AVLTree:
    # Insert function with rebalancing
    def insert(self, root, key):
        if not root:
            return Node(key)
        
        # Insert the node
        if key < root.key:
            root.left = self.insert(root.left, key)
        elif key > root.key:
            root.right = self.insert(root.right, key)
        else:
            # Handle duplicates (optional)
            return root
        
        # Update the height of the ancestor node
        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        # Get the balance factor
        balance = self.get_balance(root)

        # Rotate based on balance factor
        # Left Left Case
        if balance > 1 and key < root.left.key:
            return self.right_rotate(root)

        # Right Right Case
        if balance < -1 and key > root.right.key:
            return self.left_rotate(root)

        # Left Right Case
        if balance > 1 and key > root.left.key:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)

        # Right Left Case
        if balance < -1 and key < root.right.key:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        return root

    # Delete function with rebalancing
    def delete(self, root, key):
        if not root:
            return root

        # Standard BST delete
        if key < root.key:
            root.left = self.delete(root.left, key)
        elif key > root.key:
            root.right = self.delete(root.right, key)
        else:
            if root.left is None:
                return root.right
            elif root.right is None:
                return root.left
            
            # Node with two children, get the in-order successor
            temp = self.get_min_value_node(root.right)
            root.key = temp.key
            root.right = self.delete(root.right, temp.key)

        # If the tree has only one node, return
        if root is None:
            return root

        # Update the height of the current node
        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        # Get the balance factor
        balance = self.get_balance(root)

        # Rotate based on balance factor
        # Left Left Case
        if balance > 1 and self.get_balance(root.left) >= 0:
            return self.right_rotate(root)

        # Right Right Case
        if balance < -1 and self.get_balance(root.right) <= 0:
            return self.left_rotate(root)

        # Left Right Case
        if balance > 1 and self.get_balance(root.left) < 0:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)

        # Right Left Case
        if balance < -1 and self.get_balance(root.right) > 0:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        return root

    # Utility functions
    def get_height(self, root):
        if not root:
            return 0
        return root.height

    def get_balance(self, root):
        if not root:
            return 0
        return self.get_height(root.left) - self.get_height(root.right)

    def left_rotate(self, z):
        y = z.right
        T2 = y.left
        y.left = z
        z.right = T2
        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        return y

    def right_rotate(self, z):
        y = z.left
        T3 = y.right
        y.right = z
        z.left = T3
        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        return y

    def get_min_value_node(self, root):
        if root is None or root.left is None:
            return root
        return self.get_min_value_node(root.left)

# Example usage
avl = AVLTree()
root = None
keys = [20, 4, 15, 70, 50, 80, 90]

for key in keys:
    root = avl.insert(root, key)
