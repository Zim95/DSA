'''
Time complexity

At iteration 1:
size of array = (n/2)

At iteration 2:
size of array = (n/2)/2 = (n/4)

At final iteration:
size of array = (n/2^k)
The size of array in the final iteration is 1, so
=> 1 = n/2^k
=> 2^k = n
Applying log base 2 on both sides
=> log2(2^k) = log2(n)
=> klog2(2) = log2(n)
=> k = log2(n)
'''

def binary_search(ar, key):
    offset = 0
    while ar:
        mid = len(ar)//2;
        if key == ar[mid]:
            return offset + mid
        elif key < ar[mid]:
            ar = ar[:mid]
        else:
            offset += mid + 1
            ar = ar[mid+1:]
    return -1


if __name__ == "__main__":
    print(binary_search([1, 2, 3, 4, 5, 6, 7, 8], 1))
    print(binary_search([1, 2, 3, 4, 5, 6, 7, 8], 2))
    print(binary_search([1, 2, 3, 4, 5, 6, 7, 8], 3))
    print(binary_search([1, 2, 3, 4, 5, 6, 7, 8], 4))
    print(binary_search([1, 2, 3, 4, 5, 6, 7, 8], 5))
    print(binary_search([1, 2, 3, 4, 5, 6, 7, 8], 6))
    print(binary_search([1, 2, 3, 4, 5, 6, 7, 8], 7))
    print(binary_search([1, 2, 3, 4, 5, 6, 7, 8], 8))
    print(binary_search([1, 2, 3, 4, 5, 7, 8], 7))
    print(binary_search([1, 2, 3, 4, 5, 7, 8], 9))
