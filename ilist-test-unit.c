/**
 *  Integer LIST ADT : automatated unit test driver, your assignment will be graded by a similar unit test suite
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
* Run a single test case
* Report on failed test
* Return 0 if test successful, 1 otherwise
*/


/*You will need to make several minor changes to the unit test driver
(ilist-test-unit.c) where it does some "white-box" testing and actually inspects the
internal data structure (does an end-run around the API to test the inner-workings).
You can simply re-write or just remove the offending test cases.
int run_test(int result, int expected, char* msg) 
*/
/*
* Run a single test case
* Report on failed test
* Return 0 if test successful, 1 otherwise
*/

int run_test(int result, int expected, char* msg) 
{

   if (result != expected)
   {
      printf("\nTest failed: %s \n\tFunction returned %d but expected %d\n", msg, result, expected);
      return(1);
   }
   return(0);
}

/*
 * Run a series of unit tests cases.
 * Report on failed tests.
 */
void main()
{
   int i;
   int failed_test_counter = 0;
   printf("Unit Test Suite for IntList ADT operations...\n");
   
   // Test 1: Constructor
   IntList list = ilistNew();
   printf("1");
   failed_test_counter += run_test(ilistLen(list), 0, "Constructor fails to create empty list.");
   printf(".");
   
  
   // Test 2: Simple Append
   
   for (i=0; i<5; i++) {
      ilistAppend(&list, i*11);
   }
   printf("2");
   failed_test_counter += run_test(ilistLen(list), 5, "List length incorrect after Appending 5 items.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, 4), 44, "List tail Item does not match last item Appended.");
   printf(".");
   
   
   // Test 3: Simple Insert
   ilistInsert(&list, 2, 42);
   printf("3");
   failed_test_counter += run_test(ilistLen(list), 6, "List length incorrect after Inserting 6th item.");
   printf(".");
   
   failed_test_counter += run_test(ilistGet(list, 2), 42, "List Item at pos. 2 does not match item Inserted there.");
   printf(".");


   // Test 4: Simple Remove
   printf("4");
   ilistRemove(&list, 2);
   failed_test_counter += run_test(ilistLen(list), 5, "List length incorrect after Removing item.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, 2), 22, "List item at Remove location does not match following item.");
   printf(".");

/*
   // Test 5: Destructor (white-box tests)
   printf("5");
   ilistDelete(&list);
   failed_test_counter += run_test(ilistLen(list), 0, "Destructor fails to empty the list.");
   printf(".");
   //failed_test_counter += run_test(list.capacity, 0, "Destructor fails to set list capacity to zero.");
   //printf(".");
   //failed_test_counter += run_test((long int)list.data, (long int)NULL, "Destructor fails to set list data pointer to NULL.");
   printf(".");


   // Test 6: Append beyond capacity (white-box tests)
   ilistAppend(&list, 1);
   int new_size = list.capacity*3+2;
   for (i=1; i<new_size; i++) {
      ilistAppend(&list, i);
   }
   printf("6");
   failed_test_counter += run_test(ilistLen(list), new_size, "List length incorrect after Appending beyond its capacity.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, ilistLen(list)-1), new_size-1, "List tail Item does not match last item Appended.");
   printf(".");


   // Test 7: Insert beyond capacity (white-box tests)
   int new_capacity = list.capacity;
   while (ilistLen(list) < new_capacity+2) { 
      ilistInsert(&list, 2, 999);
   }
   printf("7");
   failed_test_counter += run_test(ilistLen(list), new_capacity+2, "List length incorrect after Inserting beyond its capacity.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, ilistLen(list)-1), new_size-1, "After Insert, List tail Item does not match last item Appended.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, 2), 999, "List Item does not match last item Inserted.");
   printf(".");
   
   */
   // Test 8: Find / Count operations
   
   ilistDelete(&list);

   int data[] = {24, 198, -9, 59, 9, 99, 33, 9, -9, 9, 987654, 222, 9, 123456, 33, 9, 9, 9, 18, 20};
   for (i=0; i<20; i++) {
      ilistAppend(&list, data[i]);
   }
   printf("8");
   failed_test_counter += run_test(ilistFind(list, 123456), 13, "Failed to find item in list that is there.");
   printf(".");
   failed_test_counter += run_test(ilistFind(list, 42), -1, "Found item in list that is not actually there.");
   printf(".");
   failed_test_counter += run_test(ilistCount(list, 987654), 1, "Failed to correctly count item that exists once in list.");
   printf(".");
   failed_test_counter += run_test(ilistCount(list, 9), 7, "Failed to correctly count item that exists multiple times in list.");
   printf(".");
   failed_test_counter += run_test(ilistCount(list, 42), 0, "Non-zero count for item that is not in list.");
   printf(".");
   

   // Test 9: Join 2 lists
   IntList list2 = ilistNew();
   int data2[] = {42, 891, 9, 95, -9, -99, -33, -9, 9, 19, 123456, -222, -9, 987654, -33, -9, -9, -9, 81, 2};
   for (i=0; i<20; i++) {
      ilistAppend(&list2, data2[i]);
   }
   ilistJoin(&list, list2);
   
   
   ilistDelete(&list2);  // wipe data in list 2
   for (i=0; i<20; i++) {
      ilistAppend(&list2, data2[i]);
   }
    
   printf("9");
  failed_test_counter += run_test(ilistLen(list), 40, "List length incorrect after Joining 2 lists.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, 0), 24, "List Item does not match last item Inserted.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, 19), 20, "List Item does not match last item Inserted.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, 20), 42, "List Item does not match last item Inserted.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, 39), 2, "After Join, List tail Item does not match last item Appended.");
   printf(".");


   // Test 10: Reverse list
   ilistDelete(&list);
   for (i=0; i<80; i++) {
      ilistAppend(&list, i);
   }
   ilistReverse(&list);
   printf("10");
   for (i=0; i<80; i++) {
      printf(".");
      failed_test_counter += run_test(ilistGet(list, i), 80-i-1, "After Reverse, list is not ordered correctly.");
   }   
   
   ilistDelete(&list);
   ilistPrint(list);
   printf("\n");
   
   printf("\n\nUnit Test Suite Complete: ");
   if (failed_test_counter == 0) printf("ALL TESTS PASSED\n");
   else printf("FAILED %d TESTS\n", failed_test_counter);
  
}
