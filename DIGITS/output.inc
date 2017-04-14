; Вывод: [<arg 1><arg 2><endl>]
outStr:
	_push_regs	<ax, bx, cx, dx, si>

	_print_msg <[_arg 1]>
	
	mov si, [_arg 2]
	_print_str [si].data_, [si].length_
	
	_print_msg endl
	
	_pop_regs	<si, dx, cx, bx, ax>
	ret ;outStr

;------------------------------------------

; Вывод: [<arg 1>]
; arg 1 - число размерности dword
outDigit:

	;_invoke digitToString <[_arg 1], dgbuf>
	;_invoke outStr <dgbuf>

	ret ;outDigit