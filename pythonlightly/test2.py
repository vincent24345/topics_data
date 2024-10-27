class AVLNode:
    def __init__(self, data):
        self.data = data
        self.left_child = None
        self.right_child = None
        self.tree_height = 1

class AVLTreeStructure:
    # Method to insert a value while keeping the tree balanced
    def insert_value(self, current_node, data):
        if not current_node:
            return AVLNode(data)

        # Place the new node in the correct position
        if data < current_node.data:
            current_node.left_child = self.insert_value(current_node.left_child, data)
        elif data > current_node.data:
            current_node.right_child = self.insert_value(current_node.right_child, data)
        else:
            # Optionally handle duplicates here
            return current_node

        # Update the height of the current node
        current_node.tree_height = 1 + max(self.get_node_height(current_node.left_child), self.get_node_height(current_node.right_child))

        # Calculate balance factor
        balance_factor = self.check_balance(current_node)

        # Balance the tree if needed
        # Case 1: Left Left
        if balance_factor > 1 and data < current_node.left_child.data:
            return self.perform_right_rotation(current_node)

        # Case 2: Right Right
        if balance_factor < -1 and data > current_node.right_child.data:
            return self.perform_left_rotation(current_node)

        # Case 3: Left Right
        if balance_factor > 1 and data > current_node.left_child.data:
            current_node.left_child = self.perform_left_rotation(current_node.left_child)
            return self.perform_right_rotation(current_node)

        # Case 4: Right Left
        if balance_factor < -1 and data < current_node.right_child.data:
            current_node.right_child = self.perform_right_rotation(current_node.right_child)
            return self.perform_left_rotation(current_node)

        return current_node

    # Method to delete a node while rebalancing the tree
    def remove_value(self, current_node, data):
        if not current_node:
            return current_node

        # Standard BST deletion process
        if data < current_node.data:
            current_node.left_child = self.remove_value(current_node.left_child, data)
        elif data > current_node.data:
            current_node.right_child = self.remove_value(current_node.right_child, data)
        else:
            if current_node.left_child is None:
                return current_node.right_child
            elif current_node.right_child is None:
                return current_node.left_child
            
            # Get in-order successor
            successor = self.find_minimum(current_node.right_child)
            current_node.data = successor.data
            current_node.right_child = self.remove_value(current_node.right_child, successor.data)

        # Return if the tree has no nodes
        if current_node is None:
            return current_node

        # Update the height of the current node
        current_node.tree_height = 1 + max(self.get_node_height(current_node.left_child), self.get_node_height(current_node.right_child))

        # Get balance factor
        balance_factor = self.check_balance(current_node)

        # Balance the tree
        # Case 1: Left Left
        if balance_factor > 1 and self.check_balance(current_node.left_child) >= 0:
            return self.perform_right_rotation(current_node)

        # Case 2: Right Right
        if balance_factor < -1 and self.check_balance(current_node.right_child) <= 0:
            return self.perform_left_rotation(current_node)

        # Case 3: Left Right
        if balance_factor > 1 and self.check_balance(current_node.left_child) < 0:
            current_node.left_child = self.perform_left_rotation(current_node.left_child)
            return self.perform_right_rotation(current_node)

        # Case 4: Right Left
        if balance_factor < -1 and self.check_balance(current_node.right_child) > 0:
            current_node.right_child = self.perform_right_rotation(current_node.right_child)
            return self.perform_left_rotation(current_node)

        return current_node

    # Helper methods
    def get_node_height(self, current_node):
        if not current_node:
            return 0
        return current_node.tree_height

    def check_balance(self, current_node):
        if not current_node:
            return 0
        return self.get_node_height(current_node.left_child) - self.get_node_height(current_node.right_child)

    def perform_left_rotation(self, node):
        right_child = node.right_child
        T2 = right_child.left_child
        right_child.left_child = node
        node.right_child = T2
        node.tree_height = 1 + max(self.get_node_height(node.left_child), self.get_node_height(node.right_child))
        right_child.tree_height = 1 + max(self.get_node_height(right_child.left_child), self.get_node_height(right_child.right_child))
        return right_child

    def perform_right_rotation(self, node):
        left_child = node.left_child
        T3 = left_child.right_child
        left_child.right_child = node
        node.left_child = T3
        node.tree_height = 1 + max(self.get_node_height(node.left_child), self.get_node_height(node.right_child))
        left_child.tree_height = 1 + max(self.get_node_height(left_child.left_child), self.get_node_height(left_child.right_child))
        return left_child

    def find_minimum(self, current_node):
        if current_node is None or current_node.left_child is None:
            return current_node
        return self.find_minimum(current_node.left_child)

# Example usage
avl_tree = AVLTreeStructure()
root_node = None
values = [20, 4, 15, 70, 50, 80, 90]

for value in values:
    root_node = avl_tree.insert_value(root_node, value)
