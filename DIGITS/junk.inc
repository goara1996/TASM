setNTsize:
	_push_regs	<bx, si>
	
	mov si, [_arg 1]
	_unref bx, <_arg 2>
	
	mov bh, 0
	inc bx
	mov [si].length_, bx
	
	_pop_regs	<si, bx>
	ret ;setNTsize
;------------------------------------------
	
; Ввод строки в буффер
; Аргументы:
; 1 - Адрес начала буффера(bfsize)
; 2 - Поясняющее сообщение
inputLine:	
	_push_regs <ax, dx>
	
	_print_msg <[_arg 2], endl>
	
	mov dx, [_arg 1]
	mov ah, 0Ah
	int 21h
	
	_print_msg endl
	
	_pop_regs <dx, ax>
	ret ;inLine
;------------------------------------------

; Динамическое выделение памяти под строку
; Аргументы:
; 1 - Адрес, по которому будет размещен
;     адрес выделенной области
; 2 - Адрес длины выделяемой памяти
allocate:
	_push_regs	<ax, bx>
	; mov ah, 48h
	; _unref bx, <_arg 2>
	; int 21h
	; jnc l_alloc_noerr
	; _print_msg <errmsg, endl>
	
; l_alloc_noerr:	
	; mov bx, [_arg 1]
	; mov [bx], ax
	
	mov bx, [_arg 1]
	mov ax,  heapptr
	mov [bx], ax
	
	_unref bx, <_arg 2>
	add heapptr, bx
	
	_pop_regs	<bx, ax>
	ret ;allocate
	
;------------------------------------------