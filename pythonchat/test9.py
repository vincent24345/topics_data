class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1

class AVLTree9:
    def insert(self, root, key):
        if not root:
            return Node(key)
        if key < root.key:
            root.left = self.insert(root.left, key)
        elif key > root.key:
            root.right = self.insert(root.right, key)

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))
        return self.rebalance(root)

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

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))
        return self.rebalance(root)

    def rebalance(self, root):
        if not self.is_balanced(root):
            balance = self.get_balance(root)
            if balance > 1:
                if self.get_balance(root.left) >= 0:
                    return self.right_rotate(root)
                else:
                    root.left = self.left_rotate(root.left)
                    return self.right_rotate(root)
            if balance < -1:
                if self.get_balance(root.right) <= 0:
                    return self.left_rotate(root)
                else:
                    root.right = self.right_rotate(root.right)
                    return self.left_rotate(root)
        return root

    def is_balanced(self, root):
        return abs(self.get_balance(root)) <= 1

    def get_height(self, root):
        return 0 if not root else root.height

    def get_balance(self, root):
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
avl9 = AVLTree9()
root9 = None
keys9 = [5, 3, 7, 1, 9]
for key in keys9:
    root9 = avl9.insert(root9, key)
