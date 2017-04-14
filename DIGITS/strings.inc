; Применить подпрограмму к каждому символу строки
iterateStr:
	_push_regs	<ax, si>
	
	_unref si, <_arg 1>
l_IS_2:
	cmp byte ptr [si], 0
	je l_IS_1
	call [_arg 2]
	inc si
	jmp l_IS_2
l_IS_1:

	_pop_regs	<si, ax>
	ret ;iterateStr
;------------------------------------------

; Форматировать строку как число
digitForm:

	mov si, [_arg 1]
	_invoke iterateStr <[si].data_, clean_Up>
	mov si, [si].data_
	
	
	ret ;digitForm
;------------------------------------------

; Число в строку с учетом системы счисления
; Аргументы
; 1 - Число
; 2 - Строка
digitToString:
	
	mov si, [_arg 2]
	mov si, [si].data_
	_unref bx, [_arg 1]
	mov ax, bx
	mov cx, digitbase
	
	cmp 
	
	ret ;digitToString
;------------------------------------------

stringToDigit:

	ret ;digitToString
;------------------------------------------