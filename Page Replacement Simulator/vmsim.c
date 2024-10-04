#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim_eng.h"

#define MAX_FRAMES 100
#define MAX_PAGES 100000

int main(int argc, char *argv[]) {
    // Check if correct number of arguments provided
    if (argc != 4) {
        printf("Insufficient Number of Arguments Passed\n");
        return 1;
    }

    // Parse arguments
    int num_frames = atoi(argv[1]);
    char *input_filename = argv[2];
    char *algorithm = argv[3];

    // Check if number of frames is valid
    if (num_frames <= 0 || num_frames > MAX_FRAMES) {
        printf("Error: Invalid number of frames. Must be between 1 and %d.\n", MAX_FRAMES);
        return 1;
    }

    // Check if algorithm is valid
    if (strcmp(algorithm, "opt") != 0 && strcmp(algorithm, "lru") != 0 && strcmp(algorithm, "fifo") != 0) {
        printf("Error: Invalid algorithm. Choose from 'opt', 'lru', or 'fifo'.\n");
        return 1;
    }

    // Open input file
    FILE *file = fopen(input_filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    // Read page references from file
    int page_refs[MAX_PAGES];
    int num_refs = 0;
    while (fscanf(file, "%d", &page_refs[num_refs])==1) {
        num_refs++;
    }
    fclose(file);

    printf("Page References: ");
    for(int i=0; i<num_refs; i++){
        printf("%d ", page_refs[i]);
    }
    printf("\n\n");

    if (strcmp(algorithm, "fifo") == 0) {
        fifo(num_frames, page_refs, num_refs, 1, NULL);
    } 
    else if (strcmp(algorithm, "lru") == 0) {
        lru(num_frames, page_refs, num_refs, 1, NULL);
    } 
    else if (strcmp(algorithm, "opt") == 0) {
        opt(num_frames, page_refs, num_refs, 1, NULL);
    }

    return 0;
}
