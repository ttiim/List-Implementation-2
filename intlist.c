/* 
*   Capilano University
*   Comp 220- Professor Jospeph Fall
*   Authour: Tim Wriglesworth
*   Worked in collaboration with Charmaine Neufeld and Karan Nedungadi
*   Date:15.02.18
    Assignment 2 singly linked list   
*   Objectives:Objectives:
    • to re-implement the List ADT using a linked-list implementation;
    • to review common linked-list algorithms (link, unlink, traverse, etc.);
    • to deepen experience with dynamic memory management.
    
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h> 

#include "intlist.h"



/* 
* Programmer  Helper functions
*
*/

Node_t* nodeCreate(int value) ;
Node_t* findPriorNode(IntList* list, Node_t* cursor);
Node_t* listTraverse (IntList list, int place);

bool llIsEmpty(const IntList list);

void nodePrint(Node_t node) ;
void llInsertBefore(IntList* list,Node_t* cursor, int value);
void llInsertAfter( IntList* list, Node_t* cursor, int value);
void llLinkAfter(IntList* list, Node_t* cursor, Node_t* NewNode);
void llPush(IntList* list, int value);

int llPop(IntList* list);


/*
*
* Helper Functions
*
*/

/*
* initialize a node pointing to NULL 
*/

Node_t* nodeCreate(int value) 
{
    Node_t* node = malloc(sizeof(Node_t));
    node->data = value;
    node->next = NULL;
    return node;
}
/*
* print the actual node data value 
*/
void nodePrint(Node_t node) 
{
    printf("[%d]%s\n", node.data, node.next ? "-->" : "--|");
}



/*
* true/false list is empty
*/
bool llIsEmpty(const IntList list) 
{
   return list.head->next == NULL;
}

/*
*  return the node at the given index in the list
*/
Node_t* listTraverse (IntList list, int place)  //try without refernce
{
  assert(!llIsEmpty(list));
  int count =0;
  Node_t* cursor= list.head->next;
   
     while (place!=count)
	 {
		 cursor= cursor->next;
		 count++;
	  }
	  return cursor;
}

/*
*
* receives pointer to the given node and then inserts a node before it.
* 
*/
void llInsertBefore(IntList* list,Node_t* cursor, int value)
{
	Node_t* cursor2= findPriorNode(list, cursor);
	llInsertAfter(list, cursor2, value);
}

/*
*  receives pointer to the given node and then inserts a node after it. 
*/
void llInsertAfter( IntList* list, Node_t* cursor, int value)  
{
	Node_t* NewNode =nodeCreate(value);
	llLinkAfter(list,cursor,NewNode);	
}

/*
* link in after at specified node 
*/
void llLinkAfter(IntList* list, Node_t* cursor, Node_t* NewNode)
{
  NewNode->next = cursor->next;
  cursor->next = NewNode;
	
  if (cursor==list->tail)
  {
	  list->tail= NewNode;
	  }
}

/*
* given a node find the node that comes behind it  
*/
Node_t* findPriorNode(IntList* list, Node_t* cursor)
{
	Node_t* cursor2 = list->head;
	while (cursor2->next != cursor) 
	{
		cursor2 = cursor2->next;
	}
	return cursor2;
}

/*
* push a node at beginning of the list
*/
void llPush(IntList* list, int value) 
{
   Node_t* newNode = nodeCreate(value);
   if (llIsEmpty(*list))
   {
	   list->head->next= list->tail = newNode;
	   }
	else 
	{
		llInsertAfter(list,list->head,value);
		}
 
}

/*
* unlink the node after the given node 
*/
Node_t* llUnlinkAfter(IntList* list, Node_t* cursor)
{
	Node_t* unlink = cursor->next;
	
	if(unlink !=NULL)
	{
		cursor->next = unlink->next;
		unlink->next= NULL;
		}
		
		if (list->tail== unlink)
		{
			list->tail= cursor;
			}
			return unlink;
}


/*
* remove the given node in list
*/
int llPop(IntList* list) 
{
   assert(!llIsEmpty(*list));
   Node_t* node = list->head->next;
   list->head->next=node->next;
   
   if (list->tail == node) 
   {
	   list->tail = list->head;
	   }
	   int value = node->data;
	   free(node);
	   
	   return value; 
}




