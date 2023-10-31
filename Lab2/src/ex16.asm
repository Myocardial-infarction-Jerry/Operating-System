org 0x7c00 ; mbr
[bits 16]
; 光标置于(8, 8)
mov ah, 02h
mov bh, 0
mov dh, 8
mov dl, 8
int 10h
; 读取光标位置
mov ah, 03h
int 10h
mov si, dx ; 行列
mov bl, 0fh ; 亮白
; 输出
mov ah, 09h
mov al, '('
mov cx, 1
int 10h
mov ah, 02h
mov bh, 0
mov dh, 8
mov dl, 9
int 10h
mov ax, si
mov cl, 8
shr ax, cl
add al, '0'
mov ah, 09h
mov cx, 1
int 10h
mov ah, 02h
mov bh, 0
mov dh, 8
mov dl, 0ah
int 10h
mov ah, 09h
mov al, ','
mov cx, 1
int 10h
mov ah, 02h
mov bh, 0
mov dh, 8
mov dl, 0bh
int 10h
mov ax, si
add al, '0'
mov ah, 09h
mov cx, 1
int 10h
mov ah, 02h
mov bh, 0
mov dh, 8
mov dl, 0ch
int 10h
mov ah, 09h
mov al, ')'
mov cx, 1
int 10h
jmp $ ; 死循环
times 510 - ($ - $$) db 0
db 0x55, 0xaa
