org 0x7c00 ; mbr
[bits 16]
; 初始化
mov si, string ; 加载字符表
mov di, 0 ; 光标选择
mov bh, 0 ; 设置页号
again:
; 设置光标
mov dh, [y + di]
mov dl, [x + di]
mov ah, 02h
int 10h
; 获取字符
lodsb
cmp al, 0
jne print
mov si, string ; 重置字符指针
lodsb
; 打印字符
print:
mov cx, 1 ; 输出字符数
mov bl, [color + di] ; 颜色
mov ah, 09h
int 10h
; 打印信息
pushad
mov cl, 25 ; 初始化循环变量
mov si, info ; 初始化学号地址
mov bl, 02h ; 前景色绿色
infop:
cmp cl, 0 ; cl大于零时继续循环
je infoe
mov ah, 02h
mov bh, 0
mov dh, 0
mov dl, 25 ; 计算列位置
sub dl, cl
add dl, 27
int 10h
push cx ; 保存cx
mov ah, 09h
lodsb ; 获取学号字符
mov cx, 1
int 10h
pop cx
dec cl ; cx自减
jmp infop
infoe:
popad
; 列坐标更新
cmp dl, 79 ; 边界检测
je rb
cmp dl, 0
je lb
jmp col
rb: ; 右边界
mov [vx + di], byte -1
jmp col
lb: ; 左边界
mov [vx + di], byte 1
col: ; 更新列坐标
mov al, [vx + di]
add dl, al
mov [x + di], dl
; 行坐标更新
cmp dh, 24 ; 边界检测
je bb
cmp dh, 0
je ub
jmp row
bb: ; 下边界
mov [vy + di], byte -1
jmp row
ub: ; 上边界
mov [vy + di], byte 1
row: ; 更新列坐标
mov al, [vy + di]
add dh, al
mov [y + di], dh
; 颜色更新
mov al, [color + di]
inc al
mov [color + di], al
; 光标切换
xor di, 1
; 延时
push dx
mov ah, 86h
mov cx, 0
mov dx, 0x2710 ; 10ms 
int 15h
pop dx
jmp again ; 循环
string db "lliiuusseennyyuuaann2211330077228899", 0
info db "---liusenyuan21307289---"
vx db 1, -1
vy db 1, 1
x db 0, 79
y db 2, 2
color db 0, 0fh
times 510 - ($ - $$) db 0
db 0x55, 0xaa
