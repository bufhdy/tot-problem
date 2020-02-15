from tr import ListNode, build_list 

class Solution:
    def swap_nodes(self, n1: ListNode, n2: ListNode) -> ListNode:
        tmp = n2.next
        n2.next = n1
        n1.next = tmp
        return n2

    def swapPairs(self, head: ListNode) -> ListNode:
        root = ListNode(None)
        root.next = head
        crt = root
        while crt.next != None and crt.next.next != None:
            crt.next = self.swap_nodes(crt.next, crt.next.next)
            crt = crt.next.next
        return root.next

s = Solution()
L = [1, 2, 3, 4]
s.swapPairs(build_list(L)).traversal()

