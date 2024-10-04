#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "sim_eng.c"
#include "sim_eng.h"

#define MIN_FRAME 2
#define MAX_FRAME 100
#define MAX_PAGES 100000

int main(int argc, char *argv[]) {
    // Check if correct number of arguments provided
    if (argc != 5) {
        printf("Insufficient Number of Arguments Passed\n");
        return 1;
    }

    // Parse arguments
    int min_frames = atoi(argv[1]);
    int max_frames = atoi(argv[2]);
    int increment = atoi(argv[3]);
    char *input_filename = argv[4];

    // Check if the min. no. of frames is valid
    if (min_frames < 2) {
        printf("Error: Invalid number of frames. Must be greater than or equal to %d\n", MIN_FRAME);
        return 1;
    }

    // Check if the max. no. of frames is valid
    if (min_frames > 100) {
        printf("Error: Invalid number of frames. Must be less than or equal to %d\n", MAX_FRAME);
        return 1;
    }

    // Check if increment is valid
    if (increment < 0) {
        printf("Error: Invalid value for increment. Must be positive\n");
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
    while (!feof(file)) {
        int num;
        fscanf(file, "%d", &num);
        page_refs[num_refs]=num;
        num_refs++;
    }
    fclose(file);

    printf("Page References: ");
    for(int i=0; i<num_refs; i++){
        printf("%d ", page_refs[i]);
    }
    printf("\n\n");

    // Open rates file
    FILE *rates = fopen("vmrates.dat", "w");
    if (rates == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }
    for(int i=min_frames; i<=max_frames; i+=increment){
        fprintf(rates, "%d ", i);
    }
    fprintf(rates,"\n");

    for(int i=0; i<3; i++){
        int num_frames = min_frames;
        while(num_frames <= max_frames){
            if(i == 0){
                opt(num_frames,page_refs, num_refs,0,rates);
            }
            else if(i == 1){
                lru(num_frames,page_refs, num_refs,0,rates);
            }
            else{
                fifo(num_frames,page_refs, num_refs,0,rates);
            }
            num_frames+=increment;
        }
        fprintf(rates,"\n");
    }

    fclose(rates);
    
    return 0;
}
