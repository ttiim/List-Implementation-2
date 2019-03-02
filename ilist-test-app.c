/**
 *  Integer LIST ADT : a simple test application, to how a Int List ADT might be used in practice
 *
 *  COMP220: Assignment 1
 *  Author:  Joseph Fall
 *  Date:    Jan. 8, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "intlist.h"



FILE* openFileRead(char* filename);
int readInt(FILE* fp);

/*
 *  A simple list application:
 *     SCENARIO: Prof. Dee is the chair of the Mathematics dept. at WhoKnowsWhat University.
 *               Each term, the dept. runs multiple sections of their popular courses, 
 *                  and the course instructors each submit a file with the student grades from their section.
 *               Prof. Dee needs a program that can load data from all those files and compute some basic statistics across all sections.
 *
 *     INPUT: a set of N files containing final scores across all sections of a given course (integers between 0 - 100)
 *     OUTPUT: statistics from the overall grade set
 */
int main(int argc, char* argv[]) {
   if (argc < 2) {
      printf("Usage: stats file1 [file2 ...] \n");
      exit(EXIT_FAILURE);
   }
   
   // Load the grades from all files into a master list.
   IntList gradelist = ilistNew();
   int i;
   for (i=1; i<argc; i++) {
      FILE* fp = openFileRead(argv[i]);
      while (! feof(fp)) {
         ilistAppend(&gradelist, readInt(fp));
      }
   }
   
   // Calculate some basic grade statistics
   int sum = 0;
   int min = 100;
   int max = 0;
   int mode = 0;
   for (i=0; i<ilistLen( gradelist ); i++) {
      int item = ilistGet( gradelist, i);
      sum += item;
      if (item < min) min = item;
      if (item > max) max = item;
      if ( ilistCount( gradelist, item) > mode ) mode = item;
   }
   
   // Print out the grade stats
   printf("Stats for %d sections: ", argc-1);
   for (i=1; i<argc; i++) {
      char* sep = i<argc-1 ? ", ":"";
      printf("%s%s",argv[i], sep);
   }
   printf("\n");
   printf("Total number of students: %d\n", ilistLen( gradelist ));
   printf("Grades: \n");
   printf("    Minumum: %d \n", min);
   printf("    Average: %.2f\n", (double) sum / ilistLen( gradelist ) );
   printf("    Mode   : %d \n", mode );
   printf("    Maximum: %d \n", max);
}

/*
 * Attempt to read / return an integer from an open file pointer, fp
 * May not return a valid value if eof is read, i.e., feof(fp)
 */
int readInt(FILE* fp) {
    int i;
    fscanf(fp, "%d", &i);
    return i;
}  

/*
 * Attempt to open the file for read access.
 * Peforms error check and exits if file is not accessible
 */
FILE* openFileRead(char* filename)
{
   FILE* inFile = fopen(filename, "r" );
   if( inFile == NULL) {
      printf( "Error opening input file %s, program terminating!\n", filename);
      exit(EXIT_FAILURE);
   }
   return inFile;
}
