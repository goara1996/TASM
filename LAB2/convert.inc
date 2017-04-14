;------------------------------------
stringToDigit:;(string, digit, base)
	xor ax, ax
	mov di, [var 1]
	mov cx, [di].length_
	mov di, [di].data_
	mov si, [var 3]
	xor bh, bh
	
l_STD_1:
	mul si
l_STD_noerr:
	mov bl, [di]
	sub bl, '0'
	cmp bl, 9
	jle l_STD_CTN
	sub bl, 'A'-'0'-10
l_STD_CTN:
	add ax, bx
	inc di
	loop l_STD_1
	mov bx, [var 2]
	mov [bx], ax  
	ret; stringToDigit
;------------------------------------
	
;------------------------------------
digitToString:;(digit, string, base)
	mov ax, [var 1]
	mov si, [var 2]
	mov bx, [var 3]
	
	; Конвертация числа в буффер(задом наперед)
	mov di, sbuffer.data_
l_DTS_1:	
	mov dx, 0
	div bx
	add dx, '0'
    cmp dx, '9'
    jle l_DTS_NTC
    add dx, 'A'-'0'-10
l_DTS_NTC:
	mov byte ptr [di], dl
	inc di
	cmp ax, 0
	jne l_DTS_1
	
	; Задание размера
	mov ax, di
	sub ax, sbuffer.data_
	mov [si].length_, ax
	
	; Выделение памяти
	mov dx, heapptr
	mov [si].data_, dx
	inc ax
	add ax, heapptr
	lea dx, MAXHEAP
	cmp ax, dx
	jle l_DTS_noerr
	_print_msg <ms_err, ms_err_heap, endl>
	_exit_prog
l_DTS_noerr:
	mov heapptr, ax
	
	; Ввод числа в нормальном порядке
	dec di
	mov si, [si].data_
l_DTS_2:
	cmp di, sbuffer.data_
	jl l_DTS_3
	mov bh, byte ptr [di]
	mov byte ptr [si], bh
	inc si
	dec di
	jmp l_DTS_2
l_DTS_3:
	mov byte ptr [si], 0

	ret; digitToString
;------------------------------------