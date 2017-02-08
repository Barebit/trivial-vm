#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// import symbols that are exported by the asm runtime

void execute_instruction();
extern unsigned char execute_instruction_buffer[15];
extern unsigned virt_regs[8];

// import Length disassembler

unsigned __stdcall LDE(void*, int);

// define code that's gonna run in VM

void virtualized_code()
{
  // print "Hysteria World"
  printf("%s World\n\n\n", "Hysteria");
  // exit() must be used to terminate the VM correctly
  exit(0);
}

// helper function that prints current opcode

int main()
{
  // set up instruction pointer for virtualized code
  unsigned char *ip = virtualized_code;

  unsigned instruction_length;

  // initialize stack for virtualized code;
  // it starts 200 bytes below the interpreter's stack

  __asm mov eax, esp
  __asm sub eax, 200
  __asm mov [virt_regs+16], eax   // "+16" is location of virtual ESP register

  // do not initialize the other registers because their values are meaningless

  // execute the instrutions one by one;
  // the endless loop breaks when the "exit(0)" command was executed

  for (;;) {
    // get lenght of current instruction
    instruction_length = LDE(ip, 0);
    // initialize the execution buffer to all NOPs
    memset(execute_instruction_buffer, 0x90, 15);
    // copy current instruction to the execution buffer
    memcpy(execute_instruction_buffer, ip, instruction_length);
    // run it
    execute_instruction();
    // move to next instruction
    ip += instruction_length;
  }
}