org 0x7c00 ; mbr
[bits 16]
; 初始化
mov dl, 0 ; 列
mov dh, 8 ; 行
mov bh, 0 ; 页码
mov bl, 0fh ; 亮白色
mov cx, 1 ; 输出字符数
mov ah, 02h
int 10h ; 设置光标
again:
; 等待输入
mov ah, 0
int 16h ; 等待键盘输入
; 字符回显
mov ah, 09h
int 10h
; 移动光标
cmp dl, 79
je next_line
inc dl
jmp move_cursor
next_line:
cmp dh, 25
je first_line
mov dl, 0
inc dh
jmp move_cursor
first_line:
mov dx, 0
move_cursor:
mov ah, 02h
int 10h
jmp again ; 重复输入
times 510 - ($ - $$) db 0
db 0x55, 0xaa
