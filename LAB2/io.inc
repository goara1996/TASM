;----------------------
inputString:;(string)

	; Запись в буффер
	lea dx, buffer
	mov ah, 0Ah
	int 21h
	_print_msg endl
	
	; Задание параметров
	xor ax, ax
	mov al, buffer.blenght_
	mov bl, al
	mov si, [var 1]
	mov [si].length_, ax
	mov di, heapptr
	mov [si].data_, di
	
	; Выделение памяти
	inc ax
	add ax, di
	lea dx, MAXHEAP
	cmp ax, dx
	jg Errors_Heap_Overflow
	mov heapptr, ax
	
	; Запись из буффера в строку
	lea si, buffer.bdata_
l_IS_1:
	cmp bl, 0
	je l_IS_2
	mov bh, byte ptr [si]
	mov byte ptr [di], bh
	inc si
	inc di
	dec bl
	jmp l_IS_1
l_IS_2:
	mov byte ptr [di], 0
	
	ret; inputString
	
outputString:;(string)
	mov si, [var 1]
	mov ah, 40h
	mov bx, 0
	mov cx,	[si].length_
	mov dx, [si].data_
	int 21h
	ret; outputString
;----------------------

;----------------------
inputArray:;(array)
	mov si, [var 1]
	mov cx, [si].length_
	cmp cx, 0
	jle l_IA_error
	mov dx, heapptr
	mov [si].data_, dx
	mov si, [si].data_
	
	mov ax, cx
	add ax, cx ; умножение на 2 (word)
	add ax, dx
	lea dx, MAXHEAP
	cmp ax, dx
	jg l_IA_error_1
	mov heapptr, ax
	
	mov bx, 0
l_IA_loop:	
	
	_save_regs <cx, si, bx>
l_IA_redo:
	_print_msg <ms_array_index_start>
	_invoke outputDecimal <bx>
	_print_msg <ms_array_index_end>
	_invoke inputDecimal <digitbuffer>
	jcxz l_IA_redo
	_load_regs <bx, si, cx>
	
	mov dx, digitbuffer
	mov [si], dx
	add si, 2
	
	inc bx
	loop l_IA_loop
	mov cx, 1
	ret; inputArray
l_IA_error:
	_print_msg <ms_err, ms_err_array, endl>
	mov cx, 0
	ret; Error inputArray
l_IA_error_1:
	_print_msg <ms_err, ms_err_array_1, endl>
	mov cx, 0
	ret; Error inputArray

outputArray:;(array)
	mov si, [var 1]
	mov cx, [si].length_
	mov si, [si].data_
	
	_print_msg <ms_array_start>
l_OA_loop:	
	
	_save_regs <cx, si>
	mov ax, word ptr [si]
	_invoke outputDecimal <ax>
	_load_regs <si, cx>
	
	add si, 2
	
	cmp cx, 1
	je l_OA_no_separator
	_print_msg <ms_array_separator>
l_OA_no_separator:
	loop l_OA_loop
	_print_msg <ms_array_end>

	ret; outputArray
;----------------------

;----------------------
inputDigit:;(digit, base)
	_save_mem
	_invoke inputString	  <digitstring>
	_invoke stringToDigit <digitstring, var, 1, var, 2>
	_load_mem
	ret; inputDigit
	
inputDecimal:;(digit)
	_invoke inputDigit <var, 1, 10>
	ret; inputDecimal
	
outputDecimal:;(digit)
	_save_mem
	_invoke digitToString <var, 1, digitstring, 10>
	_invoke outputString  <digitstring>
	_load_mem
	ret; outputDecimal
;----------------------