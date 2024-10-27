class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left_child = None
        self.right_child = None
        self.node_height = 1

class BalancedTree:
    # Function to insert a node and maintain balance
    def add_node(self, current_root, value):
        if not current_root:
            return TreeNode(value)
        
        # Insert node based on comparison
        if value < current_root.value:
            current_root.left_child = self.add_node(current_root.left_child, value)
        elif value > current_root.value:
            current_root.right_child = self.add_node(current_root.right_child, value)
        else:
            # Optionally handle duplicates here
            return current_root
        
        # Update the height of the current root node
        current_root.node_height = 1 + max(self.compute_height(current_root.left_child), self.compute_height(current_root.right_child))

        # Calculate balance factor
        balance_factor = self.get_balance_factor(current_root)

        # Balance the tree if needed
        # Case 1: Left Left
        if balance_factor > 1 and value < current_root.left_child.value:
            return self.rotate_right(current_root)

        # Case 2: Right Right
        if balance_factor < -1 and value > current_root.right_child.value:
            return self.rotate_left(current_root)

        # Case 3: Left Right
        if balance_factor > 1 and value > current_root.left_child.value:
            current_root.left_child = self.rotate_left(current_root.left_child)
            return self.rotate_right(current_root)

        # Case 4: Right Left
        if balance_factor < -1 and value < current_root.right_child.value:
            current_root.right_child = self.rotate_right(current_root.right_child)
            return self.rotate_left(current_root)

        return current_root

    # Function to delete a node and rebalance if necessary
    def remove_node(self, current_root, value):
        if not current_root:
            return current_root

        # Basic BST delete operations
        if value < current_root.value:
            current_root.left_child = self.remove_node(current_root.left_child, value)
        elif value > current_root.value:
            current_root.right_child = self.remove_node(current_root.right_child, value)
        else:
            if current_root.left_child is None:
                return current_root.right_child
            elif current_root.right_child is None:
                return current_root.left_child
            
            # Get in-order successor
            temp_node = self.get_minimum_value_node(current_root.right_child)
            current_root.value = temp_node.value
            current_root.right_child = self.remove_node(current_root.right_child, temp_node.value)

        # Return if the tree had only one node
        if current_root is None:
            return current_root

        # Update height of the current node
        current_root.node_height = 1 + max(self.compute_height(current_root.left_child), self.compute_height(current_root.right_child))

        # Check balance factor
        balance_factor = self.get_balance_factor(current_root)

        # Balance the tree
        # Case 1: Left Left
        if balance_factor > 1 and self.get_balance_factor(current_root.left_child) >= 0:
            return self.rotate_right(current_root)

        # Case 2: Right Right
        if balance_factor < -1 and self.get_balance_factor(current_root.right_child) <= 0:
            return self.rotate_left(current_root)

        # Case 3: Left Right
        if balance_factor > 1 and self.get_balance_factor(current_root.left_child) < 0:
            current_root.left_child = self.rotate_left(current_root.left_child)
            return self.rotate_right(current_root)

        # Case 4: Right Left
        if balance_factor < -1 and self.get_balance_factor(current_root.right_child) > 0:
            current_root.right_child = self.rotate_right(current_root.right_child)
            return self.rotate_left(current_root)

        return current_root

    # Helper functions
    def compute_height(self, current_root):
        if not current_root:
            return 0
        return current_root.node_height

    def get_balance_factor(self, current_root):
        if not current_root:
            return 0
        return self.compute_height(current_root.left_child) - self.compute_height(current_root.right_child)

    def rotate_left(self, z_node):
        y_node = z_node.right_child
        T2 = y_node.left_child
        y_node.left_child = z_node
        z_node.right_child = T2
        z_node.node_height = 1 + max(self.compute_height(z_node.left_child), self.compute_height(z_node.right_child))
        y_node.node_height = 1 + max(self.compute_height(y_node.left_child), self.compute_height(y_node.right_child))
        return y_node

    def rotate_right(self, z_node):
        y_node = z_node.left_child
        T3 = y_node.right_child
        y_node.right_child = z_node
        z_node.left_child = T3
        z_node.node_height = 1 + max(self.compute_height(z_node.left_child), self.compute_height(z_node.right_child))
        y_node.node_height = 1 + max(self.compute_height(y_node.left_child), self.compute_height(y_node.right_child))
        return y_node

    def get_minimum_value_node(self, current_root):
        if current_root is None or current_root.left_child is None:
            return current_root
        return self.get_minimum_value_node(current_root.left_child)

# Example usage
balanced_tree = BalancedTree()
root = None
nodes = [20, 4, 15, 70, 50, 80, 90]

for node_value in nodes:
    root = balanced_tree.add_node(root, node_value)
