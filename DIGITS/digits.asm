masm
model small

;Макрос
include macro.inc

;Сегмент данных
.data
include data.inc

;Сегмент стека
.stack 256

;Сегмент кода
.code
include output.inc
include input.inc
;include strings.inc
;include subfuncs.inc

_submacro macro arg, CHECK
	ifidn <dw>, <arg>
		CHECK = 1
		goto end_m
	endif	
	ifidn <db>, <arg>
		CHECK = 2
		goto end_m
	endif
	ife CHECK eq 0
		if CHECK eq 1
			mov ax, arg
		else 
			if CHECK eq 2
				xor ax, ax
				mov al, arg
			endif
		endif
		CHECK = 0
		goto end_m
	endif
	ifdef arg
		lea ax, arg
	else
		mov ax, arg
	endif
:end_m
endm

_test macro args
	CHECK = 0
	irp arg, <args>
		_submacro arg, CHECK
	endm
endm

fill db "      "
var db 2
testvar dw 3

main_lc_str	stringST<4097, 4>
main:
	_initds
	
label1:
	_invoke getNTstring <str_1>
	jmp label1
	
	_end_prog
;------------------------------------------

end main