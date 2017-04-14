; Ввод строки в буффер
; Аргументы:
; 1 - Адрес начала буффера
inLine:	
	_push_regs <ax, dx>
	
	_print_msg msg
	
	mov dx, [_arg 1]
	mov ah, 0Ah
	int 21h
	
	_print_msg endl
	
	_pop_regs <dx, ax>
	ret ;inLine
;------------------------------------------

; Из буффера в нуль-терминированную строку
; Аргументы:
; 1 - Адрес буффера
; 2 - Адрес строки
; 3 - Адрес длины буффера
bufToNF:
	_push_regs <si, di, bx, dx>
	mov si, [_arg 1]
	mov di, [_arg 2]
	mov bx, [_arg 3]
	mov bl, byte ptr [bx]
l_BTN_1:
	cmp bl, 0
	je l_BTN_2
	push [si]
	pop  [di]
	inc si
	inc di
	dec bl
	jmp l_BTN_1
l_BTN_2:
	mov byte ptr [di], 0
	
	_pop_regs <dx, bx, di, si>
	ret ;bufToNF
	
;------------------------------------------