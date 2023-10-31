[bits 32]

global asm_name

asm_name:
    mov ecx, name_tag_end - name_tag
    mov ebx, 80 * 24
    add ebx, 12 * 2
    mov esi, name_tag
    mov ah, 0x74
    output_name_tag:
        xor ah, 0x33
        mov al, [esi]
        mov word[gs:ebx], ax
        add ebx, 2
        inc esi
        loop output_name_tag

    push eax
    xor eax, eax
    pop eax
    ret

name_tag db '21307289 liusenyuan'
name_tag_end: