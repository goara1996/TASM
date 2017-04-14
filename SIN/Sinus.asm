;прога выводит график синуса

include pixels.inc ;содержит макросы вывода точки, осей и символа

.model small
.stack 100h
.data
gx dd 21.0 ;масштабные коэффициенты
gy dd 160.0
cycleX dd -15.0 ;изменяющаяся переменная 
delta dd 0.001 ;величина изменения
xdiv2 dd 320.0 ;середина по X и Y
ydiv2 dd 240.0
tmp dd 0 ;temp
xr dw 0 ;координаты выводимой точки
yr dw 0
Sine db 'y = cos(x)$'

.code
.486
start:
mov ax,@DATA
mov ds,ax
xor ax,ax
mov cx,7530h ;количество итераций цикла - 30000 ((15+15)/0.001)
;------------------------------------------------------------------
mov ah,0h ;инициализация графического режима 640х480
mov al,12h
int 10h

;-----------------------------------------------------------------
pusha ;вывод строки Sine
mov cx,10
mov bx,0
l3:
 mov al,Sine[bx]
 inc bx
 OutCharG bl,02h,03h,al
loop l3
popa
;-----------------------------------------------------------------
AxleX ;рисуем оси
AxleY
finit ;инициализация сопроцессора

l1:
 fld cycleX        ;st(0)=cycleX
 fld gx            ;st(0)=gx st(1)=cycleX
 fmul              ;st(0)=gx*cycleX
 frndint           ;st(0)=round(gx*cycleX)
 fld xdiv2         ;st(0)=xdiv2 st(1)=round(gx*cycleX)
 fadd              ;st(0)=xdiv2+round(gx*cycleX) - координата X найдена!!!
 fistp word ptr xr ;заносим X в переменную для вывода на экран

 fld cycleX        ;st(0)=cycleX
 fcos              ;st(0)=sin(cycleX)
 fld gy            ;st(0)=gy st(1)=sin(cycleX)
 fmul              ;st(0)=gy*sin(cycleX)
 frndint           ;st(0)=round(gy*sin(cycleX))
 fstp tmp          ;tmp=round(gy*sin(cycleX))
 fld ydiv2         ;st(0)=ydiv2
 fsub tmp          ;st(0)=ydiv2-round(gy*sin(cycleX)) - координата Y найдена!!!
 fistp word ptr yr ;заносим Y в переменную для вывода на экран

 mov ah,0ch
 mov al,0ah
 mov bh,0h
 mov cx,xr
 mov dx,yr
 int 10h
 inc cx
 inc dx
 int 10h
 sub cx, 2
 sub dx, 2
 int 10h
 add cx, 2
 add dx, 2
 int 10h
 
 fld delta ;вычисляем новое значение cycleX
 fld cycleX
 fadd
 fstp cycleX
loop l1 ;цикл по cx
;--------------------------------------------------------------------
mov ah,1h ;ожидание нажатия клавиши 
int 21h
;--------------------------------------------------------------------
mov ah,0h ;перевод обратно в TextMode
mov al,03h
int 10h
;--------------------------------------------------------------------
exit:
mov ax,4C00h ;стандартный выход
int 21h
END start
