/**
 *  Integer LIST ADT : basic test driver, useful for interactive testing during development
 *
 *  COMP220: Assignment 1
 *  Author:  Joseph Fall
 *  Date:    Jan. 8, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "intlist.h"



/*
 *  Basic, interactive test driver
 */
void main() {
   	IntList list = ilistNew();
   printf("Created a New list  Length is: %d\n", ilistLen(list));
   
   int i;
   
   for (i=0; i<30; i++) {
      ilistAppend(&list, i*11);
   }
   ilistPrint(list);
   printf("\n");
   
   ilistInsert(&list, 5, 42);
   printf("length list:%d\n", ilistLen(list));
   ilistPrint(list);
   printf("\n");
   

   ilistRemove(&list, 4);
   printf("length list:%d\n", ilistLen(list));
   ilistPrint(list);
   printf("\n");
  
   
   printf("Found 42 in list at? %d\n", ilistFind(list, 42));
   printf("Found 3 in list at? %d\n", ilistFind(list, 3));
   printf("Count of 42 in list? %d\n", ilistCount(list, 42));
   printf("Count of 3 in list? %d\n", ilistCount(list, 3));
   printf("Item at index 9? %d\n", ilistGet(list, 9));
   printf("Last item in list? %d\n", ilistGet(list, ilistLen(list)-1));  
   


   IntList list2 = ilistNew();
   for (i=0; i<20; i++) {
      ilistAppend(&list2, i*9);
   }
   ilistJoin(&list, list2);
   printf("Joined list: \n");
    printf("list 2 in regular order \n");
   ilistPrint(list);
    ilistPrint(list2);
   printf("\n");
   printf("Count total count of 99 in joined list? %d\n", ilistCount(list, 99));
 

   ilistReverse(&list2);
   printf("Reversed list 2: \n");
   ilistPrint(list2);
   printf("\n");
/*
   ilistDelete(&list);
   ilistDelete(&list2);
   ilistPrint(list);
   printf("\n");
*/
}
