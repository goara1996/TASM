;----------------------
inputString:;(string)
	lea dx, buffer
	mov ah, 0Ah
	int 21h
	_print_msg endl
	
	xor ax, ax
	mov al, buffer.blenght_
	mov bl, al
	mov si, [var 1]
	mov [si].length_, ax
	mov di, heapptr
	mov [si].data_, di
		
	inc ax
	add ax, di
	lea dx, MAXHEAP
	cmp ax, dx
	jle l_IS_noerr
	_print_msg <ms_err, ms_err_heap, endl>
	_exit_prog
l_IS_noerr:
	mov heapptr, ax
	
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
inputDigit:;(digit, base)
	_invoke inputString	  <digitstring>
	_invoke stringToDigit <digitstring, var, 1, var, 2>
	ret; inputDigit
	
inputDecimal:;(digit)
	_invoke inputDigit <var, 1, 10>
	ret; inputDecimal
	
outputDecimal:;(digit)
	_invoke digitToString <var, 1, digitstring, 10>
	_invoke outputString  <digitstring>
	ret; outputDecimal
;----------------------