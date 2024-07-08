Instructions to Compile and Execute the Code :
-> Ensure that you have a C/C++ compiler installed on your system.
-> Place the input.txt file with the machine code in the same directory as the source code.
-> Open a terminal or command prompt.
-> Navigate to the directory containing the source code and input1.txt.
-> There are two input files(input1.txt, input2.txt) in the folder. Any one of them can be used in the code.
-> Compile the code using the command: gcc disassembler.c -o disassembler
-> Execute the program with: ./disassembler

Sample Input(from text file) :
007201b3
00720863
00c0006f
00533623
100004b7
00c50493

Expected Output :
add x3, x4, x7
beq x4, x7, L1
jal x0, L1
sd x5, 12(x6)
lui x9, 0x10000
L1: addi x9, x10, 12