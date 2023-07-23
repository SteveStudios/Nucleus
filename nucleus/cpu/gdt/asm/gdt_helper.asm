; gdt_helper.asm - GDT (Global Descriptor Table) helper
; Created 2023/7/21 by Stephen Byrne

global reload_segment_registers

; Reloads the segment registers, and calls ".reload_data_segments"
reload_segment_registers:
    PUSH 0x28
    LEA RAX, [rel .reload_data_segments] 
    PUSH RAX 
    RETFQ 

; Reload the CS/Data segment registers
.reload_data_segments:
    MOV AX, 0x30
    MOV DS, AX
    MOV ES, AX
    MOV FS, AX
    MOV GS, AX
    MOV SS, AX
    RET