
proc_LB_calculate:;(number)
	mov bx, [var 1]
	mov bx, [bx]
	cmp bx, 23
	jg l_proc_LB_err_2
	cmp bx, -1
	jle l_proc_LB_err
	cmp bx, 0
	jne l_PLBC_check_0
	mov cx, 0
	jmp l_PLBC_end
l_PLBC_check_0:
	cmp bx, 1
	jne l_PLBC_check_1
	mov cx, 1
	jmp l_PLBC_end
l_PLBC_check_1:
	mov ax, 0
	mov dx, 1
l_PLBC_1:
	cmp bx, 1
	je l_PLBC_end
	mov cx, ax
	add cx, dx
	mov ax, dx
	mov dx, cx
	dec bx
	jmp l_PLBC_1
l_PLBC_end:
	mov bx, [var 1]
	mov word ptr [bx], cx
	mov cx, 1
	ret; proc_LB_calculate
l_proc_LB_err:
	_print_msg <ms_err, ms_err_fib, endl>
	mov cx, 0
	ret; Error proc_LB_calculate
l_proc_LB_err_2:
	_print_msg <ms_err, ms_err_fib_2, endl>
	mov cx, 0
	ret; Error proc_LB_calculate

number = data_LB_number	
leonardoBonacci:
	_save_mem
	_save_regs
l_LB_redo_1:
	_print_msg ms_LB_1
	_invoke inputDecimal <number>
	jcxz l_LB_redo_1
	_invoke proc_LB_calculate <number>
	jcxz l_LB_redo_1
	_print_msg ms_LB_2
	_invoke outputDecimal <dw, number>
	_print_msg endl
	_load_regs
	_load_mem
	ret; leonardoBonacci