# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
    def mergesort(self):
        s = Solution()
        s.sortList(self)
    def printf(self):
        p = self
        print('[', end = '')
        while p:
            print(p.val, end = ',' if p.next else '')
            p = p.next
        print(']')
class Solution:
    def sortList(self, head: ListNode) -> ListNode:
        h, length, unit = head, 0, 1
        while h:
            h, length = h.next, length + 1
        vhead = ListNode()
        vhead.next = head
        while unit < length:
            pre, h = vhead, vhead.next
            while h:
                h1, i = h, unit
                while h and i:
                    h, i = h.next, i - 1
                if i:
                    break
                h2, i = h, unit
                while h and i:
                    h, i = h.next, i - 1
                len1, len2 = unit, unit - i
                while len1 and len2:
                    if h1.val < h2.val:
                        pre.next, h1, len1 = h1, h1.next, len1 - 1
                    else:
                        pre.next, h2, len2 = h2, h2.next, len2 - 1
                    pre = pre.next
                pre.next, relen = h1 if len1 else h2, len1 or len2
                while relen:
                    pre, relen = pre.next, relen - 1
                pre.next = h
            unit *= 2
        return vhead.next
class test(object):
    """docstring for test"""
    def test(self):
        head = ListNode()
        tail = head
        for i in map(int, input().split()):
            p =  ListNode(i)
            tail.next = p
            tail = p
        head.printf()
        head.mergesort()
        head.printf()
if __name__ == '__main__':
    t = test()
    t.test()
        
