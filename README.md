# Arm_Hackathon

Task Two
Requires g++ with support for c++20.
Run the following command inside of the task_two directory to compile:
```
g++ main.cpp -std=c++20 -Ofast -Wno-write-strings -fomit-frame-pointer
```
To run:
```
./a.out my_input_filename.txt
```

Task Four
The makefile handles compiling and running the fsm verilog code - try make execute_fsm to compile and run it
fsm.v is the raw verilog code
fsm is the compiled verilog code
fsm.png shows a simulation of the fsm based on jk flip-flops designed by hand
fsm_working.png shows the work to design the fsm shown in fsm.png