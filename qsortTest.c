/*
 *  qsortTest.c
 *
 * Time for BubbleSort:  2719985 microseconds
 * Time for QuickSort:   6127 microseconds
 *
 *  Created by Sally Goldin, 18 Jan 2012 for CPE113
 *  Modified by Vorapon Satittanapat (Mink) 55070503469
 *  Updated 28 January 2013
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timeFunctions.h"
#include "abstractHeap.h"


/* Note - removed maxsize argument from the functions below 
 * because not needed in this version.
 */
void sortArray(char *array[], int count);
int readArray(char *array[], int count, FILE* pFp);
void printArray(char *array[], int count);
unsigned long recordTime(int bStart);
/* writeArray still need maxsize because it needs to create a file with the
 * same format as the input file.
 */
void writeArray(char *array[],int count, int maxsize, char* outputFilename);
void freeData(char* data[], int count);

/*
 * Main function. 
 * Reads first line of file to control allocation.
 * Allocates array and reads from the file. Then sorts
 * the strings and writes them to another file.
 */
int main(int argc, char* argv[])
{
    char inputLine[128];  /* buffer for reading file data */
    char ** data = NULL;   /* This will become our array - an array of pointers to char arrays*/
    FILE* pInfile = NULL; /* File pointer for input file */
    int count = 0;        /* number of lines/names in file */
    int maxsize = 0;      /* Length of longest string */
    int i = 0;            /* loop counter */
    unsigned long interval = 0; /* measure time required to sort */
    /* Input and output filenames as specified by the user */
    char inputFile[128]; 
    char outputFile[128];

    /* check to make sure we have the right number of arguments */
    if (argc != 3)
       {
       fprintf(stdout,"Wrong number of arguments! Correct usage: \n");
       fprintf(stdout,"  ./newBubble [inputfilename] [outputfilename]\n");
       exit(1);
       }
    /* Copy files from argument array to local variables */
    strcpy(inputFile,argv[1]); 
    strcpy(outputFile,argv[2]);

    /* Try to open the input file */
    pInfile = fopen(inputFile,"r");
    /* Check that the open succeeded */
    if (pInfile == NULL)
       {
       fprintf(stderr,"Unable to open file '%s'\n",inputFile);
       exit(1);
       }
    /* Read the first line in the file so we know what to allocate */
    if (fgets(inputLine,sizeof(inputLine),pInfile) == NULL)
       {
       fprintf(stderr,"Input file seems to be empty\n");
       exit(2);
       }
    sscanf(inputLine,"%d %d",&count,&maxsize);
    if ((count == 0) || (maxsize == 0))
       {
       fprintf(stderr,"Input file does not have expected format\n");
       exit(3);
       }
    fprintf(stdout,"Input file %s contains %d items to sort\n",inputFile,count);
    /* If we get this far, we can do the allocation */
    data = (char **) calloc(count,sizeof(char*)); /* allocate an array of pointers */        
    if (data == NULL)
       {
       fprintf(stderr,"Memory allocation error\n");
       exit(4);
       }
    /* Read the data. This function returns 0 if an error occurs */    
    if (!readArray(data,count,pInfile))
       {
       fprintf(stderr,"Error reading information from file\n");
       fclose(pInfile);
       freeData(data,count);
       exit(5);
       }
    fclose(pInfile);
    /* Sort the array*/
    recordTime(1);
    sortArray(data,count);
    interval = recordTime(0);
    fprintf(stdout,
         "Sorting %d items required %ld microseconds\n",count,interval);
    fprintf(stdout,
	 "(%ld microseconds per item)\n",interval/count);
    /* Write the sorted array to a file */
    writeArray(data,count,maxsize,outputFile);
    freeData(data,count);
}


/* Free all the data we have allocated.
 * Arguments
 *    data   - dynamically allocated array of char * pointers
 *    count  - number of items in the array
 */
void freeData(char* data[], int count)
{
    /* we need to free the data stored in the array first,
     * since it was allocated separately. Then we
     * can free the array itself 
     */
    int i;
    for (i = 0; i < count; i++)
        {
        if (data[i] != NULL)
            free(data[i]);
        }
    free(data);
}

/*
 * Read the contents of the file into the array.
 * Each line is treated as a single item. 
 * Arguments
 *     array    - one dimensional array of chars, treated as 2D
 *     count    - number of expected lines
 *     pFp      - file pointer for open input file 
 * Returns 1 for success, 0 if some read error (e.g. not enough
 * lines in the file
 */
int readArray(char *array[], int count, FILE* pFp)
{
    char inputLine[128];  /* buffer for reading file data */
    int i;                /* loop counter */
    int bOk = 1;          /* return status */
    int len = 0;          /* for string length */ 
    char * newString = NULL; /* to hold strdup'ed strings */
    for (i = 0; i < count; i++)
      {
      if (fgets(inputLine,sizeof(inputLine),pFp) == NULL)
	 {
	 bOk = 0;  /* File does not have expected num of lines */
	 break;  
	 } 
      /* get rid of newline then store */
      len = strlen(inputLine);
      if (inputLine[len-1] == '\n')
	 inputLine[len-1] = '\0';
      newString = strdup(inputLine);
      if (newString == NULL)
         {
         bOk = 0;   /* allocation error */
	 } 
      else
         {  
         array[i] = newString;
         }  
      }
    return bOk;
}

int compare(void* itemA, void* itemB)
{
    if(itemA>itemB)
    return 1;
    if(itemA<itemB)
    return -1;
    else
    return 0;
}

/*
 * Sort the array 'array' into ascending
 * order using the qSort algorithm.
 * Arguments
 *     array    - one dimensional array of chars, treated as 2D
 *     count    - number of expected lines
 */
void sortArray qSort(char *array[], int count)
{
    int i;
    int swapCount = 1;
    initHeap(&compare, 0, count);

    while (swapCount > 0)
       {
       swapCount = 0;
       for (i = 0; i < count-1; i++)
           {
           heapInsert(array[i]);
	       }
       for (i = 0; i < count-1; i++)
           {
           array[i] = heapExtract();
	       }
       }
}


/*
 * Output the values stored in the array to a text file with
 * the same format as the input file
 * Arguments
 *     array    - one dimensional array of chars, treated as 2D
 *     count    - number of expected lines
 *     maxsize  - max length of each data item in chars
 *     outputFilenam - name of output file
 */
void writeArray(char *array[],int count, int maxSize, char* outputFilename)
{
    int i ;
    FILE* pOutfile = NULL;
    /* open output file */
    pOutfile = fopen(outputFilename,"w");
    if (pOutfile != NULL)
       { 
       fprintf(pOutfile,"%d %d\n", count,maxSize);
       for (i = 0; i < count; i++)
	  {
	  fprintf(pOutfile,"%s\n",array[i]);
          } 
       fclose(pOutfile); /* Very important to close output files */
       }
    else
       {
       fprintf(stderr,"Error - cannot open output file %s\n",outputFilename);
       }
}

/*
 * Print the values stored in the array to the screen
 * Arguments
 *     array    - one dimensional array of chars, treated as 2D
 *     count    - number of expected lines
 */
void printArray(char *array[],int count)
{
    int i ;
    fprintf(stdout,"Current contents of the array\n");
    for (i = 0; i < count; i++)
      {
      fprintf(stdout,"%s\n",array[i]);
      } 
}
