; export symbols required by the VM

global _execute_instruction
global _execute_instruction_buffer
global _virt_regs
global _virt_flags

section .text

; execute_instruction() runs one instruction already stored in the instruction
; buffer

_execute_instruction:

 ; save current context (registers of VM interpeter)

 pushf
 pop dword [flags]
 mov [regs], eax
 mov [regs+4], ecx
 mov [regs+8], edx
 mov [regs+12], ebx
 mov [regs+16], esp
 mov [regs+20], ebp
 mov [regs+24], esi
 mov [regs+28], edi

 ; load registers of virtualized code

 push dword [_virt_flags]
 popf
 mov eax, [_virt_regs]
 mov ecx, [_virt_regs+4]
 mov edx, [_virt_regs+8]
 mov ebx, [_virt_regs+12]
 mov esp, [_virt_regs+16]
 mov ebp, [_virt_regs+20]
 mov esi, [_virt_regs+24]
 mov edi, [_virt_regs+28]

 ; execute the instruction

_execute_instruction_buffer:
 TIMES 15 DB 0x90

 ; save registers of virtualized code

 pushf
 pop dword [_virt_flags]
 mov [_virt_regs], eax
 mov [_virt_regs+4], ecx
 mov [_virt_regs+8], edx
 mov [_virt_regs+12], ebx
 mov [_virt_regs+16], esp
 mov [_virt_regs+20], ebp
 mov [_virt_regs+24], esi
 mov [_virt_regs+28], edi

 ; for correct transition back to interpreter context, load original registers

 push dword [flags]
 popf
 mov eax, [regs]
 mov ecx, [regs+4]
 mov edx, [regs+8]
 mov ebx, [regs+12]
 mov esp, [regs+16]
 mov ebp, [regs+20]
 mov esi, [regs+24]
 mov edi, [regs+28]

 ret

section .data

 regs TIMES 8 DD 0
 flags DD 0

 _virt_regs TIMES 8 DD 0
 _virt_flags DD 0
