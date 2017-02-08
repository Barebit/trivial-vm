#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// for comments see also vm1.c

void execute_instruction();
extern unsigned char execute_instruction_buffer[15];
extern unsigned virt_regs[8];
extern unsigned virt_flags;

unsigned __stdcall LDE(void*, int);

void virtualized_code()
{
  int number;
  printf("enter decimal number: ");
  if (1 != scanf("%d", &number)) {
    printf("error, exiting...\n");
    exit(1);
  }
  printf ("hexadecimal: %X\n", number);
  exit(0);
}

int main()
{
  unsigned char *ip = virtualized_code;

  unsigned instruction_length;
  int distance;

  __asm mov eax, esp
  __asm sub eax, 200
  __asm mov [virt_regs+16], eax

  for (;;) {
    instruction_length = LDE(ip, 0);
    memset(execute_instruction_buffer, 0x90, 15);
    memcpy(execute_instruction_buffer, ip, instruction_length);

    // handle branch instructions that can't be executed directly

    switch (*ip) {
       case 0x74:   // opcode of branch instruction JE rel8
         // if Zero Flag is set, continue to branch target, otherwise move to
         // next instruction
         if (virt_flags & (1 << 6))
           ip += instruction_length + (int)(signed char)ip[1];
         else
           ip += instruction_length;
         continue;

       case 0xE8:   // opcode of branch instruction CALL rel32
         // count target distance
         distance = (int)(execute_instruction_buffer - ip);
         *(int*)(execute_instruction_buffer+1) -= distance;
         break;
    }

    execute_instruction();
    ip += instruction_length;
  }
}