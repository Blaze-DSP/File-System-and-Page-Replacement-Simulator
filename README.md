# File System and Page Replacement Simulator

## Project Overview
This project implements a simple file system and a page replacement simulator. The file system supports basic operations like file and directory creation, reading, and deletion by managing inodes for metadata, allocating/deallocating data blocks, and updating directory structures. The page replacement simulator compares the efficiency of LRU, FIFO, and OPT algorithms by tracking page faults and miss rates across different workloads.

## Features
### File System Operations:
* Creation, reading, and deletion of files and directories.
* Management of space allocation using data blocks.
* Updating directory structures and handling file metadata through inodes.

### Page Replacement Simulator:
* Implementation of LRU, OPT, and FIFO algorithms.
* Evaluation of algorithm efficiency based on page faults and miss rates.
* Analysis of algorithm performance under varying workloads.

## Project Structure
```
.
├── File System/                    
│   ├── sfs.c                       # Implementation code                   
│   └── sfs.disk                    # Disk file containing data
├── Page Replacement Simulator/
│   ├── Makefile                    # Makefile to generate executables   
│   ├── sim_eng.c                   # Page replacement algorithms   
│   ├── sim_eng.h                   # Header file   
│   ├── vmgen.c                     # Page reference generator 
│   ├── vmsim.c                     # Page replacement simulator                   
│   └── vmstats.c                   # Page replacement statistics
└── README.md                   # Project documentation
```

## How to run project

### Pre-Requisistes
* A C compiler (e.g., GCC)
* A Linux or Unix-based system is recommended, as the project interacts with low-level system components.

1. **Clone Repository**
   ```bash
   git clone https://github.com/Blaze-DSP/File-System-and-Page-Replacement-Simulator.git
   cd File-System-and-Page-Replacement-Simulator
   ```
2. **To run File Sytstem Implementation**
    ```bash
   cd File System Implementation
   gcc sfs.c -o sfs_out -lm
   ./sfs_out
   SFS::/# <command>
   ```
   Command list:
   1. ls
   2. md <dname>
   3. cd <dname>
   4. create <fname> (Press ESC+Enter to stop entering data into file)
   5. rm <name>
   6. display <fname>
   7. rd
   8. exit
3. **To run Page Replacemetnt Simulator**
    ```bash
   cd Page Replacemetnt Simulator
   make
   ./vmgen_out <range of page references (max=100)> <length of sequence> <fname.dat>
   ./vmsim_out <total physical frames> <fname.dat> <algortihm: 'fifo','lru' or 'opt'>
   ./vmstats <min. frames> <max. frames> <frame increment> <fname.dat>
   make clean
   ```

## Future Improvements
* Extend file system functionality to include more operations (e.g., file permissions, symbolic links).
* Add GUI for better interaction with the simulators.
* Optimize the simulators for larger workloads and datasets.
