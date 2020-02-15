class ListNode:
    def traversal(self):
        print(self.val, end="")
        if self.next != None:
            print("->", end="")
            self.next.traversal()

    def __init__(self, x):
        self.val = x
        self.next = None

def build_list(L):
    root = ListNode(None)
    crt = root
    for l in L:
        crt.next = ListNode(l)
        crt = crt.next
    return root.next
