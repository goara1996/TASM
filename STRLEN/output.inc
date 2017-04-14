
; Вывод: [String <arg 1> has size <arg 2>]
hexToChar:
	add dl, '0'
    cmp dl, '9'
    jle thd_end
    add dl, 7
thd_end:
	ret ;hexToChar

outLine:
	_push_regs <ax, bx, cx, dx, si>

	;[String "]
	_print_msg msg1

	;Вывод строки
	mov dx, [_arg 1]
	mov bx, [_arg 2]
	xor cx, cx
	mov cl, byte ptr [bx]
	_print_str dx, cx
		
	;[" has size ]
	_print_msg msg2
	
	mov si, [_arg 2]
	;Вывод размера(hex)
	mov ah, 02h
	mov dl, [si]
	mov cl, 04h
    shr dl, cl
	and dl, 0fh
	call hexToChar
	int 21h
	mov dl, [si]
	and dl, 0fh
	call hexToChar
	int 21h
	
	;[h]
	_print_msg msg3

	;Конец строки
	_print_msg endl
	
	_pop_regs	<si, dx, cx, bx, ax>
	ret ;outLine
;------------------------------------------

; Вывод: [<arg 1><arg 2>]
outStr:
	_push_regs	<ax, bx, cx, dx>
	
	mov dx, [_arg 1]
	_print_msg dx
	
	mov dx, [_arg 2]
	mov bx, [_arg 3]
	xor cx, cx
	mov cl, byte ptr [bx]
	_print_str dx, cx
	
	_print_msg msg6
	
	_pop_regs	<dx, cx, bx, ax>
	ret ;outStr

;------------------------------------------