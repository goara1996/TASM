;������ ������ ������� � ����������� ������ (char - ASCII ��� �������)
OutCharG macro x,y,color,char
pusha
mov ah,02h
mov bh,0h
mov dh,y
mov dl,x
int 10h
mov ah,09h
mov al,char
mov bh,0h
mov bl,color
mov cx,01h
int 10h
popa
endm
;---------------------------------------------------------
;������ ������ ������� �� ����� � �����. x,y � ������ color
PutPixel macro x,y,color 
pusha
mov ah,0ch
mov al,color
mov bh,0h
mov cx,x
mov dx,y
int 10h
popa
endm
;---------------------------------------------------------
;������ ������ �������������� ����� � �������� ������ 
AxleX macro
local iter
pusha
OutCharG 4eh,0fh,03h,78h ;X
mov cx,640
iter:
 PutPixel cx,240,4h
loop iter
popa
endm
;---------------------------------------------------------
;������ ������ ������������ ����� � �������� ������
AxleY macro
local iters
pusha
mov cx,480
iters:
 mov dx,cx
 PutPixel 320,dx,4h
 dec cx
 cmp cx,19
jge iters

OutCharG 29h,01h,03h,79h ;Y
popa
endm
;---------------------------------------------------------

