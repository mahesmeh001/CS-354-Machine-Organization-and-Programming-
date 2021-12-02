/******************************************************************************
 * @file: latin_square_functions.c
 *
 * WISC NETID Mehul Maheshwari
 * CANVAS USERNAME mmaheshwari2
 * WISC ID NUMBER 9082250664
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: YOUR PREFERED NAME (YOUR WISC EMAIL)
 * @modified: SUBMISSION DATE
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgprint_latin_square(n, LS) if (DEBUG) { Print_Latin_Square(n, LS); }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE 

/******************************************************************************
 * Globals
 *****************************************************************************/
extern void Print_Latin_Square(const size_t n, char **latin_square);

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename, 
                            char ***latin_square_in, 
                            size_t *n) {
    /* BEGIN MODIFYING CODE HERE */

    //open up file to be able to work with it
    FILE *fp = fopen(filename,"r");
    if(fp==NULL) printf("Something went wrong\n");


    //malloc up space
    //int *rows = malloc(1000*sizeof(char ));

    //read in text from file
    char *buf = malloc(sizeof (char )* 1000000);

    size_t elemSize = (size_t) fread(buf, sizeof(char), 1000000, fp);

    //take square root of elemSize to find size of n
    int i = 1;
    int sq = 1;
    while(sq<=elemSize){
        i++;
        sq = i*i;
    }
    *n = i-1;

    //check print statement
    //`printf("%zu\n",*n);

   //close and reopen to go back to the beginning of the file
   fclose(fp);
   fp = fopen(filename,"r");
   if(fp==NULL) printf("Something went wrong\n");


    // 4a) reserve an array of pointers to the rows
    char **rows = malloc((*n) * sizeof (char *));

    //   4b) reserve an array of characters for each row
    for(int x = 0; x<(*n); x++) {
        *(rows+x) = malloc((*n) * sizeof(char));
    }

//    //set rows and elements to null
//    for(int i = 0; i<(*n);i++){
//        **rows='\0';
//    }

    //   5) fill in the latin_square data structure

    //iterate e (rows)
    for(int e = 0; e<(*n); e++){
        //iterate j (elements)
        for(int j = 0; j<(*n)+1; j++){
            char c = (char) fgetc(fp);
            if(c == '\n'){
                break;
            } else {
                *(*(rows+e)+j) = c;
            }
        }
    }
            *latin_square_in = rows;


//    6) close the file
    fclose(fp);
    free(buf);
    /* END MODIFYING CODE HERE */
}

/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square) {
    if (latin_square == NULL) {
        printf("Verify_Alphabet - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */

    //create parallel arrays which will hold both unique elements and their occurrences
    //char elements[1000];
    char *elements = (char *)calloc(n,sizeof(char));
    //int occurrences[1000];
    char *occurrences = (char *)calloc(n,sizeof(char));

    //initialize occurrences array to all 0's
//    for(int k = 0; k<1000;k++){
//        *(occurrences+k)=0;
//    }
    //initialize elements array to all null's
//    for(int z =0 ; z<1000; z++){
//        *(elements+z)='\0';
//    }
    //iterate through the latin square
    for(int i = 0; i<n; i ++) {
        for(int e = 0; e<n;e++){
            //change number of *'s?
            char current = *(*(latin_square+e)+i);
            //check whether the current element is already in the array

            //special case: there are no elements in the array
            if (*elements=='\0'){
                    *elements=current;
                    *occurrences=1;
            }
            //if there is a match, add at the same index it was matched into the count parallel array
            else {
                int match = 0;
                for(int x = 0; x<1000;x++){
                    if(*(elements+x)=='\0'){
                        break;
                    }
                    if(current==(*(elements+x))){
                        (*(occurrences+x))++;
                        match=1;
                    }
                }
                //if not, add to the next open index on the array
                if(match!=1){
                    int openIndex = 0;
                    while((*(elements+openIndex))){
                        openIndex++;
                    }
                    (*(elements+openIndex))=current;
                    (*(occurrences+openIndex))++;
                }
            }

        }

    }





    //create a variable to store the size of the elements
    size_t elemSize = 0;
    while(*(elements+elemSize)!='\0'){
        elemSize++;
    }

    //check at the end the size of both arrays, and whether they both equal n
    if(elemSize!=n){
        //printf("Elements size did not equal n\n");
        free(elements);
        free(occurrences);
        return 0;
    }

    //check if the actual counts of each equal n
    for(int y = 0; y<elemSize;y++){
        if((*(occurrences+y)) != (int) n){
            //printf("occurrences of number at index %d was not right.\n",(y+1));
            free(elements);
            free(occurrences);
            return 0;
        }
    }

    free(elements);
    free(occurrences);
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 * 
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
 int Verify_Rows_and_Columns(const size_t n, char **latin_square){
    if (latin_square == NULL) {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
    // printf("Error in row %d\n", i);


    //create array to hold values from the row
    char *Relements=malloc(sizeof (char)*n);

    //iterate through the 2d array
    for(int i = 0; i<n; i++){
        //initialize array to null
//        for(int z = 0 ; z<n; z++){
//            *(Relements+z)='\0';
//        }
        //input row elements into array
        for(int e = 0; e<n; e++){
            *(Relements+e)=*((*(latin_square+i))+e);
        }
        //check for duplicates in the array
        for(int x = 0; x<n;x++){
            for(int y = x+1;y<n;y++){
                if(*(Relements+x)==*(Relements+y)){
                    printf("Error in row %d\n", i);
                    goto label;
                }
            }
        }
    }



    label:;
    free(Relements);
    //repeat process for columns
    //create array to hold values from the row
    char *cElements=malloc(sizeof (char)*n);
    //iterate through the 2d array
    for(int i = 0; i<n; i++){

        //initialize array to null
//        for(int z =0 ; z<n; z++){
//            *(cElements+z)='\0';
//        }
        //input column elements into array
        for(int e = 0; e<n; e++){
            *(cElements+e)=*(*(latin_square+e)+i);
        }
        //check for duplicates in the array
        //check for duplicates in the array
        for(int x = 0; x<n;x++){
            for(int y = x+1;y<n;y++){
                if((char)*(cElements+x)==(char)*(cElements+y)){
                    printf("Error in column %d\n", i);
                    free(cElements);
                    return 0;
                }
            }
        }

    }
    free(cElements);
    // printf("Error in column %d\n", i);
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */ 
void Free_Memory(const size_t n, char **latin_square) {
    /* BEGIN MODIFYING CODE HERE */
    //free all the individual elements
    for(int i = 0; i<n;i++){
        free(*(latin_square+i));
    }
    //free the rows
    free(latin_square);
    /* END MODIFYING CODE HERE */
}


