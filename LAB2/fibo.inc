
proc_LB_calculate:;(number)
	mov bx, [var 1]
	mov bx, [bx]	
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
	ret; proc_LB_calculate

leonardoBonacci:
	_save_regs
	_print_msg <ms_LB_1>
	_invoke inputDecimal <data_LB_number>
	_invoke proc_LB_calculate <data_LB_number>
	_print_msg ms_LB_2
	_invoke outputDecimal <dw, data_LB_number>
	_print_msg endl
	_load_regs
	ret; leonardoBonacci