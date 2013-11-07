/*
 * wave.c
 * authors: Sam Mansfield and Toan Vuong
 * date: 10-29-13
 * desc: A wave generator for the 3x3x3 cube.
 *       Will generate a wave from one corner to the other
*/
#include <stdlib.h>
#include <stdio.h>
/************* TOOOLS START ********************/
#define NULL 0

// Originally a linked list, hence the name
// Modified to be a doubly-linked list
struct LinkedList {
    int col;
    struct LinkedList *prev;
    struct LinkedList *next;
};

/*
 * Echo pulse
*/
const int ECHO = 10;
/*
 * Trigger pulse
*/
const int TRIGPING = 9;

/*
 * Column pins
*/
const int COL_0_0 = 12;
const int COL_1_0 = 19;
const int COL_2_0 = 16;
const int COL_0_1 = 21;
const int COL_1_1 = 18;
const int COL_2_1 = 15;
const int COL_0_2 = 20;
const int COL_1_2 = 17;
const int COL_2_2 = 14;
const int COL_INVALID = 99;
/*
 * Plane pins
*/

const int PLANE_0 = 22;
const int PLANE_1 = 11;
const int PLANE_2 = 13;
const int PLANE_INVALID = 99;
/*
 * Number of columns
*/
const int NUM_COLS = 9;
/*
 * Number of planes
*/
const int NUM_PLANES = 3;

/*
 * Mapping of planes to array
*/
int planes[NUM_PLANES] = { PLANE_0,
                           PLANE_1,
                           PLANE_2,
                         };

/*
 * Currently ON columns
*/
// First LED in list
//struct struct LinkedList *cols = (struct struct LinkedList*) malloc(sizeof(struct struct LinkedList));
struct LinkedList *colsByPlane[NUM_PLANES];
int numColsByPlane[NUM_PLANES];
struct LinkedList *cols = NULL;

/*
 * Points plane to be invalid
*/
void setInvalid() {
    int i = 0;
    for(; i < NUM_PLANES; ++i) {
        colsByPlane[i] = NULL;
        numColsByPlane[i] = 0;
    }
}

/*
 * Removes arbitrary column from our list
 * Quits after removing the first colmn found or not finding any
 * Slightly more involved than addCol
*/
void removeCol(int col, int plane) {
    struct LinkedList *iterator = colsByPlane[plane];
    int i = 0;
    for (; i < numColsByPlane[plane]; ++i) {
        if (iterator->col == col) {
            struct LinkedList *delete = iterator;
            iterator = iterator->prev; 
            iterator->next = delete->next;
            delete->next->prev = iterator;
            if (numColsByPlane[plane] > 1) {
                // Move where cols point
                // Necessary because we might have removed the first element
                // in which case cols will be pointing to nowhere
                colsByPlane[plane] = iterator;
            } else {
                // Removing the only element in list, so set cols to point
                // to NULL
                cols = NULL;
            }
            free(delete);
            --(numColsByPlane[plane]);
            return;
        } else {
            iterator = iterator->next;
        }
    }
}

/*
 * De-initializes cols list
*/
void cleanCols(int plane) {
    int i = 0;
    // Gotta save numCols because removeCol() modifies it
    int total = numColsByPlane[plane];
    for(; i < total; ++i) {
        removeCol(colsByPlane[plane]->col, plane); 
    }
}

/*
 * Adds a column to our list
 * Makes no guarantee about uniqueness!
 * DO NOT ADD MULTIPLE COLUMNS (Although, in theory this shouldn't matter)
*/
void addCol(int col, int plane) {
    if (!colsByPlane[plane]) {
        colsByPlane[plane] = (struct LinkedList*) malloc(sizeof(struct LinkedList));
        struct LinkedList *cols = colsByPlane[plane];
        cols->col = col;
        cols->next = cols;
        cols->prev = cols;
    } else {
        struct LinkedList *cols = colsByPlane[plane];
        struct LinkedList *colsTail = cols->prev;
        // Allocate space for next list
        colsTail->next = (struct LinkedList*) malloc(sizeof(struct LinkedList));
        colsTail = colsTail->next;
        colsTail->col = col;
        colsTail->next = cols;
        colsTail->prev = cols->prev;
        cols->prev = colsTail;
    }
    ++(numColsByPlane[plane]);
}

/*
 * Initializes cols pointer with the given array
*/
void initCols(int *arr, int size, int plane) {
    cleanCols(plane);
    int i = 0;
    for (i = 0; i < size; ++i) {
        addCol(arr[i], plane);        
    }
}

// Debugging
// Assumes col is 2 chars long
// Quick hack to test my functions
char *toString(int plane) {
    char *buffer = malloc(sizeof(char) * 500);
    char *cur = buffer;
    struct LinkedList *iterator = colsByPlane[plane];
    int i = 0;
    *(cur++) = '{';
    *(cur++) = ' ';
    if (numColsByPlane[plane] == 0) {
        *(cur++) = '}';
        *cur = '\0';
        return buffer;
    }
    for(; i < numColsByPlane[plane]; ++i) {
        sprintf(cur, "%d, ", iterator->col);
        iterator = iterator->next;
        cur += 4;
    }
    *(cur) = '\0';
    *(--cur) = '}'; 
    *(--cur) = ' ';
    return buffer;
}

