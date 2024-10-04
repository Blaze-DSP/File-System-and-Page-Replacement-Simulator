#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim_eng.h"

void display_frames(int arr[], int size, int fault) {
    printf("[");
    for (int i = 0; i < size; i++) {
        if (arr[i] == -1) { // Assuming -1 represents an empty frame
            printf("  ");
        } else if (arr[i] < 10) {
            printf(" %d", arr[i]);
        } else {
            printf("%d", arr[i]);
        }
        if(i!=size-1)
            printf("|");
    }
    if(fault)
        printf("] F\n");
    else
        printf("]\n");
}

void fifo( int num_frames, int page_refs[], int num_refs, int verbosity, FILE *file){
    int frames[num_frames];
    memset(frames, -1, sizeof(frames)); // Initialize frames with -1 indicating empty

    int page_faults = 0;

    for(int i=0; i<num_refs;i++){
        int page = page_refs[i];
        int frame_found = 0;

        // Check if page already in memory
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                frame_found = 1;
                break;
            }
            else if(frames[j]==-1){
                frame_found = 1;
                frames[j] = page;
                break;
            }
        }

        if(!frame_found){
            for(int k=0; k<num_frames; k++){
                if(k == num_frames-1){
                    frames[k] = page;
                }
                else{
                    frames[k] = frames[k+1];
                }
            }
            page_faults++;
            if(verbosity){
                printf("%d: ", page);
                display_frames(frames,num_frames,1);
            }
        }
        else if(verbosity){
            printf("%d: ", page);
            display_frames(frames,num_frames,0);
        }
    }

    float miss_rate;
    if(verbosity){
        miss_rate = (float)page_faults / num_refs * 100;
        printf("Miss rate = %d / %d = %.2f%%\n", page_faults, num_refs, miss_rate);
    }   
    else{
        miss_rate = (float)page_faults / num_refs * 100;
        printf("fifo, %d frames: Miss rate = %d / %d = %.2f%%\n", num_frames, page_faults, num_refs, miss_rate);
    }

    if(file != NULL){
        fprintf(file, "%.2f ", miss_rate);
    }
}

void lru( int num_frames, int page_refs[], int num_refs, int verbosity, FILE *file){
    int frames[num_frames];
    memset(frames, -1, sizeof(frames)); // Initialize frames with -1 indicating empty

    int page_faults = 0;

    for(int i=0; i<num_refs; i++){
        int page = page_refs[i];
        int frame_found = 0;

        // Check if page already in memory
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                frame_found = 1;

                for(int k=j; k<num_frames; k++){
                    if(k == num_frames-1){
                        frames[k] = page;
                    }
                    else if(frames[k+1] == -1){
                        frames[k] = page;
                        break;
                    }
                    else{
                        frames[k] = frames[k+1];
                    }
                }
                break;
            }
            else if(frames[j]==-1){
                frame_found = 1;
                frames[j] = page;
                break;
            }
        }

        if(!frame_found){
            for(int k=0; k<num_frames-1; k++){
                frames[k] = frames[k+1];
            }
            frames[num_frames-1]=page;
            page_faults++;
            if(verbosity){
                printf("%d: ", page);
                display_frames(frames,num_frames,1);
            }
        }
        else if(verbosity){
            printf("%d: ", page);
            display_frames(frames,num_frames,0);
        }
    }

    float miss_rate;
    if(verbosity){
        miss_rate = (float)page_faults / num_refs * 100;
        printf("Miss rate = %d / %d = %.2f%%\n", page_faults, num_refs, miss_rate);
    }   
    else{
        miss_rate = (float)page_faults / num_refs * 100;
        printf("lru, %d frames: Miss rate = %d / %d = %.2f%%\n", num_frames, page_faults, num_refs, miss_rate);
    }

    if(file != NULL){
        fprintf(file, "%.2f ", miss_rate);
    }
}

void opt( int num_frames, int page_refs[], int num_refs, int verbosity, FILE *file){
    int frames[num_frames];
    memset(frames, -1, sizeof(frames)); // Initialize frames with -1 indicating empty

    int page_faults = 0;
    
    for(int i=0; i<num_refs;i++){
        int page = page_refs[i];
        int frame_found = 0;

        // Check if page already in memory
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                frame_found = 1;
                break;
            }
            else if(frames[j]==-1){
                frame_found = 1;
                frames[j] = page;
                break;
            }
        }

        if(!frame_found){
            int frame=-1, mx=-1;
            for(int j=0; j<num_frames; j++){
                int tmp=0;
                for(int k=i+1; k<num_refs; k++){
                    if(frames[j]==page_refs[k]){
                        break;
                    }
                    tmp++;
                }
                if(tmp>mx){
                    mx=tmp;
                    frame=j;
                }
            }

            frames[frame]  = page;
            page_faults++;
            if(verbosity){
                printf("%d: ", page);
                display_frames(frames,num_frames,1);
            }
        }
        else if(verbosity){
            printf("%d: ", page);
            display_frames(frames,num_frames,0);
        }
    }

    float miss_rate;
    if(verbosity){
        miss_rate = (float)page_faults / num_refs * 100;
        printf("Miss rate = %d / %d = %.2f%%\n", page_faults, num_refs, miss_rate);
    }   
    else{
        miss_rate = (float)page_faults / num_refs * 100;
        printf("opt, %d frames: Miss rate = %d / %d = %.2f%%\n", num_frames, page_faults, num_refs, miss_rate);
    }

    if(file != NULL){
        fprintf(file, "%.2f ", miss_rate);
    }
}