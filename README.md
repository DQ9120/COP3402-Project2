# COP3402-Project1
## COP3402 Systems Software Project 1 with
## David Qualls, Jenna Busch, and Kyle Mauter

==============================================

# Assignment Instructions
In this assignment we'll be implementing a virtual machine called the P-machine. \
vm.c is our skeleton file that we will be starting with \
Names should be in header comment of each source file, in readme, and comments of submission

We will be implementing the function "execute". It receives instructions from the compiler \
in the form of an instruction struct. We must then load the instructions into the stack \
prior to execution. We'll print out each line of execution as we move through the instructions, \
using the "-v" compiler directive. execute is passed a flag to indicate if the directive has been used. \
Print statements for read/write instructions should be printed regardless of directives.

# P-Machine
## Structure
The P-machine has two memory areas:
  - Stack: stores variables and grows downwards
  - Text:  stores instructions for VM to execute

Also has register file where arithmetic and logic instructions are executed. \
The P-machine has registers to handle the stack:
  - BP: Base Pointer
  - SP: Stack Pointer
  - PC: Program Counter
  - IR: Instruction Register

The Instruction Set Architecture of the P-machine is as follows:
  There are three fields "OP L M" that are separated by a single space character
  - OP: operation code, specifies the instruction to execute
  - R: register, specifies which register the operation should output in or store from
  - L: lexicographical level
  - M: depends on the operator it indicates
      * A number          (instructions: LIT, INC)
      * A program address (instructions: JMP, JPC, CAL)
      * A data address    (instructions: LOD, STO)
## Cycles
The instruction cycle is done in 2 steps (2 steps per instruction):
  - Fetch Cycle:   instruction from PC is fetched from "text" segment, placed in IR
  - Execute Cycle: instruction in IR is executed using data + register stacks
  
 ![image](https://user-images.githubusercontent.com/63477278/155031454-17757586-3792-4856-9dd1-c228490e314f.png)

## Starting Values
  - BP = MAX_STACK_LENGTH - 1               (BP: points to base of curr AR)
  - SP = BP + 1                             (SP: points to top entry of stack)
  - PC = 0                                  (PC: points to next instruction)
  - IR                                      (IR: holds curr instruction, array or struct)
  - Initial stack + reg file values = 0
  - REG_FILE_SIZE = 10
  - MAX_STACK_LENGTH = 100
  - input file <= 150 lines of code

## Error Handling
- Stack Overflow Error: when SP < 0, check for in INC
- Out of Bounds Access Error: when LOD or STO instruction accesses value < 0  or >= MAX_STACK_LENGTH

## Appendixes
[Appendexes](HW1InstructionsSpring2022_Almalki.pdf)
