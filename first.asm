;Программа преобразования двузначного шестнадцатеричного числа
;в символьном виде в двоичное представление.
;Вход: Исходное шестнадцатеричное число из двух цифр
;вводится с клавиатуры
;Выход: Результат преобразования помещается в регистр dl


;Сегмент макросов(условно)
_push_regs macro list
	irp reg, <list>
		push reg
	endm
endm

_pop_regs macro list
	irp reg, <list>
		pop reg
	endm
endm

_end_prog macro
	mov ax,4c00h
    int 21h
endm

;Сегмент данных
data segment para public "data"
    msg db 'Please, input two hex',0dh,0ah,'$'
data ends

;Сегмент стека
stk segment stack
    db 256 dup("?")
stk ends

;Сегмент кода
code segment para public "code"

getNumber proc
	assume cs:code, ds:data, ss:stk

	;Подготовка данных
	_push_regs <ax, cx>
	xor dl, dl

    ;Вывод строки msg
    mov ax, data
    mov ds, ax
    mov dx, offset msg
    mov ah, 09h
    int 21h

    ;Ввод первой цифры
    xor ax, ax
    mov ah, 01h
    int 21h

    ;Проверка - цифра или буква
    mov dl, al
    sub dl, 30h
    cmp dl, 09h
    jle M1
    sub dl, 27h
M1:
    mov cl, 04h
    shl dl, cl
    int 21h
    sub al, 30h
    cmp al, 09h
    jle M2
    sub al, 27h
M2:
    add dl, al
	
	;Возвращаем регистры в исходное состояние
	_pop_regs <cx, ax>
	
	ret
getNumber endp

main proc
    assume cs:code, ds:data, ss:stk
	
	call getNumber

    _end_prog
main endp

code ends

end main