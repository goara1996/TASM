;-----------------
_print_msg macro mslist
	mov ah, 09h
	irp msg, <mslist>
		mov dx, offset msg
		int 21h
	endm
endm
;-----------------

;-----------------
_save_regs macro list
	ifb <list>
		irp reg, <ax, bx, cx, dx, si, di>
			push reg
		endm
	else
		irp reg, <list>
			push reg
		endm
	endif
endm
_load_regs macro list
	ifb <list>
		irp reg, <di, si, dx, cx, bx, ax>
			pop reg
		endm
	else
		irp reg, <list>
			pop reg
		endm
	endif
endm
;-----------------

;-----------------
_init_prog macro
	mov ax, @data	
	mov ds, ax
	mov ax, 0
endm
_exit_prog macro
	mov ax,4c00h
    int 21h
endm
;-----------------

;-----------------
var equ bp - 2*
_sub_invoke macro arg, CHECK
	ifidn <bx>, <arg>
		push [bp - 2]
		goto end_m
	endif
	REG_CHECK = 0
	irp reg, <ax, cx, dx, si, di>
		ifidn <reg>, <arg>
			push reg
			REG_CHECK = 1
		endif
	endm
	if REG_CHECK eq 1
		REG_CHECK = 0
		goto end_m
	endif
	ifidn <dw>, <arg>
		CHECK = 1
		goto end_m
	endif	
	ifidn <db>, <arg>
		CHECK = 2
		goto end_m
	endif
	ifidn <var>, <arg>
		CHECK = 3
		goto end_m
	endif
	ife CHECK eq 0
		if CHECK eq 1
			push arg
			goto end_check
		endif
		if CHECK eq 2
			xor bx, bx
			mov bl, arg
			push bx
			goto end_check
		endif
		if CHECK eq 3 
			mov bx, [bp]
			push ss:[bx - 2 * arg]
			goto end_check
		endif
	:end_check
		CHECK = 0
		goto end_m
	endif
	ifdef arg
		lea bx, arg
	else
		mov bx, arg
	endif
	push bx
:end_m
endm
_invoke macro fname, args
	ifnb <args>
		push bx
		push bp
		mov bp, sp
		INV_CHECK = 0
		irp arg, <args>
			_sub_invoke <arg>, INV_CHECK
		endm
	endif
	call fname
	ifnb <args>
		mov sp, bp
		pop bp
		pop bx
	endif
endm
;-----------------