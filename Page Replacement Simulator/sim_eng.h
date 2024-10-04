#ifndef SIMENG_H
#define SIMENG_H

void display_frames(int arr[], int size, int fault);

void fifo( int num_frames, int page_refs[], int num_refs, int verbosity, FILE *file);

void lru( int num_frames, int page_refs[], int num_refs, int verbosity, FILE *file);

void opt( int num_frames, int page_refs[], int num_refs, int verbosity, FILE *file);

#endif //SIMENG_H