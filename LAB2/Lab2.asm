masm
model small

include macro.inc

.data
include data.inc
sdata type_string <>


.stack 100h

.code
include io.inc
include convert.inc
include fibo.inc
include trans.inc

main:
	_init_prog
	
	_print_msg <ms_Main_1, endl>
	_invoke leonardoBonacci
	
	_print_msg <ms_Main_2, endl>
	_invoke transLate
	
	_exit_prog
end main