/************* TOOOLS END ********************/

/*
 * Initializes pins
*/
void setup() {
    setInvalid();
}

// Single element
void initColsTest1() {
    int SIZE = 1;
    // 12
    int arr[] = { COL_0_0 };
    initCols(arr, SIZE, 0);
    fprintf(stdout, "Starting initColsTest1:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
}

// Empty
void initColsTest2() {
    int SIZE = 0;
    int arr[] = { };
    initCols(arr, SIZE, 0);
    fprintf(stdout, "Starting initColsTest2:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
}

// Two elements
void initColsTest3() {
    int SIZE = 2;
    // 12
    int arr[] = { COL_0_0, COL_0_1 };
    initCols(arr, SIZE, 0);
    fprintf(stdout, "Starting initColsTest3:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
}

// Four elements
void initColsTest4() {
    int SIZE = 4;
    // 12
    int arr[] = { COL_0_0, COL_0_1, COL_0_2, COL_1_0 };
    initCols(arr, SIZE, 0);
    fprintf(stdout, "Starting initColsTest4:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
}
// cleanCols with 1 element
void cleanColsTest1() {
    int SIZE = 1;
    int arr[] = { COL_0_0 };
    initCols(arr, SIZE, 0);
    // Clean up
    cleanCols(0);
    fprintf(stdout, "Starting cleanColsTest1:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
}

// Tests cleanCols with four elements
void cleanColsTest2() {
    int SIZE = 4;
    int arr[] = { COL_0_0, COL_0_1, COL_0_2, COL_1_0 };
    initCols(arr, SIZE, 0);
    // Clean up
    cleanCols(0);
    fprintf(stdout, "Starting cleanColsTest2:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
}

// Add to empty
void addColTest1() {
    addCol(COL_0_0, 0);
    fprintf(stdout, "Starting addColTest1:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
    cleanCols(0);
}

// Add to empty, and one more
void addColTest2() {
    addCol(COL_0_0, 0);
    addCol(COL_0_1, 0);
    fprintf(stdout, "Starting addColTest2:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
    cleanCols(0);
}

// Add to cols created with initCols
void addColTest3() {
    int SIZE = 4;
    // 12
    int arr[] = { COL_0_0, COL_0_1, COL_0_2, COL_1_0 };
    initCols(arr, SIZE, 0);
    addCol(COL_1_1, 0);
    fprintf(stdout, "Starting addColTest3:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
    cleanCols(0);
}

// Empty
void removeColTest1() {
    removeCol(COL_0_0, 0);
    fprintf(stdout, "Starting removeColTest1:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
    cleanCols(0);
}

// One element
void removeColTest2() {
    addCol(COL_0_0, 0);
    removeCol(COL_0_0, 0);
    fprintf(stdout, "Starting removeColTest2:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
    cleanCols(0);
}

// One element
void removeColTest3() {
    addCol(COL_0_0, 0);
    removeCol(COL_1_0, 0);
    fprintf(stdout, "Starting removeColTest3:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
    cleanCols(0);
}

// One element
void removeColTest4() {
    int SIZE = 4;
    // 12
    int arr[] = { COL_0_0, COL_0_1, COL_0_2, COL_1_0 };
    initCols(arr, SIZE, 0);
    removeCol(COL_1_0, 0);
    fprintf(stdout, "Starting removeColTest4:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
    cleanCols(0);
}

// One element
void removeColTest5() {
    int SIZE = 4;
    // 12
    int arr[] = { COL_0_0, COL_0_1, COL_0_2, COL_1_0 };
    initCols(arr, SIZE, 0);
    removeCol(COL_0_1, 0);
    fprintf(stdout, "Starting removeColTest5:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
    cleanCols(0);
}


// One element
void removeColTest6() {
    int SIZE = 4;
    // 12
    int arr[] = { COL_0_0, COL_0_1, COL_0_2, COL_1_0 };
    initCols(arr, SIZE, 0);
    removeCol(COL_2_0, 0);
    fprintf(stdout, "Starting removeColTest6:\n");
    char *colsString = toString(0);
    fprintf(stdout, "%s\n", colsString);
    free(colsString);
    cleanCols(0);
}

void initColsTests() {
    initColsTest1();
    initColsTest2();
    initColsTest3();
    initColsTest4();
}

void cleanColsTests() {
    cleanColsTest1();
    cleanColsTest2();
}

void addColTests() {
    addColTest1();
    addColTest2();
    addColTest3();
}

void removeColTests() {
    removeColTest1();
    removeColTest2();
    removeColTest3();
    removeColTest4();
    removeColTest5();
    removeColTest6();
}

int main() {
    setup();
    initColsTests();
    cleanColsTests();
    addColTests();
    removeColTests();
}
