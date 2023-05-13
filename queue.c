/* 
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    //Initialize the q 
    queue_t *q =  malloc(sizeof(queue_t));    
    
    if(q == NULL) 
    { 
      return NULL;
    } 

    //Initialize the tail
    q->tail = NULL;// tail; 
  

    //Initialize the head 
    q->head = NULL;  

    //Initializing the size
    q->size = 0; 
    
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */  
    if(q == NULL) 
    { 
      return;
    } 
    if(q->size == 0) 
    { 
      free(q); 
      return;
    } 

    //Iterating through the q, freeing all the nodes
    list_ele_t* curNode = q -> head; 
    list_ele_t* tempNode;
    while(curNode) 
    { 
      tempNode = curNode->next;
      free(curNode->value);
      free(curNode);  
      curNode = tempNode;
    }  
  

     /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    //newh is the node we are inserting
    list_ele_t *newh;   
    if(q == NULL) 
    { 
      return false;
    }  
    //We need to copy s into another char and use that as the value we are inserting 
    //We use the copy and not the direct value bc if s changes later on, it won't break our program
    char* copyh = malloc((strlen(s)+1)); 
    if(copyh == NULL) 
    { 
      return false;
    }
    strcpy(copyh,s);
    newh = (list_ele_t*)malloc(sizeof(list_ele_t));  
    if(newh == NULL) 
    { 
      free(copyh);
      return false;
    } 

    /* What should you do if the q is NULL? */  
    //If q is empty, we need to set the head equal to newh directly 
    if(q->size == 0) 
    { 
      q -> head = newh;    
      q->head->value = copyh; 
      q->head -> next = NULL;  
      q->tail = newh; 
      q->size = q->size + 1; 
      return true;
    } 

    //We need to insert the head at the first node 
    //Set the value of the new node
    newh -> value = copyh;  
    //Change the new node's next to point to the head node of queue
    newh -> next = q ->head;   

    //Make the head pointer point to the new node
    q->head = newh; 
    
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
   
    q->size = q->size + 1;  
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
  
    list_ele_t *oldt;
    list_ele_t *newt;   
    if(q == NULL) 
    {    
      return false;
    }   

    char* copyt = malloc((strlen(s)+1));  
    if(copyt == NULL) 
    { 
      return false;
    }
    strcpy(copyt,s);   

    newt = (list_ele_t*)malloc(sizeof(list_ele_t));  
    if(newt == NULL) 
    { 
      free(copyt);
      return false;
    } 

    /* What should you do if the q is NULL? */  
    //If q is null, we need to set the tail equal to newt directly

    if(q->size == 0) 
    { 
      
      q -> tail = newt;  
      q->tail->value = copyt;
      q->tail -> next = NULL;   
      q->head = newt;
      q->size = q->size + 1; 
      return true;
    }
    //We need to insert the tail at the last node 
    //In order to make this O(1) time, I created a node pointer to the old tail 
    //And attached the new tail to the old tail
    oldt = q->tail; 
    newt -> value = copyt; 
    oldt->next = newt;    
    newt -> next = NULL; 
    
    q->tail = newt;  
    q->size = q->size + 1;  
    //free(copyt);
    return true;

}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */ 
    list_ele_t *tempNode;  
    //Check if argument is valid 
    
    if(bufsize == 0) 
    { 
      return false;
    }
    if(q == NULL)  
    { 
      return false;
    }  
    if(q->size == 0) 
    { 
      return false;
    }  
    if(q->head->value == NULL) 
    { 
      return false;
    }  
    /*if(q->head == NULL) 
    { 
      return false;
    }*/ 

    if(q->size == 1) 
    { 
      //Copying the value we are removing into sp 
      //The size of the string we are removing is bufsize -1, bc we need to make space to add on the null terminator
      strncpy(sp,q->head->value,bufsize - 1);  
      //sp[bufsize - 1] = '\0';  

      //Adding on the null terminator to the end of sp
      *(sp + bufsize - 1) = '\0';
      
      free(q->head->value);
      free(q->head);   
      q->head = NULL;
      q->size = 0;
      //Do we need to free the tail?? 
      return true;
    }

    strncpy(sp,q->head->value,bufsize - 1);    
    //sp[bufsize - 1] = '\0';  
    *(sp + bufsize - 1) = '\0'; 

    //Freeing the head data 
    //Making head point to head->next
    tempNode = q->head->next;  
    //printf("test1\n"); 
    free(q->head->value); 
    //printf("test2\n");
    free(q->head);    
    q->head = tempNode;   
    q->size = q->size - 1; 
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */ 

int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if(q == NULL) 
    { 
      return 0;
    } 
    if(q->size == 0) 
    { 
      return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
/*void q_reverse(queue_t *q)
{
  list_ele_t *curNode; 
  list_ele_t *tempNode;
  if(q->head == NULL) 
  { 
    return;
  }
  curNode = q->head->next; 
  while(curNode) 
  { 
    tempNode = curNode; 
    q_insert_head(q,curNode->value); 
    curNode = tempNode->next;  
    q->head->next = NULL;
  }
}*/  

//Used free pointer walk method
void q_reverse(queue_t *q)
{
  //prev,cur,after are the three pointers to use in the free pointer walk 
  list_ele_t *cur; 
  list_ele_t *prev; 
  list_ele_t *after;
  list_ele_t *temp;
  if(q == NULL) 
  { 
    return;
  }
  if(q->head == NULL) 
  { 
    return;
  } 
  if(q->size == 0) 
  { 
    return;
  } 
  if(q->size == 1) 
  { 
    return;
  } 
  if(q->size == 2) 
  {  
    temp = q->head;  
    q->head = q->tail;  
    q->tail = temp;  
    q->head->next = q->tail; 
    q->tail->next = NULL; 
    return;
  }
  //prev points to before the q initially
  prev = NULL;  
  //cur points to first node in q
  cur = q->head;  
  //after points to node after cur in q
  after = q->head->next;  

  //Execute the free pointer walk-continue to iterate through the q 
  //At each iteration, make cur next point to its previous node(prev) 
  //This moves the cur to be before the previous node 
  //Shift over all three pointers by 1 
  //Continue doing this until "after" points to memory after the q
  while(after != NULL) 
  { 
    cur->next = prev;   

    prev = cur; 
    cur = after;  
    after = cur->next;
  }   
  //Because we stop iterating as soon as after = NULL, we still have one iteration of assigning cur next left to do
  cur->next = prev; 

  //At this point, we have fixed all of the internal nodes. Now we simply switch the ends to finish reversing
  temp = q->head;  
  q->head = q->tail;
  q->tail = temp;   
  return;
} 


