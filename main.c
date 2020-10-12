#include <stdio.h>
#include <stdlib.h>


int main( int argc, char *argv[argc+1]) {

    //File name from arguments
    if (argc != 3 ){
        printf("no file");
        return EXIT_SUCCESS;
    }

    // Declare the read file
    FILE *fp;

    fp = fopen( argv[1], "r");

    // Check if the file is empty
    if ( fp == NULL ){
        printf("Unable to read");
        return EXIT_SUCCESS;
    }
    // Get the data
    int matrixGrid;

    while ( fscanf( fp, "%d", &matrixGrid ) != EOF ){
        printf("%d", matrixGrid);
    }

    // Close the file and destroy memory allocations
    fclose(fp);



    return EXIT_SUCCESS;
}
