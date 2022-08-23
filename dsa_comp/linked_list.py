class Node:

    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:

    def __init__(self):
        self.head = None
    
    def append(self, data):
        node = Node(data)
        if self.head is None:
            self.head = node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = node
    
    def reverse(self):
        prev = None
        curr = self.head
        nxt = curr.next
        '''
        Iteration 1:
        -------------
        p:None <- c:a -> n:b -> c -> d -> None
        None <- p:a -> c:b -> n:c -> d -> None

        Iteration 2:
        -------------
        None <- p:a <- c:b -> n:c -> d -> None
        None <- a <- p:b -> c:c -> n:d -> None

        Iteration 3:
        -------------
        None <- a <- p:b <- c:c -> n:d -> None
        None <- a <- b <- p:c -> c:d -> n:None

        Finally:
        --------
        None <- a <- b <- p:c <- c:d(head) 
        '''
        iterate = True
        while curr.next:
            curr.next = prev
            prev = curr
            curr = nxt
            nxt = curr.next
        curr.next = prev
        self.head = curr

    def reverse_recursive(self, prev=None, curr=None):
        if curr and not curr.next:
            curr.next = prev
            self.head = curr
            return

        if not curr:
            curr = self.head

        nxt = curr.next
        curr.next = prev
        prev = curr
        curr = nxt
        nxt = curr.next
        self.reverse_recursive(prev, curr)

    def detect_loop(self):
        # s = set()
        # curr = self.head
        # while curr.next:
        #     if curr.data in s:
        #         return True
        #     s.add(curr.data)
        #     curr = curr.next
        # return False
        hare = self.head
        turtle = self.head
        while turtle and hare:
            turtle = turtle.next
            hare = hare.next
            if hare:
                hare = hare.next
            if turtle == hare:
                return True
        return False

    def remove_loop(self):
        s = set()
        curr = self.head
        while curr:
            if curr.next.data in s:
                curr.next = None
            s.add(curr.data)
            curr = curr.next

    def remove_duplicate(self):
        # this approach gives us TLE:
        # we need to first sort this linked list then appraoch
        # we have another question for sorting
        s = set()
        prev = None
        curr = self.head
        while curr:
            if curr.data in s:
                curr = curr.next
                prev.next = curr
            else:
                s.add(curr.data)
                prev = curr
                curr = curr.next

    def right_shift(self):
        prev = None
        curr = self.head
        while curr.next:
            prev = curr
            curr = curr.next
        curr.next = self.head
        prev.next = None
        self.head = curr

    def add_one(self):
        '''
        3->6->9
        If we add 1 to the last node
        we get:
        3->6->10
        We need to get 3->7->0

        Edge case:
        9->9->9
        1->0->0->0
        '''
        def _add_one(node):
            if not node.next:
                node.data += 1
                if node.data == 10:
                    node.data = 0
                    return 1
                return 0
            carry = _add_one(node.next)
            node.data += carry
            if node.data == 10:
                node.data = 0
                return 1
            return 0
        
        curr = self.head
        carry = _add_one(curr)
        if carry:
            node = Node(1)
            node.next = self.head
            self.head = node

    def print_list(self):
        current = self.head
        while current:
            print(current.data, "->", end=" ")
            current = current.next
        print("\n")

def reverse_upto_k(k, head):
    if k == 1:
        return head
    prev = None
    curr = head
    nxt = curr.next

    while curr.next and k>1:
        curr.next = prev
        prev = curr
        curr = nxt
        nxt = curr.next
        k = k - 1
    curr.next = prev
    head = curr
    if not nxt:
        return head
    head_second = curr.next
    nxt_curr = head
    while nxt_curr.next:
        nxt_curr = nxt_curr.next
    nxt_curr.next = reverse_upto_k(k, head_second)
    return head

if __name__ == "__main__":
    linked_list = LinkedList()
    linked_list.append(5)
    linked_list.append(2)
    linked_list.append(1)
    linked_list.append(0)
    linked_list.append(3)
    print('Original list')
    linked_list.print_list()
    linked_list.reverse()
    print('After normal reverse')
    linked_list.print_list()
    linked_list.reverse_recursive()
    print('After recursive reverse')
    linked_list.print_list()
    list_head = reverse_upto_k(2, linked_list.head)
    print('just did partial reverse. The function doesnt affect the list')
    linked_list.print_list()
    # creating a loop in the list for test
    linked_list.head.next.next.next.next.next = linked_list.head
    print('Loop created. Loop detected: {}'.format(
        linked_list.detect_loop()
    ))
    linked_list.remove_loop()
    print('Removed loop. New linked list')
    linked_list.print_list()
    print('Loop detected: {}'.format(linked_list.detect_loop()))
    linked_list.append(5)
    linked_list.append(3)
    print('Added duplicate')
    linked_list.print_list()
    print('Removed duplicate')
    linked_list.remove_duplicate()
    linked_list.print_list()
    linked_list.right_shift()
    print('Right shift')
    linked_list.print_list()
    linked_list.add_one()
    print('Added one')
    linked_list.print_list()
