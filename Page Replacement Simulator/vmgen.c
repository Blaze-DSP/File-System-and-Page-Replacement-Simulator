#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PAGE 100

int main(int argc, char *argv[]) {
    // Check if correct number of arguments provided
    if (argc != 4) {
        printf("Insufficient Number of Arguments Passed\n");
        return 1;
    }

    // Parse arguments
    int range = atoi(argv[1]);
    int length = atoi(argv[2]);
    char *output_filename = argv[3];

    // Check if the range of page references is valid
    if (range < 0 || range > MAX_PAGE) {
        printf("Error: Invalid number of frames. Must be between 1 and %d.\n", MAX_PAGE);
        return 1;
    }

    // Open output file
    FILE *file = fopen(output_filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }

    srand(time(NULL)); // Add random seed to rand()
    int page, prev_page=-1;
    for(int i=0; i<length; i++){
        page = rand()%range;
        while(page == prev_page){
            page = rand()%range;
        }
        if(i==length-1)
            fprintf(file, "%d", page);
        else
            fprintf(file, "%d ", page);
        prev_page = page;
    }
    
    fclose(file);
    printf("Output File containing sequence of %d page numbers from 0 to %d generated as %s.\n", length, range, output_filename);
    
    return 0;
}
