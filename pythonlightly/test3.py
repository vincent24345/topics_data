class AVLTreeNode:
    def __init__(self, key_value):
        self.key_value = key_value
        self.left_child = None
        self.right_child = None
        self.tree_height = 1

class AVLTreeManager:
    # Function to insert a new key while maintaining tree balance
    def add_key(self, root_node, key_value):
        if not root_node:
            return AVLTreeNode(key_value)

        # Insert the key in the correct position
        if key_value < root_node.key_value:
            root_node.left_child = self.add_key(root_node.left_child, key_value)
        elif key_value > root_node.key_value:
            root_node.right_child = self.add_key(root_node.right_child, key_value)
        else:
            # Duplicates can be handled here if needed
            return root_node

        # Update the height of the current node
        root_node.tree_height = 1 + max(self.get_tree_height(root_node.left_child), self.get_tree_height(root_node.right_child))

        # Calculate balance factor
        balance_factor = self.calculate_balance(root_node)

        # Balance the tree if necessary
        # Case 1: Left Left
        if balance_factor > 1 and key_value < root_node.left_child.key_value:
            return self.rotate_right(root_node)

        # Case 2: Right Right
        if balance_factor < -1 and key_value > root_node.right_child.key_value:
            return self.rotate_left(root_node)

        # Case 3: Left Right
        if balance_factor > 1 and key_value > root_node.left_child.key_value:
            root_node.left_child = self.rotate_left(root_node.left_child)
            return self.rotate_right(root_node)

        # Case 4: Right Left
        if balance_factor < -1 and key_value < root_node.right_child.key_value:
            root_node.right_child = self.rotate_right(root_node.right_child)
            return self.rotate_left(root_node)

        return root_node

    # Function to delete a key and rebalance the tree
    def remove_key(self, root_node, key_value):
        if not root_node:
            return root_node

        # Standard deletion process for BST
        if key_value < root_node.key_value:
            root_node.left_child = self.remove_key(root_node.left_child, key_value)
        elif key_value > root_node.key_value:
            root_node.right_child = self.remove_key(root_node.right_child, key_value)
        else:
            if root_node.left_child is None:
                return root_node.right_child
            elif root_node.right_child is None:
                return root_node.left_child
            
            # In-order successor
            successor = self.get_min_node(root_node.right_child)
            root_node.key_value = successor.key_value
            root_node.right_child = self.remove_key(root_node.right_child, successor.key_value)

        # If the tree has no nodes
        if root_node is None:
            return root_node

        # Update the height of the current node
        root_node.tree_height = 1 + max(self.get_tree_height(root_node.left_child), self.get_tree_height(root_node.right_child))

        # Check balance factor
        balance_factor = self.calculate_balance(root_node)

        # Balance the tree
        # Case 1: Left Left
        if balance_factor > 1 and self.calculate_balance(root_node.left_child) >= 0:
            return self.rotate_right(root_node)

        # Case 2: Right Right
        if balance_factor < -1 and self.calculate_balance(root_node.right_child) <= 0:
            return self.rotate_left(root_node)

        # Case 3: Left Right
        if balance_factor > 1 and self.calculate_balance(root_node.left_child) < 0:
            root_node.left_child = self.rotate_left(root_node.left_child)
            return self.rotate_right(root_node)

        # Case 4: Right Left
        if balance_factor < -1 and self.calculate_balance(root_node.right_child) > 0:
            root_node.right_child = self.rotate_right(root_node.right_child)
            return self.rotate_left(root_node)

        return root_node

    # Helper methods
    def get_tree_height(self, root_node):
        if not root_node:
            return 0
        return root_node.tree_height

    def calculate_balance(self, root_node):
        if not root_node:
            return 0
        return self.get_tree_height(root_node.left_child) - self.get_tree_height(root_node.right_child)

    def rotate_left(self, node):
        right_child = node.right_child
        T2 = right_child.left_child
        right_child.left_child = node
        node.right_child = T2
        node.tree_height = 1 + max(self.get_tree_height(node.left_child), self.get_tree_height(node.right_child))
        right_child.tree_height = 1 + max(self.get_tree_height(right_child.left_child), self.get_tree_height(right_child.right_child))
        return right_child

    def rotate_right(self, node):
        left_child = node.left_child
        T3 = left_child.right_child
        left_child.right_child = node
        node.left_child = T3
        node.tree_height = 1 + max(self.get_tree_height(node.left_child), self.get_tree_height(node.right_child))
        left_child.tree_height = 1 + max(self.get_tree_height(left_child.left_child), self.get_tree_height(left_child.right_child))
        return left_child

    def get_min_node(self, root_node):
        if root_node is None or root_node.left_child is None:
            return root_node
        return self.get_min_node(root_node.left_child)

# Example usage
avl_tree_manager = AVLTreeManager()
root_node = None
key_values = [20, 4, 15, 70, 50, 80, 90]

for key in key_values:
    root_node = avl_tree_manager.add_key(root_node, key)
