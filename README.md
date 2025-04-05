# Reverse Engineering Task Solution

## Project Overview  
This repository contains a solution to reverse engineer the algorithm used by `ReverseTestTask1.exe`, which processes `input.bin` to generate `output.bin`. The goal is to replicate this algorithm in a C program.

---

## Task Description  
The original task provided the following problem statement (translated):  
> *"ReverseTestTask1.exe reads `input.bin` on startup and generates `output.bin` from it. The task is to replicate the generation algorithm. Any file can be used as `input.bin`."*

---

## Building the Solution  
The solution is implemented in `main.c`. To build the program:  
```bash
gcc main.c -o main
```  

---

## Testing the Solution  
A test script `test.sh` is included to verify correctness:  
1. Generates a random `input.bin` file.  
2. Runs both `main` and `task/ReverseTestTask1.exe` to produce their respective `output.bin` files.  
3. Compares the MD5 checksums of both outputs.  

Run the test with:  
```bash
./test.sh
```  
Configure test params inside *test.sh* if need.
