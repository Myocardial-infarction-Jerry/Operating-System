org 0x7c00 ; mbr
[bits 16]
mov cl, [len] ; 初始化循环变量
mov si, number ; 初始化学号地址
mov bl, 0fh ; 前景色亮白
again:
cmp cl, 0 ; cl大于零时继续循环
je end
mov ah, 02h
mov bh, 0
mov dh, 8
mov dl, [len] ; 计算列位置
sub dl, cl
add dl, 8
int 10h
push cx ; 保存cx
mov ah, 09h
lodsb ; 获取学号字符
mov cx, 1
int 10h
pop cx
dec cl ; cx自减
jmp again
end:
jmp $ ; 死循环
number db '21307289'
len db 8
times 510 - ($ - $$) db 0
db 0x55, 0xaa
