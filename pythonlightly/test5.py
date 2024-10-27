class AVLTreeElement:
    def __init__(self, key):
        self.key = key
        self.left_child = None
        self.right_child = None
        self.height = 1

class AVLTreeHandler:
    # Method to add a new element
    def add_element(self, node, key):
        if not node:
            return AVLTreeElement(key)

        if key < node.key:
            node.left_child = self.add_element(node.left_child, key)
        elif key > node.key:
            node.right_child = self.add_element(node.right_child, key)
        else:
            return node

        node.height = 1 + max(self.get_tree_height(node.left_child), self.get_tree_height(node.right_child))

        balance = self.calculate_balance(node)

        # Balancing the tree
        if balance > 1 and key < node.left_child.key:
            return self.rotate_right(node)

        if balance < -1 and key > node.right_child.key:
            return self.rotate_left(node)

        if balance > 1 and key > node.left_child.key:
            node.left_child = self.rotate_left(node.left_child)
            return self.rotate_right(node)

        if balance < -1 and key < node.right_child.key:
            node.right_child = self.rotate_right(node.right_child)
            return self.rotate_left(node)

        return node

    # Method to delete an element
    def delete_element(self, node, key):
        if not node:
            return node

        if key < node.key:
            node.left_child = self.delete_element(node.left_child, key)
        elif key > node.key:
            node.right_child = self.delete_element(node.right_child, key)
        else:
            if node.left_child is None:
                return node.right_child
            elif node.right_child is None:
                return node.left_child

            temp = self.get_min_node(node.right_child)
            node.key = temp.key
            node.right_child = self.delete_element(node.right_child, temp.key)

        if not node:
            return node

        node.height = 1 + max(self.get_tree_height(node.left_child), self.get_tree_height(node.right_child))

        balance = self.calculate_balance(node)

        if balance > 1 and self.calculate_balance(node.left_child) >= 0:
            return self.rotate_right(node)

        if balance < -1 and self.calculate_balance(node.right_child) <= 0:
            return self.rotate_left(node)

        if balance > 1 and self.calculate_balance(node.left_child) < 0:
            node.left_child = self.rotate_left(node.left_child)
            return self.rotate_right(node)

        if balance < -1 and self.calculate_balance(node.right_child) > 0:
            node.right_child = self.rotate_right(node.right_child)
            return self.rotate_left(node)

        return node

    # Helper functions
    def get_tree_height(self, node):
        if not node:
            return 0
        return node.height

    def calculate_balance(self, node):
        if not node:
            return 0
        return self.get_tree_height(node.left_child) - self.get_tree_height(node.right_child)

    def rotate_left(self, node):
        right_child = node.right_child
        temp = right_child.left_child
        right_child.left_child = node
        node.right_child = temp
        node.height = 1 + max(self.get_tree_height(node.left_child), self.get_tree_height(node.right_child))
        right_child.height = 1 + max(self.get_tree_height(right_child.left_child), self.get_tree_height(right_child.right_child))
        return right_child

    def rotate_right(self, node):
        left_child = node.left_child
        temp = left_child.right_child
        left_child.right_child = node
        node.left_child = temp
        node.height = 1 + max(self.get_tree_height(node.left_child), self.get_tree_height(node.right_child))
        left_child.height = 1 + max(self.get_tree_height(left_child.left_child), self.get_tree_height(left_child.right_child))
        return left_child

    def get_min_node(self, node):
        if node is None or node.left_child is None:
            return node
        return self.get_min_node(node.left_child)

# Example usage
avl_tree_handler = AVLTreeHandler()
root_node = None
keys_to_add = [20, 4, 15, 70, 50, 80, 90]

for key in keys_to_add:
    root_node = avl_tree_handler.add_element(root_node, key)
