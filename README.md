# Trivial VM

The most trivial virtual machine for education purposes. It can run a few x86 machine code instructions on Windows OS. I never tried to build it on Linux but it should be possible.

The VM is very slow because it copies the instruction being executed to an executable buffer and runs it directly.

This project was introduced at _hysteria session 2011_.

The `LDE64.lib` is Lenght Disassembler. It comes from https://github.com/BeaEngine/lde64.

## Tools

* Visual compiler and linker
* NASM

Another toolchain can be used too but beware of command line options. For more see the batch files.

## Build

The build batch files produce listings in assembler language. The listing shows what instructions actually run in the VM.

## VM core

The core functionality is located in `execute.asm`. The instruction being executed is stored in `execute_instruction_buffer` first, `execute_instruction()` is called to execute it then.

## VM1

The `vm1.c` is the simplest VM possible. It consists of few tens of lines of simple C and asm code.

It merely runs very simple code:

    printf("%s World\n\n\n", "Hysteria");
    exit(0);

## VM2

The `vm2.c` builds on VM1 and shows how to resolve branch instructions that can't be executed directly. It runs slightly more complicated code:

    int number;
    printf("enter decimal number: ");
    if (1 != scanf("%d", &number)) {
      printf("error, exiting...\n");
      exit(1);
    }
    printf ("hexadecimal: %X\n", number);
    exit(0);
