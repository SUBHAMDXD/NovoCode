from typing import Optional, List

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def modifiedList(self, nums: List[int], head: Optional[ListNode]) -> Optional[ListNode]:
        nums_set = set(nums)
        
        dummy = ListNode(0)
        dummy.next = head
        
        prev = dummy
        current = head
        
        while current:
            if current.val in nums_set:
                prev.next = current.next
            else:
                prev = current
            
            current = current.next
            
        return dummy.next