class AVLTreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.height = 1

class AVLTreeManager:
    # Method to insert a new node
    def insert(self, node, value):
        if not node:
            return AVLTreeNode(value)

        if value < node.value:
            node.left = self.insert(node.left, value)
        elif value > node.value:
            node.right = self.insert(node.right, value)
        else:
            return node

        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))

        balance = self.get_balance(node)

        # Balancing the tree
        if balance > 1 and value < node.left.value:
            return self.rotate_right(node)

        if balance < -1 and value > node.right.value:
            return self.rotate_left(node)

        if balance > 1 and value > node.left.value:
            node.left = self.rotate_left(node.left)
            return self.rotate_right(node)

        if balance < -1 and value < node.right.value:
            node.right = self.rotate_right(node.right)
            return self.rotate_left(node)

        return node

    # Method to remove a node
    def remove(self, node, value):
        if not node:
            return node

        if value < node.value:
            node.left = self.remove(node.left, value)
        elif value > node.value:
            node.right = self.remove(node.right, value)
        else:
            if not node.left:
                return node.right
            elif not node.right:
                return node.left

            temp = self.get_min_value_node(node.right)
            node.value = temp.value
            node.right = self.remove(node.right, temp.value)

        if not node:
            return node

        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))

        balance = self.get_balance(node)

        if balance > 1 and self.get_balance(node.left) >= 0:
            return self.rotate_right(node)

        if balance < -1 and self.get_balance(node.right) <= 0:
            return self.rotate_left(node)

        if balance > 1 and self.get_balance(node.left) < 0:
            node.left = self.rotate_left(node.left)
            return self.rotate_right(node)

        if balance < -1 and self.get_balance(node.right) > 0:
            node.right = self.rotate_right(node.right)
            return self.rotate_left(node)

        return node

    # Helper methods
    def get_height(self, node):
        if not node:
            return 0
        return node.height

    def get_balance(self, node):
        if not node:
            return 0
        return self.get_height(node.left) - self.get_height(node.right)

    def rotate_left(self, node):
        right_child = node.right
        temp = right_child.left
        right_child.left = node
        node.right = temp
        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))
        right_child.height = 1 + max(self.get_height(right_child.left), self.get_height(right_child.right))
        return right_child

    def rotate_right(self, node):
        left_child = node.left
        temp = left_child.right
        left_child.right = node
        node.left = temp
        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))
        left_child.height = 1 + max(self.get_height(left_child.left), self.get_height(left_child.right))
        return left_child

    def get_min_value_node(self, node):
        if node is None or node.left is None:
            return node
        return self.get_min_value_node(node.left)

# Example usage
avl_tree_manager = AVLTreeManager()
root_node = None
values = [20, 4, 15, 70, 50, 80, 90]

for value in values:
    root_node = avl_tree_manager.insert(root_node, value)
