//Initial Template for C++

// C program to find n'th Node in linked list
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

/* Link list Node */
struct Node {
    int data;
    struct Node *next;
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};



 // } Driver Code Ends
/* Linked List Node structure:

struct Node
{
    int data;
    struct Node *next;
}

*/

class Solution{
    public:
    struct Node* reverseList(struct Node *head) {
        Node *prev = NULL;
        Node *curr = head;
        Node *next = head->next;
        
        /*
          p:null -> c:a -> n:b -> c -> d -> e -> null
          
          iteration1:
          -----------
          p:null <- c:a -> n:b -> c -> d -> e -> null
          null <- p:a -> c:b -> n:c -> d -> e -> null
          
          iteration2:
          -----------
          null <- p:a <- c:b -> n:c -> d -> e -> null
          null <- a <- p:b -> c:c -> n:d -> e -> null
          
          iteration3:
          -----------
          null <- a <- p:b <- c:c -> n:d -> e -> null
          null <- a <- b <- p:c -> c:d -> n:e -> null
          
          iteration4:
          -----------
          null <- a <- b <- p:c <- c:d -> n:e -> null
          null <- a <- b <- c <- p:d -> c:e -> n:null
          
          iteration5:
          -----------
          null <- a <- b <- c <- p:d <- c:e -> n:null
          null <- a <- b <- c <- d <- p:e -> c:null
        */
        while(curr != NULL) {
            curr->next = prev;
            prev = curr;
            curr = next;
            if(curr != NULL) {
                next = curr->next;
            } else {
                head = prev;
            }
        }
        
        return head;
        // code here
        // return head of reversed list
    }
    
};
    


// { Driver Code Starts.

void printList(struct Node *head)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
       printf("%d ", temp->data);
       temp  = temp->next;
    }
}

/* Driver program to test above function*/
int main()
{
    int T,n,l,firstdata;
    cin>>T;

    while(T--)
    {
        struct Node *head = NULL,  *tail = NULL;

        cin>>n;
        
        cin>>firstdata;
        head = new Node(firstdata);
        tail = head;
        
        for (int i=1; i<n; i++)
        {
            cin>>l;
            tail->next = new Node(l);
            tail = tail->next;
        }
        
        Solution ob;
        head = ob. reverseList(head);
        
        printList(head);
        cout << endl;
    }
    return 0;
}

  // } Driver Code Ends