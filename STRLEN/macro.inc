MAXSIZE equ 32

; Инициализация сегмента данных
_initds macro
	mov ax, @data	
	mov ds, ax
	mov ax, 0
endm

; Вызов подпрограммы
_invoke macro fname, args
	push ax
	mov bp, sp
	irp arg, <args>
		lea ax, arg
		push ax
	endm
	call fname
	mov sp, bp
	pop ax
endm

; Доступ к аргументу
_arg equ bp - 2*

; Сохранение регистров
_push_regs macro list
	irp reg, <list>
		push reg
	endm
endm

; Выгрузка регистров
_pop_regs macro list
	irp reg, <list>
		pop reg
	endm
endm

; Вывод сообщения
_print_msg macro msg
	mov ah, 09h
	mov dx, offset msg
	int 21h
endm

; Вывод строки
_print_str macro string, strlength
	mov ah, 40h
	mov bx, 0
	mov cx,	strlength
	mov dx, string
	int 21h
endm

; Конец программы
_end_prog macro
	mov ax,4c00h
    int 21h
endm