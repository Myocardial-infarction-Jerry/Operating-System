your_if:
mov eax, [a1] ; load a1
cmp eax, 12
jl C1
cmp eax, 24
jl C2
C3: ; a1 >= 24
sal eax, 4
mov [if_flag], eax
jmp CE
C2: ; 12 <= a1 < 24 
mov edx, 24
sub edx, eax
imul eax, edx
mov [if_flag], eax
jmp CE
C1: ; a1 < 12
sar eax, 1
add eax, 1
mov [if_flag], eax
CE:

your_while:

L1:
mov edx, [a2]
cmp edx, 12
jl WE
call my_random
mov edx, [a2]
mov edi, edx
sub edi, 12
mov ebx, [while_flag]
mov [ebx + edi], al
sub edx, 1
mov [a2], edx
jmp L1
WE:

your_function:
mov esi, [your_string]
L2:
lodsb
cmp al, 0
je FE
pushad
push ax
call print_a_char
pop ax
popad
jmp L2
FE:
ret
