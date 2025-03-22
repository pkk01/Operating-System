# Operating System Concepts Repository

## Description
This repository contains various C programs that demonstrate key concepts in operating systems, including memory allocation techniques, deadlock prevention algorithms, page replacement strategies, and process scheduling methods. Each program is designed to provide practical insights into how these concepts are implemented in real-world scenarios.

## Directory Structure
- **MemoryAllocationTechniques/**: Contains programs related to different memory allocation techniques.
  - `01_DMA.c`: Demonstrates dynamic memory allocation using `malloc()`.
  - `06_Heap.c`: Implements a custom memory allocation system using heap management.
  - `07_affectOfFree.c`: Explores the effects of freeing allocated memory.
  
- **DeadLocks/**: Contains programs that address deadlock prevention.
  - `01_BankersAlgorithm.c`: Implements the Banker's Algorithm for deadlock avoidance.
  - `02_BankAlgoPrevention.c`: Simulates deadlock prevention strategies.
  - `03_SharedMemory.c`: Demonstrates shared memory concepts.

- **PageReplacementTechniques/**: Contains programs that illustrate various page replacement algorithms.
  - `01_FIFO.c`: Implements the First-In-First-Out (FIFO) page replacement algorithm.
  - `02_LRU.c`: Implements the Least Recently Used (LRU) page replacement algorithm.
  - `03_OPR.c`: Implements the Optimal Page Replacement algorithm.
  - `04_LFU.c`: Implements the Least Frequently Used (LFU) page replacement algorithm.

- **ProcessScheduling/**: Contains programs that demonstrate different process scheduling algorithms.
  - `FCFS01.c`: Implements the First-Come, First-Served (FCFS) scheduling algorithm.
  - `LotteryScheduling08.c`: Implements the Lottery Scheduling algorithm.
  - Other scheduling algorithms are also included.

## Usage
To compile and run the programs, use the following commands in your terminal:
```bash
gcc <filename>.c -o <outputname>
./<outputname>
```
Replace `<filename>` with the name of the C file you want to compile and `<outputname>` with the desired name for the executable.

## Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
