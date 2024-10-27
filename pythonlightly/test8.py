class AVLTreeElement:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1

class AVLTreeHandler:
    # Method to insert a new node
    def insert(self, root, key):
        if not root:
            return AVLTreeElement(key)

        if key < root.key:
            root.left = self.insert(root.left, key)
        elif key > root.key:
            root.right = self.insert(root.right, key)
        else:
            return root

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        balance = self.get_balance(root)

        # Balancing the tree
        if balance > 1 and key < root.left.key:
            return self.rotate_right(root)

        if balance < -1 and key > root.right.key:
            return self.rotate_left(root)

        if balance > 1 and key > root.left.key:
            root.left = self.rotate_left(root.left)
            return self.rotate_right(root)

        if balance < -1 and key < root.right.key:
            root.right = self.rotate_right(root.right)
            return self.rotate_left(root)

        return root

    # Method to delete a node
    def delete(self, root, key):
        if not root:
            return root

        if key < root.key:
            root.left = self.delete(root.left, key)
        elif key > root.key:
            root.right = self.delete(root.right, key)
        else:
            if not root.left:
                return root.right
            elif not root.right:
                return root.left

            temp = self.get_min_value_node(root.right)
            root.key = temp.key
            root.right = self.delete(root.right, temp.key)

        if not root:
            return root

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        balance = self.get_balance(root)

        if balance > 1 and self.get_balance(root.left) >= 0:
            return self.rotate_right(root)

        if balance < -1 and self.get_balance(root.right) <= 0:
            return self.rotate_left(root)

        if balance > 1 and self.get_balance(root.left) < 0:
            root.left = self.rotate_left(root.left)
            return self.rotate_right(root)

        if balance < -1 and self.get_balance(root.right) > 0:
            root.right = self.rotate_right(root.right)
            return self.rotate_left(root)

        return root

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
avl_tree_handler = AVLTreeHandler()
root = None
values = [20, 4, 15, 70, 50, 80, 90]

for value in values:
    root = avl_tree_handler.insert(root, value)