/*
*  List operations************************** 
*
*/


/*
 * Constructor - return a new, empty list 
 * POST:  ilistLen(list) == 0
 */
IntList ilistNew( )
{
   
   Node_t* dummy= nodeCreate(INT_MIN);
   IntList list= {dummy, dummy};
   return list;
}
 
 
 /*
 * Insert the given item into the list at the given location
 * POST: length of list is increased by one, and ilistGet( list, at ) == item
 */
void ilistInsert( IntList *list, int at, int item )
{
 llInsertBefore(list,listTraverse(*list,at), item);
  
}
	   
	
/*
 * Print a text representation of this list on STDOUT
 */
void ilistPrint( IntList list )
{
	
  Node_t* cur = list.head->next; 
  printf("\nList:\n  ");
  
  while (cur != NULL) 
  {
	  nodePrint(*cur);
      cur = cur->next;
	  }
	  
	  printf("\n\n");	
	
}
	

/*
 * Append the given item to the list 
 * POST: ilistGet( ilistLen(list)-1 ) == item
 */
void ilistAppend( IntList *list, int item )
{
 if (llIsEmpty(*list)) 
 {
	 llPush(list, item);
	 }
	 else 
	 {
		 llInsertAfter(list,list->tail,item);
		 }
}	
	
/*
 * Return the number of items in the list
 */
int ilistLen( IntList list )
{
  Node_t* cur = list.head->next;
  int len = 0;
  while (cur != NULL) 
  {
	  len++;
	  cur = cur->next;
	  }
	  
	  return len;
}
	


/*
 * Remove the given item at the given location from the  list 
 * POST: length of list is reduced by one, item at given location has been removed.
 */
void ilistRemove( IntList *list, int at )
{
	Node_t* cursor= listTraverse(*list,at);
    assert(cursor!=list->head);
	free(llUnlinkAfter(list,findPriorNode(list,cursor)));              
		
}


/*
 * Search the list for the given item
 * RETURN: the position, pos, such that ilistGet(list, pos)==item OR -1 if the item is not found
 */
int ilistFind( IntList list, int item )
{
	int count=0; 
   Node_t* cur = list.head->next;
   while (cur != NULL) 
   {
	   if (cur->data == item)
	   {
		   return count;
		   }
		   cur = cur->next;
		   count++;
		   }
		   
		   return -1;
}

	
	
	


/*
 * Return the number of times the given item occurs in the list 
 */
int ilistCount( IntList list, int item )
{
	int count=0; 
	Node_t* cur = list.head->next;
	
	while (cur != NULL) 
	{
		if (cur->data == item)
		{
			count++;
			} 
			cur = cur->next;
			}
			
			return count;
}


/*
 * Return the item at the given index from the list 
 * PRE: 0<=at && at<ilistLen(list)
 */
int ilistGet( IntList list, int at )
{
	Node_t* nodepointer = listTraverse (list,at);
	return nodepointer->data;  	
}
	
	
	
/*
 * Append all items from list2 to list1 
 * POST: length of list1 increased by size of list2 and all items from list2 are appended to list1.
 */
void ilistJoin( IntList *list1, IntList list2 )
{
	Node_t* cur = list2.head->next;
	while (cur!=NULL)
	{
		ilistAppend(list1, cur->data);
		cur=cur->next;
		}
	
}
	
	
	
/*
 * Reverse the order of items in the list
 * POST: items in the list are in reversed order (e.g., first item is now last and visa versa)
 */
void ilistReverse( IntList *list )          //  https:algorithms.tutorialhorizon.com/reverse-a-linked-list/ 
{
    Node_t* prevNode = NULL;
	Node_t* nextNode = NULL;
	Node_t* currNode= list->head->next;
	while (currNode!=NULL)
	{
		nextNode=currNode->next;
		currNode->next=prevNode;
		prevNode=currNode;
		currNode=nextNode;
		}
		list->head->next = prevNode;	
}
	



/*
 * Destructor - remove all data and free all memory associated with the list 
 * POST: ilistLen(list) == 0
 */
 void ilistDelete( IntList *list )
 {
	 while (list->head->next != NULL) 
	 {
		 llPop(list);
		 }
}


