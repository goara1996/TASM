masm
model small
.386

include macro.inc

.data
include data.inc
sdata type_string <>


.stack 100h

.code
include io.inc
include convert.inc
include errors.inc

include fibo.inc
include trans.inc
include arrays.inc

_get_hotkey macro
	mov ah, 08h
	int 21h
endm

main:
	_init_prog

l_Main_ask_hotkey:
	_print_msg <endl, ms_Main_1, endl>
	_get_hotkey
	cmp al, '1'
	je l_Main_lb
	cmp al, '2'
	je l_Main_ts
	cmp al, '3'
	je l_Main_as
	cmp al, 'q'
	je l_Main_end
	_print_msg <ms_Main_hotkeys>
	jmp l_Main_ask_hotkey
	
l_Main_lb:
	_print_msg <ms_Main_2, endl>
	_invoke leonardoBonacci
	jmp l_Main_ask_hotkey
	
l_Main_ts:
	_print_msg <ms_Main_3, endl>
	_invoke transLate
	jmp l_Main_ask_hotkey
	
l_Main_as:
	_print_msg <ms_Main_3, endl>
	_invoke arraySorting
	jmp l_Main_ask_hotkey

l_Main_end:
	_exit_prog
end main