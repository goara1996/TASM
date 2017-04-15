;------------------------------------
stringToDigit:;(string, digit, base)
	xor ax, ax
	mov di, [var 1]
	mov cx, [di].length_
	mov di, [di].data_
	mov si, [var 3]
	xor bh, bh	
	
	cmp byte ptr [di], '-'
	je l_STD_minus
	mov dx, 0
	push dx
	jmp l_STD_1
l_STD_minus:
	mov dx, 1
	push dx
	jmp l_STD_skip
	
l_STD_1:
	cmp byte ptr [di], ' '
	je l_STD_skip
	mul si
	mov bl, [di]
	sub bl, '0'
	cmp bl, 9
	jle l_STD_CTN
	sub bl, 'A'-'0'-10
l_STD_CTN:
	cmp bx, si
	jge l_STD_err
	add ax, bx
	jc l_STD_err
	js l_STD_err
l_STD_skip:
	inc di
	loop l_STD_1
	
	pop cx
	jcxz l_STD_no_minus
	neg ax
l_STD_no_minus:
	
	mov bx, [var 2]
	mov [bx], ax 
	mov cx, 1
	ret; stringToDigit
l_STD_err:
	_print_msg <ms_err, ms_err_dig, endl>
	pop cx
	mov cx, 0
	ret; Error stringToDigit
;------------------------------------
	
;------------------------------------
digitToString:;(digit, string, base)
	mov ax, [var 1]
	mov si, [var 2]
	mov bx, [var 3]
	
	cmp ax, -1
	jle l_DTS_minus
	mov cx, 0
	jmp l_DTS_minus_checked
l_DTS_minus:
	mov cx, 1
	neg ax
l_DTS_minus_checked:
	
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
	jcxz l_DTS_no_minus_1
	inc ax
l_DTS_no_minus_1:
	mov [si].length_, ax
	
	; Выделение памяти
	mov dx, heapptr
	mov [si].data_, dx
	inc ax
	add ax, heapptr
	lea dx, MAXHEAP
	cmp ax, dx
	jg Errors_Heap_Overflow
	mov heapptr, ax
	
	; Ввод числа в нормальном порядке
	dec di
	mov si, [si].data_
	
	jcxz l_DTS_no_minus_2
	mov byte ptr [si], '-'
	inc si
l_DTS_no_minus_2:
	
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