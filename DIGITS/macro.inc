BUFFERSIZE  equ 32
HEAPSIZE	equ 1024

_initds macro
	mov ax, @data	
	mov ds, ax
	mov ax, 0
endm

_invoke macro fname, args
	push ax
	mov bp, sp
	irp arg, <args>
		lea ax, arg
		push ax
	endm
	call fname
	mov sp, bp
	pop ax
endm

_arg equ bp - 2*

_unref macro reg, arg
	mov reg, [arg]
	mov reg, [reg]
endm

_unrefd macro arg
	mov reg, [arg]
	mov reg, [reg]
	mov reg, [reg]
endm

_push_regs macro list
	irp reg, <list>
		push reg
	endm
endm

_pop_regs macro list
	irp reg, <list>
		pop reg
	endm
endm

_print_const_int macro const
	mov ah, 02h
	irpc sym, const
		mov dl, sym + '0'
		int 21h
	endm
endm

_print_sym macro sym
	mov ah, 02h
	mov dl, sym
	int 21h
endm

_print_msg macro mslist
	mov ah, 09h
	irp msg, <mslist>
		mov dx, offset msg
		int 21h
	endm
endm

_print_str macro string, strlength
	mov ah, 40h
	mov bx, 0
	mov cx,	strlength
	mov dx, string
	int 21h
endm

_end_prog macro
	mov ax,4c00h
    int 21h
endm